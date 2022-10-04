#pragma once

enum outputs {
	OStream1 = 0x01, // Is used to select Output Stream one
	OStream2 = 0x02, // Is used to select Output Stream two
	OFStream = 0x04 // Is used to select the Output File Stream
}; // Enum of the flags used by OStreamMangaer to select which output to write to

void StartConsole();

#define TIME_FORMAT_STRING "%c : \t"
#define TIME_MARGIN "\t\t\t"