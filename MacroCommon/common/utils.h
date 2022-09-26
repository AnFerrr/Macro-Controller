#pragma once

#include <string>

struct s_version {
	int major;
	int minor;
};

std::string version_to_str(const s_version& version);
s_version str_to_version(std::string version_str);