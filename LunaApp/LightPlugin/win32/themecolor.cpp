#include "themecolor.h"

#include <QtDebug>

using namespace luna;

const wchar_t * const dllName = L"uxtheme.dll";

const char * const GetImmersiveColorFromColorSetEx_Name =
    reinterpret_cast<char *>(95);

const char * const GetImmersiveColorTypeFromName_Name =
    reinterpret_cast<char *>(96);

const char * const GetImmersiveUserColorSetPreference_Name =
    reinterpret_cast<char *>(98);

ThemeColor::ThemeColor() :
    allOk(true),
    mDllHandle(0),
    GetImmersiveColorFromColorSetEx(nullptr),
    GetImmersiveColorTypeFromName(nullptr),
    GetImmersiveUserColorSetPreference(nullptr)
{
    mDllHandle = LoadLibrary(dllName);
    if(NULL == mDllHandle) {
        allOk = false;
        return;
    }

    GetImmersiveColorFromColorSetEx =
        reinterpret_cast<GetImmersiveColorFromColorSetEx_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveColorFromColorSetEx_Name));

    if(nullptr == GetImmersiveColorFromColorSetEx) {
        allOk = false;
        return;
    }

    GetImmersiveColorTypeFromName =
        reinterpret_cast<GetImmersiveColorTypeFromName_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveColorTypeFromName_Name));

    if(nullptr == GetImmersiveColorTypeFromName) {
        allOk = false;
        return;
    }

    GetImmersiveUserColorSetPreference =
        reinterpret_cast<GetImmersiveUserColorSetPreference_t *>(
            GetProcAddress(
                mDllHandle,
                GetImmersiveUserColorSetPreference_Name));

    if(nullptr == GetImmersiveUserColorSetPreference) {
        allOk = false;
        return;
    }

    mColorType = GetImmersiveColorTypeFromName(L"ImmersiveStartSelectionBackground");
}

ThemeColor::~ThemeColor() {
    if(NULL != mDllHandle) FreeLibrary(mDllHandle);
}

Color ThemeColor::get() {
    if(!allOk) {
        return Color(1.0, 0.0, 1.0, 0.0);
    }

    unsigned int userColorSet = GetImmersiveUserColorSetPreference(false, false);
    unsigned int color = GetImmersiveColorFromColorSetEx(
        userColorSet,
        mColorType,
        false,
        0);

    Color ret = uintToColor(color).array().pow(2.2f).matrix();
    ret[3] = 0.0;
    return ret;
}


