#include "utils.h"

OStreamManager& OStreamManager::operator<<(std::ostream& (*os)(std::ostream&))
{
	if (output_flags & OStream1) os1_ << os;
	if (output_flags & OStream2) os2_ << os;
	if (output_flags & OFStream) ofs_ << os;
	return *this;
}

void OStreamManager::UpdateTime() {
	time = std::time(nullptr);
	localtime_s(&tm, &time);
}

void OStreamManager::LogTime() {
	UpdateTime();
	if (output_flags & OStream1) os1_ << std::put_time(&tm, TIME_FORMAT_STRING);
	if (output_flags & OStream2) os2_ << std::put_time(&tm, TIME_FORMAT_STRING);
	if (output_flags & OFStream) ofs_ << std::put_time(&tm, TIME_FORMAT_STRING);
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