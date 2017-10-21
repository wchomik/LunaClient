#include "themecolor.h"
/*
[DllImport("uxtheme.dll", EntryPoint = "#95")]
   public static extern uint GetImmersiveColorFromColorSetEx(uint dwImmersiveColorSet, uint dwImmersiveColorType, bool bIgnoreHighContrast, uint dwHighContrastCacheMode);
   [DllImport("uxtheme.dll", EntryPoint = "#96")]
   public static extern uint GetImmersiveColorTypeFromName(IntPtr pName);
   [DllImport("uxtheme.dll", EntryPoint = "#98")]
   public static extern int GetImmersiveUserColorSetPreference(bool bForceCheckRegistry, bool bSkipCheckOnFail);

   public Color GetThemeColor()
   {
       var colorSetEx = GetImmersiveColorFromColorSetEx(
           (uint)GetImmersiveUserColorSetPreference(false, false),
           GetImmersiveColorTypeFromName(Marshal.StringToHGlobalUni("ImmersiveStartSelectionBackground")),
           false, 0);

       var colour = Color.FromArgb((byte)((0xFF000000 & colorSetEx) >> 24), (byte)(0x000000FF & colorSetEx),
           (byte)((0x0000FF00 & colorSetEx) >> 8), (byte)((0x00FF0000 & colorSetEx) >> 16));

       return colour;
   }*/

#include <QtDebug>

const wchar_t * const dllName = L"uxtheme.dll";
const char * const GetImmersiveColorFromColorSetEx_Name =
    reinterpret_cast<char *>(95);
const char * const GetImmersiveColorTypeFromName_Name =
    reinterpret_cast<char *>(96);
const char * const GetImmersiveUserColorSetPreference_Name =
    reinterpret_cast<char *>(98);

namespace luna {
    ThemeColor::ThemeColor() :
        mDllHandle(0),
        GetImmersiveColorFromColorSetEx(nullptr),
        GetImmersiveColorTypeFromName(nullptr),
        GetImmersiveUserColorSetPreference(nullptr)
    {
        mDllHandle = LoadLibrary(dllName);

        GetImmersiveColorFromColorSetEx =
            reinterpret_cast<GetImmersiveColorFromColorSetEx_t *>(
                GetProcAddress(
                    mDllHandle,
                    GetImmersiveColorFromColorSetEx_Name));

        GetImmersiveColorTypeFromName =
            reinterpret_cast<GetImmersiveColorTypeFromName_t *>(
                GetProcAddress(
                    mDllHandle,
                    GetImmersiveColorTypeFromName_Name));

        GetImmersiveUserColorSetPreference =
            reinterpret_cast<GetImmersiveUserColorSetPreference_t *>(
                GetProcAddress(
                    mDllHandle,
                    GetImmersiveUserColorSetPreference_Name));

        mColorType = GetImmersiveColorTypeFromName(L"ImmersiveStartSelectionBackground");
    }

    ThemeColor::~ThemeColor() {
        FreeLibrary(mDllHandle);
    }

    Color ThemeColor::get() {
        unsigned int userColorSet = GetImmersiveUserColorSetPreference(false, false);
        unsigned int color = GetImmersiveColorFromColorSetEx(
            userColorSet,
            mColorType,
            false,
            0);

        return uintToColor(color).array().pow(2.2f).matrix();
    }
}

