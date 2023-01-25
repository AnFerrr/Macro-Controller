#pragma once

#include "mppch.h"

#include "version/version.h"

#if MP_PLATFORM_WINDOWS == 1
typedef HMODULE plugin_handle; /**< @brief Pointer to a plugin library. */
#elif MP_PLATFORM_LINUX == 1
typedef void* plugin_handle; /**< @brief Pointer to a plugin library. */
#endif

namespace macropad::plugin
{
	typedef int (*int_return_function)(); /**< @brief Pointer to a function returning an int and taking no parameter. */
	typedef void (*void_return_function)(); /**< @brief Pointer to a function returning an int and taking no parameter. */
	typedef const char* (*cstr_return_function)(); /**< @brief Pointer to a function returning an int and taking no parameter. */
	/**
	 * @brief Structure holding a single plugin's data.
	 */
	struct mp_plugin
	{
		/**
		 * @brief Pointer to the initiating function of the plugin.
		 *
		 * Called when loading the plugin.
		 * @see mpInit
		 */
		macropad::plugin::int_return_function init;
		/**
		 * @brief Pointer to the release function of the plugin.
		 *
		 * Called when releasing plugin. Usually when stopping program or disabling plugin.
		 * @see mpRelease
		 */
		macropad::plugin::void_return_function release;

		std::string name;
		std::string description;
		std::string version;
		std::string author;

		/**
		 * @brief Version of the SDK used to compile this plugin.
		 *
		 * This is attributed automatically.
		 */
		macropad::Version4 sdk_version;

		/**
		 * @brief Pointer to the current plugin in the software once fully loaded.
		 */
		plugin_handle handle;
	};
}