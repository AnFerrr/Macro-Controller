#pragma once

#include <string>

#include "pluginSDK/IPlugin.h"
#include "common/utils.h"

namespace MacroPad{
	namespace PluginSDK {
		class APlugin : public IPlugin
		{
		public:
			virtual ~APlugin() = default;

			virtual std::string GetName() const;

			virtual s_version GetVersion() const;
			virtual std::string GetVersionStr() const;

			virtual s_version GetSDKVersion() const;
			virtual std::string GetSDKVersionStr() const;

		private:
			std::string m_name_ = "";
			const s_version m_version_{ -1, -1 };
			const s_version m_sdk_version_{ -1, -1 };
		};
	}
}