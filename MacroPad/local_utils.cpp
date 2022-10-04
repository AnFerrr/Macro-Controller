#include "local_utils.h"

#include <iostream>
#include <windows.h>
#include "benchmark/Benchmark.h"

void StartConsole()
{
	PROFILE_FUNCTION;
	AllocConsole();

	FILE* newstdout = stdout, * newstdin = stdin, * newsterr = stderr;

	freopen_s(&newstdout, "CONOUT$", "w", stdout);
	freopen_s(&newsterr, "CONOUT$", "w", stderr);
	freopen_s(&newstdin, "CONIN$", "r", stdin);

	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}