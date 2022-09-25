#pragma once

#include <regex>
#include "../PluginSDK/PluginSDK.h"

typedef std::shared_ptr<PluginSDK::IPlugin> PluginPointer;
typedef std::vector<PluginPointer> PluginList;

/**
	* @brief This object is used to manage plugins. Loading them, storing
	*			them, calling them and so on.
*/
class PluginManager {
public:
	PluginManager();
	~PluginManager();

	/**
	 * @brief Returns a list of the loaded and initialized plugins
	 * @return
	*/
	std::vector<std::string> ListPluginsInDirectory();

	/**
	 * @brief Registers a plugin in the plugin manager
	 * Is called by the plugin being loaded.
	 * @param plugin Plugin to be registered.
	*/
	void RegisterGenericPlugin(PluginPointer plugin);

	/**
	 * @brief Loads and initializes plugins in the plugin directory
	*/
	void LoadPlugins();

	/**
	 * @brief Sets plugin in the manager's memory. Is called during plugin loading
	 *
	 * @param plugin Unique_ptr to the plugin to put in the manager.
	*/
	std::string GetPluginList();

	PluginPointer& GetPlugin(std::string name);

private:
	/**
	 * @brief Loaded plugins.
	*/
	PluginList plugins;

	/**
	 * @brief Current plugins location
	*/
	std::string pluginsDir;
	// TODO : static PluginManager& instance ? + GetPm() ?
};

typedef void(_stdcall* register_plugin)(PluginManager& pm);
//PLUGIN_SDK void _stdcall Register(PluginManager& pm);
