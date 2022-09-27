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
			virtual std::string GetName() const {};
	
			/**
			 * @brief Returns the current version of the plugin.
			 * @return The current version of the plugin.
			*/
			virtual s_version GetVersion() const {};
			virtual std::string GetVersionStr() const {};

			/**
			 * @brief Returns the version of the SDK used to compile the
			 * plugin.
			*/
			virtual s_version GetSDKVersion() const {};
			virtual std::string GetSDKVersionStr() const {};

			virtual void OnLoad() {};
			virtual void OnInit() {};
			virtual void OnUnload() {};
			virtual void OnRelease() {};
		};
	}
}

// TODO : complete Macro to simplify registering for end devs