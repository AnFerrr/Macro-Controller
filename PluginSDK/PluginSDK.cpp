#define PLUGIN_EXPORT

#include "PluginSDK.h"
#include <iostream>

namespace PluginSDK {
	version_s Plugin::GetVersion() const
	{
		return plugin_version_;
	}
	std::string Plugin::GetVersionStr() const
	{
		return version_s_to_str(sdk_version_);
	}
	std::string Plugin::GetName() const
	{
		return name_;
	}
	version_s Plugin::GetSDKVersion() const
	{
		return sdk_version_;
	}
	std::string Plugin::GetSDKVersionStr() const
	{
		return version_s_to_str(sdk_version_);
	}
}