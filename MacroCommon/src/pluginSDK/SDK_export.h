#pragma once

#define MP_BUILD_SDK_DLL
#ifdef MP_BUILD_SDK_DLL
#define MP_SDK_DLL __declspec(dllexport)
#else
#define MP_SDK_DLL __declspec(dllimport)
#endif