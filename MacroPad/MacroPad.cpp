#ifndef UNICODE
#define UNICODE
#endif 

#include "MacroPad.h"
#include "utils.h"
#include "OStreamManager.h"

#include "MacroCommon.h"

bool g_ApplicationRunning = true;


namespace MacroPad {
	void Main(int argc, char** argv) {
		while(g_ApplicationRunning) {
			std::cout << "Allows the app to quick reboot" << std::endl;
		}
	}
};

typedef IPTest* (__stdcall* LoadPTR)();

#define NO_CONSOLE
#ifdef NO_CONSOLE
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	StartConsole();
	OStreamManager stream_manager(std::cout, "MacroDebug.out");

	ITest* test = return_test();
	if (test)
		std::cout << test->getValue() << std::endl;

	HMODULE handle = LoadLibraryW(L"QuickPTest.dll");
	if (!handle) {
		std::cout << "No DLL Loaded..." << std::endl;
		system("pause");
		return -1;
	}

	LoadPTR Load = (LoadPTR)GetProcAddress(handle, "Load");
	if (!Load) {
		std::cout << "No Load function..." << std::endl;
		system("pause");
		return -1;
	}

	IPTest* ptest = Load();
	if (ptest) {
		std::cout << "final function(4) : " << ptest->finalFunction() << std::endl;
		std::cout << "get value(3) : " << ptest->getValue() << std::endl;
		std::cout << "something(42) : " << ptest->something(test) << std::endl;
		test->setValue(12);
		std::cout << "something(12) : " << ptest->something(test) << std::endl;
		ptest->setsomething(test, 69);
		std::cout << "setsomething(69) : " << ptest->something(test) << std::endl;
		int val = 3;
		std::cout << "val(3) : " << val << std::endl;
		ptest->setMyValue(420);
		std::cout << "getValue(420) : " << ptest->getValue() << std::endl;
		ptest->setValue(val);
		std::cout << "val(420) : " << val << std::endl;
	}
	//PluginManager pm;
	//pm.LoadPlugins();
	//std::cout << pm.GetPluginList() << std::endl;
	if (test)
		delete test;
	if (ptest)
		delete ptest;
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