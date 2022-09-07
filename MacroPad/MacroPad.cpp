#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>
#include <fstream>
#include "tchar.h"
#include <WinUser.h>

#include "PluginSDK.h"
#include <cstdio>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    
    PluginSDK::PluginManager pm;
    pm.LoadPlugins();


    AllocConsole();
    FILE* newstdout = nullptr;
    freopen_s(&newstdout, "CONOUT$", "w", stdout);
    std::cout.clear();

    std::ofstream file;
    file.open("out.debug");
    file << "uh?" << std::endl;
    file << pm.GetPluginList();
    file.close();
    //::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    //pm.StartUI();
    system("pause");
}