#define PLUGIN_EXPORT

#include "PluginSDK.h"

namespace PluginSDK {
	std::string IPlugin::GetSDKVersion() const {
		return SDK_VERSION;
	}
}