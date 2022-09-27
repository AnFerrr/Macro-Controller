#pragma once

#include <string>

#include "common/utils.h"
#define NAME(name) const std::string g_name = name;
#define VERSION(major, minor) const s_version g_version{major, minor};


//#include "IPlugin.h"
//namespace MacroPad{
//	namespace PluginSDK {
//		class APlugin : public IPlugin
//		{
//		public:
//			virtual ~APlugin() = default;
//
//			virtual std::string GetName() const;
//
//			virtual s_version GetVersion() const;
//			virtual std::string GetVersionStr() const;
//
//			virtual s_version GetSDKVersion() const;
//			virtual std::string GetSDKVersionStr() const;
//
//			virtual void OnInit();
//
//		private:
//			std::string m_name_ = "";
//			s_version m_version_{ -1, -1 };
//			s_version m_sdk_version_{ -1, -1 };
//			// TODO : static PluginMangaer& instance; ?
//		};
//	}
//}
