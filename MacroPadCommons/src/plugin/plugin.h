#pragma once

#include "mppch.h"

#include "sdk_version.h"
#include "version/version.h"
#include "function_types.h"

#ifdef MP_BUILD_PLUGIN
#ifdef __cplusplus
#define MP_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define MP_PLUGIN_EXPORT __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define MP_PLUGIN_EXPORT
#else
#define MP_PLUGIN_EXPORT
#endif
#endif

constexpr int PLUGIN_INITIALIZATION_SUCCESS = 0;
constexpr int PLUGIN_INITIALIZATION_UNKNOWN_FAILURE = 1;
constexpr int PLUGIN_INITIALIZATION_RESSOURCE_LOADING_FAILURE = 2;
constexpr int PLUGIN_INITIALIZATION_MEMORY_AQUISITION_FAILURE = 3;

namespace macropad::plugin
{
		#if WINDOWS_COMP == 1
		typedef HMODULE plugin_handle;
		#elif LINUX_COMP == 1
		typedef void* plugin_handle;
		#endif

		//plugin structure
		struct mp_plugin
		{
			macropad::plugin::int_return_function init;
			macropad::plugin::void_return_function release;

			std::string name;
			std::string description;
			std::string version;
			std::string author;

			macropad::Version4 sdk_version;

			plugin_handle handle;
		};

		MP_PLUGIN_EXPORT int mpInit(void);
		MP_PLUGIN_EXPORT void mpRelease(void);

		#define DESCRIPTION(description) MP_PLUGIN_EXPORT const char* getDescription() { return description; };
		#define PLUGIN_VERSION(version) MP_PLUGIN_EXPORT const char* getPluginVersion() { return #version; };
		#define AUTHOR(author) MP_PLUGIN_EXPORT const char* getAuthor() { return author; };

		// Used to define the plugin name. Also creates some mandatory functions.
		#define PLUGIN(name) MP_PLUGIN_EXPORT const char* getName() { return name; };																\
							 MP_PLUGIN_EXPORT const char* getSDKVersion(void) { return MP_SDK_VERSION; }											\
							 macropad::plugin::mp_plugin* self_pointer; /* Owned by core, no cleanup needed*/								\
							 MP_PLUGIN_EXPORT void setPointer(macropad::plugin::mp_plugin* plugin_pointer) { self_pointer = plugin_pointer; }

		class PluginException : public std::runtime_error
		{
		public:
			PluginException(macropad::plugin::mp_plugin& plugin_, const char* msg) throw() : std::runtime_error(msg), plugin(plugin_) {};
			macropad::plugin::mp_plugin& getPlugin() { return plugin; };

			macropad::plugin::mp_plugin& plugin;
		};
}

#ifndef MP_BUILD_PLUGIN
inline std::ostream& operator<<(std::ostream& os, const macropad::plugin::mp_plugin& e)
{
	std::string description = std::regex_replace(e.description, std::regex("\n"), "\n\t\t\t\t\t\t ");

	return os << "Plugin: " << e.name << " : " << e.version << "\n\t\t\t\t\t\t " <<
		"Description: " << description << "\n\t\t\t\t\t\t " <<
		"Author: " << e.author << "\n\t\t\t\t\t\t " <<
		"SDK Version: " << e.sdk_version;

	// TODO: fix "<< e.sdk_version"
}
#endif