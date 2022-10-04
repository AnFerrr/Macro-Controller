#pragma once

#include <string>

#include "common/utils.h"
#include "pluginSDK/IPlugin.h"
#include "pluginSDK/SDK_version.h"

// TODO : This shit causes issues when compiling core because NAME() is never called;
#define NAME(name) #name;
#define VERSION(version) #version;

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

			virtual void OnLoad();
			virtual void OnInit();

			virtual void OnUpdate();

			virtual void OnUnload();
			virtual void OnRelease();

		private:
			std::string m_name;
			std::string m_version;

			// TODO : static PluginMangaer& instance; ?
		};
	}
}
