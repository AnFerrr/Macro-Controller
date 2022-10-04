module;

#include <string>
#include "pluginSDK/IPlugin.h"

export module APlugin;

namespace MacroPad {
	namespace PluginSDK {
		export class APlugin : public IPlugin
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