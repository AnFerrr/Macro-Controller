#pragma once

#ifdef SDK_EXPORT
#define SDK_DLL extern "C" __declspec(dllexport)
#else
#define SDK_DLL extern "C" __declspec(dllimport)
#endif