#pragma once

#if MP_PLATFORM_WINDOWS == 1
#ifdef MP_BUILD_COMMONS
#define CORE_DLL __declspec(dllexport)
#else
#define CORE_DLL __declspec(dllimport)
#endif
#else
#define CORE_DLL
#endif

#define BIT(x) (1 << x) /**< @brief Makes a number with the x bit set to 1. */

#define stringify(a) stringify_(a)
#define stringify_(a) #a

namespace macropad
{
	typedef unsigned int index; /**< @brief For use in for loops. */
}