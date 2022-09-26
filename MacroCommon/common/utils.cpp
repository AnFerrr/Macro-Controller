#include "utils.h"

#include <regex>
#include <sstream>

std::string version_to_str(const s_version& version)
{
	return version.major + "." + version.minor;
}

s_version str_to_version_s(std::string version_str)
{
	s_version version{ -1, -1 };
	if (!std::regex_match(version_str, std::regex("\\d+\\.\\d+")))
		return version;

	std::stringstream sstream(version_str);
	std::string item;

	int i = 0;
	int version_int[2] = { -1, -1 };

	while (getline(sstream, item, '.')) {
		version_int[i] = std::stoi(item);
		i++;
	}

	version.major = version_int[0];
	version.minor = version_int[1];

	return version;
}