module;

#define CORE_EXPORT

#include <string>
#include "common/utils.h"
#include "pluginSDK/SDK_version.h"

module APlugin;

namespace MacroPad {
	namespace PluginSDK {
		std::string APlugin::GetName() const
		{
			return m_name;
		};

		s_version APlugin::GetVersion() const
		{
			return version_from_str(m_version.c_str());
		};
		std::string APlugin::GetVersionStr() const
		{
			return m_version;
		};

		s_version APlugin::GetSDKVersion() const
		{
			return version_from_str(SDK_VERSION);
		};
		std::string APlugin::GetSDKVersionStr() const
		{
			return SDK_VERSION;
		};

		void OnLoad() {};
		void OnInit() {};

		void OnUpdate() {};

		void OnUnload() {};
		void OnRelease() {};
	}
}
