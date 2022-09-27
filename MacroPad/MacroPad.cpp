#ifndef UNICODE
#define UNICODE
#endif 

#include "MacroPad.h"
#include "OStreamManager.h"

#include "pluginSDK/APlugin.h"
#include "pluginSDK/IPlugin.h"

bool g_ApplicationRunning = true;

namespace MacroPad {
	void Main(int argc, char** argv) {
		while(g_ApplicationRunning) {
			std::cout << "Allows the app to quick reboot" << std::endl;
		}
	}
};

typedef MacroPad::PluginSDK::IPlugin *IPointer;
typedef IPointer (__stdcall *LoadPTR)();

#define NO_CONSOLE
#ifdef NO_CONSOLE
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	StartConsole();
	OStreamManager stream_manager(std::cout, "MacroDebug.out");
	//PluginManager pm;
	//pm.LoadPlugins();
	//std::cout << pm.GetPluginList() << std::endl;
	HMODULE handle = LoadLibrary(L"QuickPTest.dll");
	if (!handle) {
		std::cout << "ma gueule" << std::endl;
		return -1;
		system("pause");
	}
	LoadPTR Load = (LoadPTR)GetProcAddress(handle, "Load");
	if (!Load) {
		std::cout << "No Load" << std::endl;
		system("pause");
		return -1;
	}
	IPointer plugin = Load();
	system("pause");
	return 0;
}
#else
int main () {
	
};
#endif


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

// TODO : Give PM to Keyboardmanager to get access to action manager  