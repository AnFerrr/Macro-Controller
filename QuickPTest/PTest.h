#pragma once

#include "pluginSDK/plugin_export.h"

#include "pluginSDK/IPlugin.h"
#include "pluginSDK/APlugin.h"

NAME("Keyboard manager")
VERSION(0, 1)

class Test : public MacroPad::PluginSDK::IPlugin {
public:
	Test() {
	};
	~Test(){
	};
};

typedef MacroPad::PluginSDK::IPlugin *IPointer;

PLUGIN_DLL IPointer __stdcall Load() {
	return new Test();
}