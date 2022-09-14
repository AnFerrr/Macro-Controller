#include "utils.h"

OStreamManager& OStreamManager::operator<<(std::ostream& (*os)(std::ostream&))
{
	UpdateTime();
	if (output_flags & OStream1) os1_ << std::put_time(&tm, "%T   %F") << os;
	if (output_flags & OStream2) os2_ << std::put_time(&tm, "%T   %F") << os;
	if (output_flags & OFstream) ofs_ << std::put_time(&tm, "%T   %F") << os;
	return *this;
}

void OStreamManager::UpdateTime() {
	time = std::time(nullptr);
	localtime_s(&tm, &time);
}

void StartConsole() {
	AllocConsole();
	FILE* newstdout = stdout, * newstdin = stdin, * newsterr = stderr;

	freopen_s(&newstdout, "CONOUT$", "w", stdout);
	freopen_s(&newsterr, "CONOUT$", "w", stderr);
	freopen_s(&newstdin, "CONIN$", "r", stdin);

	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}