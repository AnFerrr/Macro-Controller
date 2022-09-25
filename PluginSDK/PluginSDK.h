#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../MacroPad/utils.h"

#ifdef PLUGIN_EXPORT
#define PLUGIN_SDK extern "C" __declspec(dllexport)
#else
#define PLUGIN_SDK extern "C" __declspec(dllimport)
#endif

#define SDK_VERSION "0.1"

namespace PluginSDK {
	/**
	 * @brief Plugin interface. Is used to allow for polymorphism
	 * and compatibility between main program and DLLs,
	 * across compilers.
	*/
	class IPlugin {
	public: 
		virtual ~IPlugin() = default;

		/**
		 * @brief Returns the current version of the plugin.
		 * @return The current version of the plugin.
		*/
		virtual version_s GetVersion() const = 0;
		virtual std::string GetVersionStr() const = 0;

		/**
		 * @brief Returns the name of the plugin.
		 * @return The name of the plugin.
		*/
		virtual std::string GetName() const = 0;

		/**
		 * @brief Returns the version of the SDK used to compile this
		 * plugin.
		 * @return The version of the SDK used to compile this
		 * plugin.
		*/
		virtual version_s GetSDKVersion() const = 0;
		virtual std::string GetSDKVersionStr() const = 0;

		virtual void OnLoad(){};
		virtual void OnInit(){};
		virtual void OnUnload(){};
		virtual void OnRelease(){};
		// TODO : static PluginMangaer& instance; ?
	};

	class Plugin : public IPlugin {
	public:
		virtual ~Plugin() = default;

		virtual version_s GetVersion() const;
		virtual std::string GetVersionStr() const;
		virtual std::string GetName() const;
		virtual version_s GetSDKVersion() const;
		virtual std::string GetSDKVersionStr() const;

		std::string name_ = "";
		version_s plugin_version_{ -1, -1};
		version_s sdk_version_{ -1, -1 };
	};

	typedef std::shared_ptr<IPlugin> PluginPointer;
	typedef std::vector<PluginPointer> PluginList;
}

// TODO : complete Macro to simplify registering for end devs
// TODO : System tray notification mode
// TODO : Main process + window process