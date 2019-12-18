#include "ThemeColor.hpp"

#include <prism/Prism.hpp>

const char * const dllName = "uxtheme.dll";

const char * const GetImmersiveColorFromColorSetEx_Name =
    reinterpret_cast<char *>(95);

const char * const GetImmersiveColorTypeFromName_Name =
    reinterpret_cast<char *>(96);

const char * const GetImmersiveUserColorSetPreference_Name =
    reinterpret_cast<char *>(98);

ThemeColor::ThemeColor() :
    mLoaded(false),
    mDllHandle(0),
    GetImmersiveColorFromColorSetEx(nullptr),
    GetImmersiveColorTypeFromName(nullptr),
    GetImmersiveUserColorSetPreference(nullptr)
{
    mDllHandle = LoadLibrary(dllName);
    if(NULL == mDllHandle) {
        return;
    }

    GetImmersiveColorFromColorSetEx =
        reinterpret_cast<GetImmersiveColorFromColorSetEx_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveColorFromColorSetEx_Name));

    if(nullptr == GetImmersiveColorFromColorSetEx) {
        return;
    }

    GetImmersiveColorTypeFromName =
        reinterpret_cast<GetImmersiveColorTypeFromName_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveColorTypeFromName_Name));

    if(nullptr == GetImmersiveColorTypeFromName) {
        return;
    }

    GetImmersiveUserColorSetPreference =
        reinterpret_cast<GetImmersiveUserColorSetPreference_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveUserColorSetPreference_Name));

    if(nullptr == GetImmersiveUserColorSetPreference) {
        return;
    }

    mColorType = GetImmersiveColorTypeFromName(L"ImmersiveStartSelectionBackground");
    mLoaded = true;
}

ThemeColor::~ThemeColor()
{
    if(NULL != mDllHandle) FreeLibrary(mDllHandle);
}

prism::CieXYZ ThemeColor::get() {
    if(!mLoaded) {
        return prism::CieXYZ(1.0, 0.0, 1.0, 0.0);
    }

    unsigned int userColorSet = GetImmersiveUserColorSetPreference(false, false);
    unsigned int color = GetImmersiveColorFromColorSetEx(
        userColorSet,
        mColorType,
        false,
        0);

    auto rgb = prism::linearizeSRGB(prism::fromInteger(color));
    rgb[3] = 0.0f;
    
    return prism::RGBColorSpaceTransformation(prism::sRGB()).transform(rgb);
}


