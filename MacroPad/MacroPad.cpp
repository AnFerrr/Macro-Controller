#ifndef UNICODE
#define UNICODE
#endif 

#include "MacroPad.h"
#include "utils.h"

OStreamManager SetupLogger{
	std::ofstream file;
	file.open("out.debug");
	OStreamManager sm(std::cout, file);
	sm.output_flags = OStream1;

	std::cout << "" << "Initilizing plugin manager..." << std::endl;
	
	file.close();
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	StartConsole();

	PluginSDK::PluginManager pm;
	pm.LoadPlugins();
	system("pause");
	return 0;
}


// TODO : Logger initialization
// TODO : cout << time
// TODO : Debug
// TODO : Unit tests
// TODO : Exceptions
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
//system("pause");