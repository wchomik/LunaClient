#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <d3d11.h>
#include <dxgi1_5.h>
#include <wrl.h>

#include <lunacore/colorutils.h>
#include "array2d.h"

class ScreenCapture
{
public:
    ScreenCapture();
    ~ScreenCapture();

    void configure(const unsigned width, const unsigned height);
    Array2D<luna::Color> & pixels(){ return mPixels; }
    bool getNextFrame();
private:
    void processFrame(Microsoft::WRL::ComPtr<IDXGIResource> & desktopResource);
    void blitTexture(ID3D11RenderTargetView * dst, ID3D11ShaderResourceView * src, ID3D11SamplerState * sampler, size_t width, size_t height);
    bool obtainScreen();
    bool mHasOutput;

    Microsoft::WRL::ComPtr<IDXGIFactory2> mFactory;
    Microsoft::WRL::ComPtr<IDXGIAdapter> mAdapter;
    Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> mPointSampler;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> mMipSampler;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
    Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;

    Microsoft::WRL::ComPtr<IDXGIOutput5> mDuplicatedOutput;
    Microsoft::WRL::ComPtr<IDXGIOutputDuplication> mOutputDuplication;
    DXGI_FORMAT mOutputFormat;
    size_t mOutputWidth;
    size_t mOutputHeight;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> mMipTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mMipTextureShaderView;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mMipTextureRenderView;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> mScaledTexture;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mScaledTextureRenderView;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> mCPUTexture;

    Array2D<luna::Color> mPixels;
};




#endif // SCREENCAPTURE_H
