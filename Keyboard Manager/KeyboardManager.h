#pragma once

#define PLUGIN_EXPORT

#include <PluginSDK.h>
#include <map>
#include <fstream>
#include <PluginManager.h>

enum keyIDs {
	KEYONE,
	KEYTWO,
	KEYTHREE,
	KEYFOUR,
	KEYFIVE,
	KEYSIX
};

typedef void (*funct)(); 

class KeyboardManager :
	public PluginSDK::Plugin
{
public:
	KeyboardManager(){
		name_ = "Keyboard Manager";
		plugin_version_ = {0, 1};
	};
	~KeyboardManager() = default;

	int BindKey(keyIDs key);
	void Update() {
		/*if (GetKeyState(0x42) & 0x8000) {
			std::cout << "i don\'t know why but i wanna do this\n";
		}*/
	};

private:
	std::map<keyIDs, funct> key_binds_;
};

PLUGIN_SDK void _stdcall Register(PluginManager& pm);