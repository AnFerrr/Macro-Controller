#pragma once

#include "pluginSDK/plugin_export.h"

#include "pluginSDK/PluginSDK.h"

import APlugin;

class Test : public MacroPad::PluginSDK::APlugin {
public:
	Test() {};
	~Test() {};
};

PLUGIN_DLL PluginPointer __stdcall Load() {
	return new Test();
}
