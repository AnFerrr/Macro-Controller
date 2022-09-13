#define PLUGIN_EXPORT

#include "PluginSDK.h"
#include <iostream>

namespace PluginSDK {
	std::string IPlugin::GetSDKVersion() const {
		return SDK_VERSION;
	}

	PluginPointer& PluginManager::GetPlugin(std::string name) {
		for (auto& plugin : plugins) {
			if (name == plugin->GetName())
				return plugin;
		}
	}
}