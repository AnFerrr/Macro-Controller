#pragma once

#include <string>

#include "common/utils.h"

namespace MacroPad{
	namespace PluginSDK {
		class IPlugin
		{
		public:
			virtual ~IPlugin() = default;

			virtual std::string GetName() const = 0;

			virtual s_version GetVersion() const = 0;
			virtual std::string GetVersionStr() const = 0;

			virtual s_version GetSDKVersion() const = 0;
			virtual std::string GetSDKVersionStr() const = 0;

			virtual void OnLoad() {};
			virtual void OnInit() {};
			virtual void OnUnload() {};
			virtual void OnRelease() {};
		};
	}
}