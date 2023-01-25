#include <iostream>

#include <MacroPadCommons.h>
#include <Log/Log.h>

#include "Application.h"

extern bool g_ApplicationRunning;

MacroPad::Application::Application()
{
}

MacroPad::Application::~Application()
{
}

//void LoadDLL()
//{
//	HINSTANCE hm = LoadLibraryA("DevSandbox.dll");
//	if (!hm) {
//		MP_CORE_ERROR("DLL Couldn't be loaded! Aborting...");
//		return;
//	}
//
//	void (*remoteLog)() = (void (*)())GetProcAddress(hm, "RemoteLog");
//	if (remoteLog)
//		remoteLog();
//	else
//		MP_CORE_ERROR("RemoteLog Couldn't be fetched! Aborting...");
//
//	FreeLibrary(hm);
//}

// Make singleton to access important data everywhere

// ------- TEMP -----------------------------------------------------
//#include "Events/Event.h"
//#include "Events/KeyEvent.h"
// ------------------------------------------------------------------
//void OnEvent(MacroPad::Event& event)
//{
//	if (event.GetEventType() == MacroPad::EventType::KeyPressed)
//	{
//		MacroPad::KeyPressedEvent& e = (MacroPad::KeyPressedEvent&)event;
//		if (e.GetKeyCode() == 'X')
//			MP_CORE_TRACE("Tab key is pressed (event)!");
//		MP_CORE_TRACE("{0}", (char)e.GetKeyCode());
//	}
//}

void LoadPlugins();

//void MacroPad::Application::Run()
//{
//	// ------- TEMP -----------------------------------------------------
//	MP_CORE_INFO("Waiting for keyboard input...")
//	while (!(GetKeyState('A') & 0x8000) && g_ApplicationRunning) {
//		int a = 0;
//		if ((GetKeyState(VK_ESCAPE) & 0x8000))
//			g_ApplicationRunning = false;
//		if ((GetKeyState('R') & 0x80000)) {
//			MP_CORE_INFO("Trying to load DLL");
//			//LoadDLL();
//		}
//		//if ((GetKeyState('X') & 0x8000)) {
//		//	KeyPressedEvent e('x', 0);
//		//	OnEvent(e);
//		//}
//	}
//	// ------------------------------------------------------------------
//}
