#pragma once

#define PLUGIN_EXPORT

#include <PluginSDK.h>

class UIPlugin : public PluginSDK::IPlugin {
public: 
    UIPlugin();
    ~UIPlugin();

    std::string GetVersion() const;
    std::string GetName() const;

    int StartUI();

private:
    std::string name_;
    std::string version_;
};