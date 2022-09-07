#include "PluginSDK.h"
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <regex>
#include <fstream>

namespace fs = std::filesystem;

namespace PluginSDK {

	PluginManager::PluginManager() {
		pluginsDir = "I:\\Users\\Antoine\\source\\repos\\MacroPad\\x64\\Debug";
	}

	PluginManager::~PluginManager() {}

	bool isDLL(std::filesystem::directory_entry entry) {
		return std::regex_match(entry.path().filename().string(),
			std::regex(".+\\.dll"));
	}

	std::vector<string> PluginManager::ListPluginsInDirectory() {
		std::vector<string> plugins;
		string path = pluginsDir;
		for (const auto& entry : fs::directory_iterator(path))
			if (isDLL(entry))
				plugins.push_back(entry.path().string());
		return plugins;
	}

	void PluginManager::LoadPlugins() {
		std::vector<std::string> plugin_list = ListPluginsInDirectory();
		for (auto& plugin : plugin_list) {
			HINSTANCE handle = LoadLibraryA(plugin.c_str());
			register_plugin regPlug = (register_plugin)GetProcAddress(handle, "Register");
			regPlug(*this);
		}
	}

	void PluginManager::RegisterGenericPlugin(PluginPointer plugin) {
		this->plugins.push_back(std::move(plugin));
	}

	std::string PluginManager::GetPluginList() {
		std::string pluginList;

		for (auto& plugin : this->plugins) {
			pluginList += "---" + plugin.get()->GetName() + "\n";
			pluginList += "SDK version: " + plugin.get()->GetSDKVersion() + "\n";
			pluginList += "----------------------------------";
			pluginList += "\n";
		}

		return pluginList;
	}
}