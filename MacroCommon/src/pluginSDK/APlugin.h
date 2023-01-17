#pragma once

#include <string>

#include "common/utils.h"
#include "IPlugin.h"

#include "SDK_version.h"
#include "SDK_export.h"

// TODO : This shit causes issues when compiling core because NAME() is never called;
#define NAME(name) #name;
#define VERSION(version) #version;

namespace MacroPad{
	namespace PluginSDK {
		class __declspec(dllexport) APlugin : public IPlugin
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
#pragma warning(suppress: 4251) //m_name_ is only accessed through methods
			std::string m_name_;
#pragma warning(suppress: 4251) //m_version_ is only accessed through methods
			std::string m_version_;

			// TODO : static PluginMangaer& instance; ?
		};
	}
}