#include "utils.h"

void StartConsole()
{
	AllocConsole();

	FILE* newstdout = stdout, * newstdin = stdin, * newsterr = stderr;

	freopen_s(&newstdout, "CONOUT$", "w", stdout);
	freopen_s(&newsterr, "CONOUT$", "w", stderr);
	freopen_s(&newstdin, "CONIN$", "r", stdin);

	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}

std::string version_to_str(const version_s& version)
{
	std::string version_str("");
	version_str = version.major + "." + version.minor;
	return version_str;
}

version_s str_to_version_s(std::string version_str)
{
	version_s version {-1, -1};
	if (!std::regex_match(version_str, std::regex("\\d+\\.\\d+"))) {
		std::cout << "String: " << version_str << " doesn't match version format" << std::endl;
		return version;
	}

	std::stringstream sstream(version_str);
	std::string item;
	int i = 0;
	int version_int[2] = {-1, -1};

	while (getline(sstream, item, '.')) {
		version_int[i] = std::stoi(item);
		i++;
	}

	version.major = version_int[0];
	version.minor = version_int[1];
	return version;
}