#pragma once

#include <string>

#include "common/utils.h"
#include "IPlugin.h"

#define NAME(name) const std::string g_name = name;
#define VERSION(major, minor) const s_version g_version{major, minor};

namespace MacroPad{
	namespace PluginSDK {
		class APlugin : public IPlugin
		{
		public:
			virtual ~APlugin() = default;

			virtual std::string APlugin::GetName() const { return m_name_; };

			virtual s_version APlugin::GetVersion() const { return m_version_; };
			virtual std::string APlugin::GetVersionStr() const { return version_to_str(m_version_); };

			virtual s_version APlugin::GetSDKVersion() const { return m_sdk_version_; };
			virtual std::string APlugin::GetSDKVersionStr() const { return version_to_str(m_sdk_version_); };

			virtual void APlugin::OnInit() { m_sdk_version_ = str_to_version(SDK_VERSION); };

		private:
			std::string m_name_ = "";
			s_version m_version_{ -1, -1 };
			s_version m_sdk_version_{ -1, -1 };
			// TODO : static PluginMangaer& instance; ?
		};
	}
}
