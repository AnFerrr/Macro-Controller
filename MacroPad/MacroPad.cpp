#ifndef UNICODE
#define UNICODE
#endif 

#include "MacroPad.h"
#include "utils.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	StartConsole();
	OStreamManager sm(std::cout, "MacroDebug.out");

	sm << "i don\'t know why but i wanna do this\n";

	PluginSDK::PluginManager pm;
	pm.LoadPlugins();
	system("pause");
	return 0;
}

//TODO : Debug
//TODO : Template
//TODO : Ardoise

//PluginSDK::PluginManager pm;
//pm.LoadPlugins();
//
//AllocConsole();
//FILE* newstdout = nullptr;
//freopen_s(&newstdout, "CONOUT$", "w", stdout);
//std::cout.clear();
//
//std::ofstream file;
//file.open("out.debug");
//file << "uh?" << std::endl;
//file << pm.GetPluginList();
//file.close();
////::ShowWindow(::GetConsoleWindow(), SW_SHOW);
////pm.StartUI();
//PluginSDK::PluginPointer& plugin = pm.GetPlugin("wxWidgetWrapper");
//std::cout << plugin->GetName();
