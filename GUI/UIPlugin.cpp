#include "UIPlugin.h"

UIPlugin::UIPlugin()
{
}

UIPlugin::~UIPlugin()
{
}

std::string UIPlugin::GetVersion() const
{
	return plugin_version_;
}

std::string UIPlugin::GetName() const
{
	return name_;
}

PLUGIN_SDK void _stdcall Register(PluginSDK::PluginManager& pm)
{
	PluginSDK::PluginPointer instance(new UIPlugin);
	pm.RegisterGenericPlugin(std::move(instance));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int UIPlugin::StartUI() {
    WNDCLASS windowClass = { 0 };
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = L"Window in Console";
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    if (!RegisterClass(&windowClass))
        MessageBox(NULL, L"Could not register class", L"Error", MB_OK);
    HWND windowHandle = CreateWindow(L"Window in Console",
        L"Window name",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME |
            WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        0,
        0,
        500,
        500,
        NULL,
        NULL,
        NULL,
        NULL);
    ShowWindow(windowHandle, SW_RESTORE);
    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0) > 0)
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    DeleteObject(windowHandle); //doing it just in case
    return messages.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_CHAR: //this is just for a program exit besides window's borders/taskbar
        if (wparam == VK_ESCAPE)
        {
            DestroyWindow(hwnd);
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
}