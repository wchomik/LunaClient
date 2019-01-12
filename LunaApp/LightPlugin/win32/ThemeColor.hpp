#pragma once

#include <prism/Prism.hpp>

#include <Windows.h>
#undef interface

class ThemeColor
{
public:
    explicit ThemeColor();
    ~ThemeColor();
    prism::CieXYZ get();
private:
    using GetImmersiveColorFromColorSetEx_t =
        unsigned int __stdcall (
            unsigned int  dwImmersiveColorSet,
            unsigned int dwImmersiveColorType,
            bool bIgnoreHighContrast,
            unsigned int dwHighContrastCacheMode);

    using GetImmersiveColorTypeFromName_t =
        unsigned int __stdcall (const wchar_t * pName);

    using GetImmersiveUserColorSetPreference_t =
        unsigned int __stdcall (
            bool bForceCheckRegistry,
            bool bSkipCheckOnFail);

    bool mLoaded;

    HINSTANCE mDllHandle;

    GetImmersiveColorFromColorSetEx_t * GetImmersiveColorFromColorSetEx;
    GetImmersiveColorTypeFromName_t * GetImmersiveColorTypeFromName;
    GetImmersiveUserColorSetPreference_t * GetImmersiveUserColorSetPreference;

    unsigned int mColorType;
};
