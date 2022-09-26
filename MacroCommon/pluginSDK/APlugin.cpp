#include "APlugin.h"

#include "common/utils.h"

namespace MacroPad {
	namespace PluginSDK {
		std::string APlugin::GetName() const
		{
			return m_name_;
		}
		s_version APlugin::GetVersion() const
		{
			return m_version_;
		}
		std::string APlugin::GetVersionStr() const
		{
			return version_s_to_str(sdk_version_);
		}
	}
}

s_version MacroPad::PluginSDK::APlugin::GetSDKVersion() const
{
	return m_sdk_version_;
}
std::string MacroPad::PluginSDK::APlugin::GetSDKVersionStr() const
{
	return version_s_to_str(sdk_version_);
}