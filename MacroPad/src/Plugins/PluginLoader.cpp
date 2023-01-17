#include <filesystem>

#include "Log/Log.h"
#include "PluginLoader.h"
#include <profiling/profiling_timer.h>
#include <directory/directory.h>
#include <plugin/function_types.h>

/**
 * @brief Gets the list of libraries in the specified directory
 *
 * @param dir The directory to list libraries from
 * @param library_list Output vector containing the library filenames
 */
void getLibraryList(const std::string& dir, std::vector<std::string>& library_list)
{
	TIMING_FUNCTION();
	std::vector<std::string> file_list;
	macropad::directory_management::list_regular_files(dir, file_list);

	std::regex regex(SHARED_LIB_EXTENSION, std::regex_constants::icase);

	MP_CORE_TRACE("Getting list of libraries from plugin directory ({})...", dir);
	for (auto& file : file_list)
		if (std::regex_match(file, regex))
			library_list.push_back(dir + "/" + file);
}

/**
 * @brief Loads a library from the given library name.
 *
 * @param library_path The path of the library to be loaded.
 * @param libraries_handles A plugin to store the handle to the successfully loaded library and a name.
 */
void MPLoadLibrary(const std::string& library_path, macropad::plugin::mp_plugin& plugin)
{
	TIMING_FUNCTION();
	MP_CORE_TRACE("Loading library {} to memory...", library_path);
	MP_CORE_INDENT();

	plugin.handle = LoadLibraryA(library_path.c_str());
	plugin.name = library_path.substr(library_path.find_last_of('/') + 1);

	if (plugin.handle) {
		MP_CORE_INFO("{} opened.", plugin.name);
		MP_CORE_RESET_INDENT();
	} else {
		std::string error = plugin.name + " isn't a valid library.";
		MP_CORE_RESET_INDENT();
		throw std::runtime_error(error);
	}
}

/**
 * @brief Fills a plugin structure with information from a DLL handle.
 *
 * @param handle The handle to the library from which to retrieve data.
 * @param plugin The plugin struct to be filled.
 */
void fillPlugin(HMODULE& handle, macropad::plugin::mp_plugin& plugin)
{
	TIMING_FUNCTION();
	plugin.init = (macropad::plugin::int_return_function)getDLLFunction<int>(handle, "mpInit", true);

	getDLLFunction<void, macropad::plugin::mp_plugin*>(handle, "setPointer", true)(&plugin);


	plugin.release = (macropad::plugin::void_return_function)getDLLFunction<void>(handle, "mpRelease", false);

	plugin.name = std::regex_replace(callDLLFunction<const char*>(handle, "getName", false, ""), std::regex("[^&+<> -(_)^*,;:!<?./[:alnum:]]+"), "?");
	plugin.description = std::regex_replace(callDLLFunction<const char*>(handle, "getDescription", false, ""), std::regex("[^&+ -<>\\n(_)^*,;:!<?./[:alnum:]]+"), "?");
	plugin.author = std::regex_replace(callDLLFunction<const char*>(handle, "getAuthor", false, ""), std::regex("[^&+<> -(_)^*,;:!<?./[:alnum:]]+"), "?");
	plugin.version = std::regex_replace(callDLLFunction<const char*>(handle, "getPluginVersion", false, ""), std::regex("[^&+<> -(_)^*,;:!<?./[:alnum:]]+"), "?");
}

/**
 * @brief Loads the specified plugin into memory and initializes it if it is compatible with the current version of the MacroPad plugin SDK.
 *
 * @param plugin The plugin object to load and initialize.
 * @param plugin_list A vector to store the loaded and initialized plugin in.
*/
void initiatializePlugin(macropad::plugin::mp_plugin plugin, std::vector<macropad::plugin::mp_plugin>& plugin_list)
{
	MP_CORE_TRACE("initializing plugin " + plugin.name);
	// TODO: add specific error treatment
	// MAYBE TRY: add warning values and store in plugin
	// TODO: make error flags
	if (plugin.init() == PLUGIN_INITIALIZATION_SUCCESS) {
		MP_CORE_INFO("Plugin loaded succesfully.");
		plugin_list.push_back(plugin);
	}
	else
		throw std::runtime_error("Something went wrong during plugin initialization");
}

/**
 * @brief Checks if the plugin is compatible with the current version of the MacroPad SDK.
 * @param plugin The plugin to be checked.
 * 
 * @return True if the plugin is compatible, false otherwise.
 */
bool checkPluginCompatibility(macropad::plugin::mp_plugin& plugin)
{
	TIMING_FUNCTION();
	macropad::Version4 sdk_version = MP_SDK_VERSION;
	std::string tmp_version_str = callDLLFunction<const char*>(plugin.handle, "getSDKVersion", true, 0);
	plugin.sdk_version = tmp_version_str.c_str();

	if (plugin.sdk_version.minor < sdk_version.minor)
		return false;

	return true;
}

/**
 * @brief Loads all the plugins from a given directory and stores them in the provided vector.
 *
 * @param dir The directory to load the plugins from.
 * @param plugins A reference to the vector where the loaded plugins will be stored.
*/
void loadPlugins(const std::string& dir, std::vector<macropad::plugin::mp_plugin>& plugins)
{
	MP_CORE_TRACE("Starting to load plugins");
	TIMING_FUNCTION();
	std::vector<std::string> libraries_names;
	getLibraryList(dir, libraries_names);

	for (const auto& library_path : libraries_names) {
		macropad::plugin::mp_plugin plugin;

		try {
			TIMING_SCOPE("try loading plugin " + library_path);

			MPLoadLibrary(library_path, plugin);
			if (!checkPluginCompatibility(plugin))
				throw std::runtime_error("Critical incompatibility with current SDK version.");
			
			MP_CORE_TRACE("Opening {}...", plugin.name);
			MP_CORE_INDENT_VALUE(plugin.name);
			
			fillPlugin(plugin.handle, plugin);
			initiatializePlugin(plugin, plugins);
		}
		catch (const std::runtime_error e) {
			macropad::logging::cannot_load_plugin(plugin.name.c_str(), e.what());
			FreeLibrary(plugin.handle);
		}
		MP_CORE_RESET_INDENT();
	}
	MP_CORE_RESET_INDENT();
}

/**
 *@brief Releases the the plugins in the given list and calls the release function of each.
 *
 *@param plugins The list of plugins to release.
*/
void releasePlugins(std::vector<macropad::plugin::mp_plugin>& plugins) {
	TIMING_FUNCTION();
	for (auto& plugin : plugins) {
		TIMING_SCOPE("releasing " + plugin.name);
		MP_CORE_INDENT();
		MP_CORE_TRACE("Freeing: {}", plugin.name);
		if (plugin.release)
			plugin.release();
		FreeLibrary(plugin.handle);
		MP_CORE_RESET_INDENT();
	}
}