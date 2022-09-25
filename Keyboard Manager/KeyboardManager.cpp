#include "KeyboardManager.h"

PLUGIN_SDK void _stdcall Register(PluginManager& pm)
{
	PluginSDK::PluginPointer instance(new KeyboardManager);
	pm.RegisterGenericPlugin(std::move(instance));
}
