#pragma once

#ifdef PLUGIN_EXPORT
#define PLUGIN_DLL extern "C" __declspec(dllexport)
#else
#define PLUGIN_DLL extern "C" __declspec(dllimport)
#endif