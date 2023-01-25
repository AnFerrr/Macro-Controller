#pragma once

#include <memory>
#include <vector>
#include <string>

#include <regex>

#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>

#include <chrono>

#include <thread>
#include <mutex>

#include <algorithm>
#include <stdexcept>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN // Allows for a lighter windows.h
#include <windows.h>
#endif

#include <filesystem>
