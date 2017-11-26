#ifndef THEMECOLOR_H
#define THEMECOLOR_H

#include "luna/colorutils.h"
#include <Windows.h>

namespace luna {
    class ThemeColor
    {
    public:
        ThemeColor();
        ~ThemeColor();
        Color get();
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

        bool allOk;

        HINSTANCE mDllHandle;

        GetImmersiveColorFromColorSetEx_t * GetImmersiveColorFromColorSetEx;
        GetImmersiveColorTypeFromName_t * GetImmersiveColorTypeFromName;
        GetImmersiveUserColorSetPreference_t * GetImmersiveUserColorSetPreference;

        unsigned int mColorType;
    };
}
#endif // THEMECOLOR_H
