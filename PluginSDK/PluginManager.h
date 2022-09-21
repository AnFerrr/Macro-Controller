#pragma once

#include "PluginSDK.h"

using string = std::string;

namespace PluginSDK {
	/**
	 * @brief This object is used to manage plugins. Loading them, storing 
	 *			them, calling them and so on.
	*/
	class PluginManager {
	public:
		PluginManager();
		~PluginManager();
		std::vector<std::string> ListPluginsInDirectory();
		void LoadPlugins();

		void RegisterGenericPlugin(PluginPointer plugin);
	private:
		// static PluginManager& instance ? + GetPm() ?
		PluginList plugins;
		std::string pluginsDir = "\\Plugins";
	};
}