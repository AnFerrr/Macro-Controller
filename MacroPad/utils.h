#pragma once

#include <iostream>
#include <windows.h>
#include <regex>
#include <sstream>


#define TIME_FORMAT_STRING "%c :  "
#define TIME_MARGIN "\t\t     "

enum outputs {
	OStream1 = 0x01, // Is used to select Output Stream one
	OStream2 = 0x02, // Is used to select Output Stream two
	OFStream = 0x04 // Is used to select the Output File Stream
}; // Enum of the flags used by OStreamMangaer to select which output to write to

struct version_s {
	int major;
	int minor;
};

void StartConsole();

std::string version_s_to_str(const version_s& version);
version_s str_to_version_s(std::string version_str);