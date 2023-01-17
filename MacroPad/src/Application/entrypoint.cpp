#include "Application/Application.h"

#include <MacroPadCommons.h>
#include <log/Log.h>
#include <directory/directory.h>

bool g_ApplicationRunning = true;

namespace MacroPad {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning) {
			MP_CORE_INFO("Starting...");
			MP_CORE_TRACE("- - - - Welcome to MacroPad - - - -")
			Application app;
			app.Run();
			if (g_ApplicationRunning)
				MP_CORE_INFO("Restarting MacroPad...");
		}
		MP_CORE_INFO("Exiting MacroPad...");
		return 0;
	}
}

// Should app be heap or stack? Depending on size

#if defined MP_DIST && defined MP_PLATFORM_WINDOWS

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
	return MacroPad::Main(0, nullptr);
}

#else

#include <profiling/instrumentation_manager.h>
#include <Plugin/Plugin.h>
#include "Plugins/PluginLoader.h"

int main(int argc, char** argv)
{
	macropad::profiling::InstrumentationManager::Instance().BeginSession("Program");

	macropad::logging::Log::Init();

	std::string plugin_dir_path = "./plugin";
	std::vector<macropad::plugin::mp_plugin> plugins;

	if (macropad::directory_management::check_directory(plugin_dir_path) == -1) {
		macropad::directory_management::create_directory(plugin_dir_path);
		return -1;
	}

	loadPlugins(plugin_dir_path, plugins);
	releasePlugins(plugins);

	macropad::profiling::InstrumentationManager::Instance().EndSession();
	//return MacroPad::Main(argc, argv);
}
#endif