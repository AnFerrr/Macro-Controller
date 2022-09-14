#include "PluginSDK.h"
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <regex>
#include <fstream>

#if __cplusplus >= 201703L
#define CPP17
#else
#define CPPOLDER
#endif

#ifndef CPP17
#include <dirent.h>
#endif

#ifdef CPP17
namespace fs = std::filesystem;
#endif

namespace PluginSDK {

	PluginManager::PluginManager() {
		pluginsDir = "I:\\Users\\Antoine\\source\\repos\\MacroPad\\x64\\Debug";
	}

	PluginManager::~PluginManager() {}

	bool isDLL(std::string filename) {
		return std::regex_match(filename, std::regex(".+\\.dll"));
	}

#ifdef CPP17
	std::vector<string> PluginManager::ListPluginsInDirectory() {
		std::vector<string> plugins;
		string path = pluginsDir;
		for (const auto& entry : fs::directory_iterator(path))
			if (isDLL(entry.path().filename().string()))
				plugins.push_back(entry.path().string());
		return plugins;
	}
#else
	std::vector<string> PluginManager::ListPluginsInDirectory() {
		DIR *dir; struct dirent *diread;
		std::vector<string> plugins;
		string path = pluginsDir;

		if ((dir = opendir(pluginsDir.c_str())) != nullptr) {
        	while ((diread = readdir(dir)) != nullptr) {
        		path = pluginsDir + "/" + diread->d_name;
            	plugins.push_back(path);
        	}
        	closedir (dir);
    	} else {
        	perror ("opendir");
	    }
		return plugins;
	}
#endif

	void PluginManager::LoadPlugins() {
		std::vector<std::string> plugin_list = ListPluginsInDirectory();
		for (auto& plugin : plugin_list) {
			HINSTANCE handle = LoadLibraryA(plugin.c_str());
			register_plugin regPlug = (register_plugin)GetProcAddress(handle, "Register");
			if (regPlug)
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