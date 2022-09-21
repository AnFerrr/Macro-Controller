#pragma once

#ifdef PLUGIN_EXPORT
#define PLUGIN_SDK extern "C" __declspec(dllexport)
#else
#define PLUGIN_SDK extern "C" __declspec(dllimport)
#endif

// Version of the SDK. Used to check for compatibility with main
// software
#define SDK_VERSION "0.0.1"

#include <string>
#include <vector>
#include <memory>
#include <windows.h>

using string = std::string;

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
		virtual std::string GetVersion() const = 0;

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
		std::string GetSDKVersion() const;

		virtual int StartUI() = 0;

		virtual void OnLoad(){};
		virtual void OnInit(){};
		virtual void OnUnload(){};
		virtual void OnRelease(){};
		// TODO : static PluginMangaer& instance; ?
	};

	typedef std::shared_ptr<IPlugin> PluginPointer;
	typedef std::vector<PluginPointer> PluginList;

	/**
	 * @brief This object is used to manage plugins. Loading them, storing
	 *			them, calling them and so on.
	*/
	class PluginManager {
	public:
		PluginManager();
		~PluginManager();

		/**
		 * @brief Returns a list of the loaded and initialized plugins
		 * @return 
		*/
		std::vector<std::string> ListPluginsInDirectory();
		
		/**
		 * @brief Registers a plugin in the plugin manager
		 * Is called by the plugin being loaded.
		 * @param plugin Plugin to be registered.
		*/
		void RegisterGenericPlugin(PluginPointer plugin);
		
		/**
		 * @brief Loads and initializes plugins in the plugin directory
		*/
		void LoadPlugins();

		/**
		 * @brief Sets plugin in the manager's memory. Is called during plugin loading
		 *
		 * @param plugin Unique_ptr to the plugin to put in the manager.
		*/
		std::string GetPluginList();

		PluginPointer& GetPlugin(std::string name);

		void StartUI() {
			plugins[0].get()->StartUI();
		}

	private:
		/**
		 * @brief Loaded plugins.
		*/
		PluginList plugins;

		/**
		 * @brief Current plugins location
		*/
		std::string pluginsDir;
		// TODO : static PluginManager& instance ? + GetPm() ?
	};

	typedef void (_stdcall *register_plugin)(PluginManager& pm);
	PLUGIN_SDK void _stdcall Register(PluginManager& pm);
}


// TODO : complete Macro to simplify registering for end devs
// TODO : System tray notification mode
// TODO : Main process + windows process