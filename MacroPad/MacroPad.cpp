#ifndef UNICODE
#define UNICODE
#endif 

#include "MacroPad.h"
#include "utils.h"

OStreamManager StartLogger(){
	std::string file("debug.out");
	OStreamManager sm(std::cout, std::cerr, OStream1 | OStream2);

	system("pause");
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	StartConsole();
	StartLogger();

	PluginSDK::PluginManager pm;
	pm.LoadPlugins();
	system("pause");
	return 0;
}

// TODO : Time format string
// TODO : cout << time
// TODO : Macro CPP version guard
// TODO : Logger initialization
// TODO : Fix not all control paths return a value "bool function(string name, PluginPointer& pp)", "Maybe<T> function(string name)" or exceptions
// TODO : Exceptions
// TODO : Debug
// TODO : Unit tests
// TODO : Better plugins
// TODO : Template
// TODO : Ardoise

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
