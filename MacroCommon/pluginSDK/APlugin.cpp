#include <string>
#include "common/utils.h"
#include "SDK_version.h"
#include "APlugin.h"

namespace MacroPad {
	namespace PluginSDK {
		std::string APlugin::GetName() const
		{
			return m_name_;
		};

		s_version APlugin::GetVersion() const
		{
			return version_from_str(m_version_.c_str());
		};
		std::string APlugin::GetVersionStr() const
		{
			return m_version_;
		};

		s_version APlugin::GetSDKVersion() const
		{
			return version_from_str(SDK_VERSION);
		};
		std::string APlugin::GetSDKVersionStr() const
		{
			return SDK_VERSION;
		};

		void APlugin::OnLoad() {};
		void APlugin::OnInit() {};

		void APlugin::OnUpdate() {};

		void APlugin::OnUnload() {};
		void APlugin::OnRelease() {};
	}
}
