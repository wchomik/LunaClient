#include "screencapture.h"

#include <iostream>
#include <algorithm>
#include <iterator>

#include <QMutexLocker>

#include "shaders.h"

#include "lunaconfig.h"
#include "win32errorhandling.h"


using namespace Microsoft::WRL;

namespace luna { namespace graphics {
    ScreenCapture::ScreenCapture(QObject *parent) :
        QThread(parent),
        mShouldRun(true),
        mHasOutput(false),
        mOutputWidth(0),
        mOutputHeight(0)
    {
        HRESULT hr;
        hr = CreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)&mFactory);
        testHR(hr);
        // adapter 0 is always the one with primary display
        // so it's probably the right one
        hr = mFactory->EnumAdapters(0, &mAdapter);
        testHR(hr);

        D3D_FEATURE_LEVEL featureLevels[]{
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_1
        };
        D3D_FEATURE_LEVEL featureLevel;
        hr = D3D11CreateDevice(
            nullptr,//mAdapter.Get(),
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            D3D11_CREATE_DEVICE_DEBUG,
            featureLevels,
            4,
            D3D11_SDK_VERSION,
            mDevice.GetAddressOf(),
            &featureLevel,
            mContext.GetAddressOf());
        testHR(hr);

        hr = mDevice->CreateVertexShader(vertexCode, sizeof(vertexCode), nullptr, mVertexShader.GetAddressOf());
        testHR(hr);

        hr = mDevice->CreatePixelShader(pixelCode, sizeof(pixelCode), nullptr, mPixelShader.GetAddressOf());
        testHR(hr);

        D3D11_INPUT_ELEMENT_DESC elems[]{
            {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXTURE_COORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };
        hr = mDevice->CreateInputLayout(elems, 2, vertexCode, sizeof(vertexCode), mInputLayout.GetAddressOf());
        testHR(hr);

        float vertexData[]{
            0, 0, 0, 1, 0, 0,
            2, 0, 0, 1, 2, 0,
            0, 2, 0, 1, 0, 2
        };
        D3D11_BUFFER_DESC vertexBufferDesc{
            sizeof(vertexData),
            D3D11_USAGE_IMMUTABLE,
            D3D11_BIND_VERTEX_BUFFER,
            0,
            0,
            sizeof(float) * 6
        };
        D3D11_SUBRESOURCE_DATA initData{ vertexData, 0, 0 };
        hr = mDevice->CreateBuffer(&vertexBufferDesc, &initData, mVertexBuffer.GetAddressOf());
        testHR(hr);

        D3D11_SAMPLER_DESC samplerDesc{
            D3D11_FILTER_MIN_MAG_MIP_POINT,
            D3D11_TEXTURE_ADDRESS_CLAMP,
            D3D11_TEXTURE_ADDRESS_CLAMP,
            D3D11_TEXTURE_ADDRESS_CLAMP,
            0.0f,
            1,
            D3D11_COMPARISON_NEVER,
            {0.0f, 0.0f, 0.0f, 0.0f},
            0.0f,
            100.0f
        };

        hr = mDevice->CreateSamplerState(&samplerDesc, mPointSampler.GetAddressOf());
        testHR(hr);

        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        hr = mDevice->CreateSamplerState(&samplerDesc, mMipSampler.GetAddressOf());
        testHR(hr);

        D3D11_RASTERIZER_DESC rasterizerDesc{
            D3D11_FILL_SOLID,
            D3D11_CULL_NONE,
            false,
            0,
            0.0f,
            0.0f,
            false,
            false,
            false,
            false
        };
        hr = mDevice->CreateRasterizerState(&rasterizerDesc, mRasterizerState.GetAddressOf());
        testHR(hr);

        unsigned strides = sizeof(float) * 6;
        unsigned offsets = 0;
        mContext->IASetInputLayout(mInputLayout.Get());
        mContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &strides, &offsets);
        mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        mContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
        mContext->PSSetShader(mPixelShader.Get(), nullptr, 0);

        mContext->RSSetState(mRasterizerState.Get());
    }

    void ScreenCapture::configure(const unsigned width, const unsigned height)
    {
        QMutexLocker mutex(&mDuplicationMutex);
        HRESULT hr;
        if(width != mPixels.columns() || height != mPixels.rows()){
            obtainScreen();
            mPixels = Array2D<Color>(width, height);

            D3D11_TEXTURE2D_DESC texDesc{
                width,
                height,
                1u, // no mipmapping
                1u, // single texture
                DXGI_FORMAT_R32G32B32A32_FLOAT,
                {1, 0}, // no multisampling
                D3D11_USAGE_DEFAULT,
                D3D11_BIND_RENDER_TARGET,
                0u, // no cpu access
                0
            };
            hr = mDevice->CreateTexture2D(&texDesc, nullptr, mScaledTexture.ReleaseAndGetAddressOf());
            testHR(hr);

            texDesc.Usage = D3D11_USAGE_STAGING;
            texDesc.BindFlags = 0;
            texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            hr = mDevice->CreateTexture2D(&texDesc, nullptr, mCPUTexture.ReleaseAndGetAddressOf());
            testHR(hr);

            D3D11_RENDER_TARGET_VIEW_DESC renderDesc;
            renderDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            renderDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            renderDesc.Texture2D.MipSlice = 0;

            hr = mDevice->CreateRenderTargetView(mScaledTexture.Get(), &renderDesc, mScaledTextureRenderView.ReleaseAndGetAddressOf());
            testHR(hr);
        }
    }

    void ScreenCapture::stop(){
        mShouldRun = false;
        wait();
    }

    void ScreenCapture::run()
    {
        while(mShouldRun){
            bool acquired = false;
            ComPtr<IDXGIResource> desktopResource;
            {
                QMutexLocker mutex(&mDuplicationMutex);

                HRESULT hr;
                if(mHasOutput){
                    DXGI_OUTDUPL_FRAME_INFO frameInfo;
                    hr = mOutputDuplication->AcquireNextFrame(100, &frameInfo, desktopResource.ReleaseAndGetAddressOf());
                    if(DXGI_ERROR_WAIT_TIMEOUT == hr){
                        continue;
                    }else if(FAILED(hr)){
                        mHasOutput = false;
                    }else{
                        acquired = true;
                    }
                }else{
                    mHasOutput = obtainScreen();
                }
            }
            if(acquired){
                processFrame(desktopResource);
            }else if(!mHasOutput){
                QThread::msleep(100);
            }
        }
        mShouldRun = true;
    }

    void ScreenCapture::processFrame(ComPtr<IDXGIResource> &desktopResource)
    {
        HRESULT hr;
        ComPtr<ID3D11Texture2D> original;
        hr = desktopResource.As<ID3D11Texture2D>(&original);
        testHR(hr);

        D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
        viewDesc.Format = mOutputFormat;
        viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        viewDesc.Texture2D.MostDetailedMip = 0;
        viewDesc.Texture2D.MipLevels = 1;

        //ComPtr<ID3D11ShaderResourceView> outputView;
        //hr = mDevice->CreateShaderResourceView(original.Get(), &viewDesc, outputView.GetAddressOf());
        //testHR(hr);

        mContext->CopyResource(mMipTexture.Get(), original.Get());
        //blitTexture(mMipTextureRenderView.Get(), outputView.Get(), mPointSampler.Get(), mOutputWidth, mOutputHeight);
        mContext->GenerateMips(mMipTextureShaderView.Get());
        blitTexture(mScaledTextureRenderView.Get(), mMipTextureShaderView.Get(), mMipSampler.Get(), mPixels.columns(), mPixels.rows());

        mContext->CopyResource(mCPUTexture.Get(), mScaledTexture.Get());
        D3D11_MAPPED_SUBRESOURCE resource;
        hr = mContext->Map(mCPUTexture.Get(), 0, D3D11_MAP_READ, 0, &resource);
        testHR(hr);

        uint8_t * src = reinterpret_cast<uint8_t *>(resource.pData);
        uint8_t * dst = reinterpret_cast<uint8_t *>(mPixels.data());
        size_t dstPitch = mPixels.columns() * sizeof(Color);
        size_t srcPitch = resource.RowPitch;
        if(srcPitch != dstPitch){
            for(size_t i = 0; i < mPixels.rows(); ++i){
                memcpy(dst, src, dstPitch);
                dst += dstPitch;
                src += srcPitch;
            }
        }else{
            memcpy(dst, src, dstPitch * mPixels.rows());
        }

        mContext->Unmap(mCPUTexture.Get(), 0);

        emit dataReady();
    }

    void ScreenCapture::blitTexture(ID3D11RenderTargetView * dst, ID3D11ShaderResourceView * src, ID3D11SamplerState * sampler, size_t width, size_t height)
    {
        D3D11_VIEWPORT viewport{0, 0, width, height, 0, 1};
        mContext->OMSetRenderTargets(1, &dst, nullptr);
        mContext->PSSetShaderResources(0, 1, &src);
        mContext->PSSetSamplers(0, 1, &sampler);
        mContext->RSSetViewports(1, &viewport);
        mContext->Draw(3, 0);
    }

    bool ScreenCapture::obtainScreen()
    {
        DXGI_FORMAT supportedFormats[]{
            DXGI_FORMAT_R16G16B16A16_FLOAT,
            DXGI_FORMAT_R10G10B10A2_UNORM,
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
            DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_B8G8R8A8_UNORM,
        };
        DXGI_FORMAT viewFormats[]{
            DXGI_FORMAT_R16G16B16A16_FLOAT,
            DXGI_FORMAT_R10G10B10A2_UNORM,
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
            DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
            DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
        };
        static_assert(sizeof(supportedFormats) == sizeof(viewFormats), "Different array sizes");
        const size_t formatCount = sizeof(supportedFormats) / sizeof(DXGI_FORMAT);
        HRESULT hr;
        bool found = false;
        for(int i = 0;; ++i){
            ComPtr<IDXGIOutput> output;
            hr = mAdapter->EnumOutputs(i, &output);
            if(DXGI_ERROR_NOT_FOUND == hr) break;
            else testHR(hr);

            hr = output.As<IDXGIOutput5>(&mDuplicatedOutput);
            if(!FAILED(hr)){
                hr = mDuplicatedOutput->DuplicateOutput1(
                    mDevice.Get(),
                    0,
                    formatCount,
                    supportedFormats,
                    mOutputDuplication.ReleaseAndGetAddressOf());
                if(!FAILED(hr)){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
            return false;
        }else{
            DXGI_OUTDUPL_DESC  desc;
            mOutputDuplication->GetDesc(&desc);
            mOutputWidth = desc.ModeDesc.Width,
            mOutputHeight = desc.ModeDesc.Height;
            auto index = std::find(supportedFormats, supportedFormats + formatCount, desc.ModeDesc.Format)
                    - supportedFormats;
            if(index == formatCount) throw std::runtime_error("Unexpected format");
            mOutputFormat = viewFormats[index];

            D3D11_TEXTURE2D_DESC texDesc{
                mOutputWidth,
                mOutputHeight,
                0, // mip levels all
                1, // single texture
                mOutputFormat,
                {1, 0}, // no multisampling
                D3D11_USAGE_DEFAULT,
                D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET,
                0, // no cpu access
                D3D11_RESOURCE_MISC_GENERATE_MIPS
            };
            hr = mDevice->CreateTexture2D(&texDesc, nullptr, mMipTexture.ReleaseAndGetAddressOf());
            testHR(hr);

            D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
            viewDesc.Format = mOutputFormat;
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            viewDesc.Texture2D.MipLevels = -1;
            viewDesc.Texture2D.MostDetailedMip = 0;
            hr = mDevice->CreateShaderResourceView(mMipTexture.Get(), &viewDesc, mMipTextureShaderView.ReleaseAndGetAddressOf());
            testHR(hr);

            return true;
        }
    }
}}

