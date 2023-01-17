#pragma once

#include <string>
#include "core_export.h"

struct s_version {
	int major;
	int minor;
};

__declspec(dllexport) s_version __stdcall version_from_str(const char* version_str);

// TODO : System tray notification mode
// TODO : Main process + window process