#pragma once

#include <string>

#include "common/utils.h"

namespace MacroPad{
	namespace PluginSDK {
		/**
		 * @brief Plugin interface. Is used to allow for plugin polymorphism
		 * and compatibility between main program and DLLs,
		 * across compilers.
		*/
		class IPlugin
		{
		public:
			virtual ~IPlugin() = default;

			/**
			 * @brief Returns the name of the plugin.
			 * @return The name of the plugin.
			*/
			virtual std::string GetName() const = 0;
	
			/**
			 * @brief Returns the current version of the plugin.
			 * @return The current version of the plugin.
			*/
			virtual s_version GetVersion() const = 0;
			virtual std::string GetVersionStr() const = 0;

			/**
			 * @brief Returns the version of the SDK used to compile the
			 * plugin.
			*/
			virtual s_version GetSDKVersion() const = 0;
			virtual std::string GetSDKVersionStr() const = 0;

			virtual void OnLoad() = 0;
			virtual void OnInit() = 0;
			virtual void OnUnload() = 0;
			virtual void OnRelease() = 0;
		};
	}
}

// TODO : complete Macro to simplify registering for end devs