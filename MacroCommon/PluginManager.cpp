#define PLUGIN_EXPORT

#include "PluginManager.h"

PLUGIN_SDK int __stdcall return_int(int a)
{
	return a + 42;
}

PLUGIN_SDK Test* __stdcall return_test()
{
	return new Test();
}