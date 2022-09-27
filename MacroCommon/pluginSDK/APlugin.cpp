#define CORE_EXPORT

#include "APlugin.h"

#include "common/utils.h"
#include "pluginSDK/SDK_version.h"

namespace MacroPad {
	namespace PluginSDK {
		std::string APlugin::GetName() const
		{
			return m_name_;
		}
		s_version APlugin::GetVersion() const
		{
			return m_version_;s
		}
		std::string APlugin::GetVersionStr() const
		{
			return version_to_str(m_version_);
		}
		s_version APlugin::GetSDKVersion() const
		{
			return m_sdk_version_;
		}
		std::string APlugin::GetSDKVersionStr() const
		{
			return version_to_str(m_sdk_version_);
		}
		void APlugin::OnInit()
		{
			m_sdk_version_ = str_to_version(SDK_VERSION);
		}
	}
}
