#pragma once

#define PLUGIN_EXPORT

#include <PluginSDK.h>

class UIPlugin :
    public PluginSDK::Plugin
{
public:
    UIPlugin();
    ~UIPlugin();

    std::string GetVersion() const;
    std::string GetName() const;

    int StartUI();
};