#define CORE_EXPORT

#include "common/utils.h"
#include "common/core_export.h"

#include <regex>
#include <sstream>

CORE_DLL s_version __stdcall version_from_str(const char* version_str)
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