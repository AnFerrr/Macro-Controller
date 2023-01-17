#pragma once

#include <memory>
#include <vector>

#include <string>
#include <iostream>
#include <sstream>
#include <string_view>

#include <regex>

#include <algorithm>
#include <stdexcept>

#define WIN32_LEAN_AND_MEAN // Allows for a lighter windows.h
#include <windows.h>

#if defined(__linux__)
#define LINUX_COMP 1
#define WINDOWS_COMP 0
#elif _WIN32
#define WINDOWS_COMP 1
#define LINUX_COMP 0
#endif