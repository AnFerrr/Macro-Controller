#pragma once

#if defined(__linux__)
#define LINUX_COMP 1
#define WINDOWS_COMP 0
#elif _WIN32
#define WINDOWS_COMP 1
#define LINUX_COMP 0
#endif

#if WINDOWS_COMP == 1
#ifdef MP_BUILD_COMMONS
#define CORE_DLL __declspec(dllexport)
#else
#define CORE_DLL __declspec(dllimport)
#endif
#else
#define CORE_DLL
#endif

#define BIT(x) (1 << x)

#define stringify(a) stringify_(a)
#define stringify_(a) #a

namespace macropad
{
	typedef unsigned int index;
}