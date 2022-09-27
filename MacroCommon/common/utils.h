#pragma once

#include <string>
#include "core_export.h"

struct s_version {
	int major;
	int minor;
};

CORE_DLL std::string __stdcall version_to_str(const s_version& version);
CORE_DLL s_version __stdcall str_to_version(const std::string version_str);

// TODO : System tray notification mode
// TODO : Main process + window process