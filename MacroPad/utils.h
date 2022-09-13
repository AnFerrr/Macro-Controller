#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

enum outputs {
	OStream1 = 0x01,
	OStream2 = 0x02,
	OFstream = 0x04
};

typedef unsigned char LoggerOutputFlags;

class OStreamManager {
public:
	OStreamManager(std::ostream& os1, std::ostream& os2, LoggerOutputFlags output_flags = 0x03) :
		os1_(os1), os2_(os2), ofs_(nullptr), output_flags(output_flags) {};
	OStreamManager(std::ostream& os1, std::ofstream& ofs, LoggerOutputFlags output_flags = 0x03) :
		os1_(os1), os2_(std::cerr), ofs_(&ofs), output_flags(0x03) {};
	OStreamManager(LoggerOutputFlags output_flags = 0x03) :
		os1_(std::cout), os2_(std::cerr), ofs_(nullptr), output_flags(0x3) {};

	LoggerOutputFlags output_flags;

	template<class T>
	OStreamManager& operator<<(const T& x) {
		UpdateTime();
		if (output_flags & OStream1) os1_ << std::put_time(&tm, "%T   %F") << x;
		if (output_flags & OStream2) os2_ << std::put_time(&tm, "%T   %F") << x;
		if (output_flags & OFstream) *ofs_ << std::put_time(&tm, "%T   %F") << x;
		return *this;
	}

	OStreamManager& operator<<(std::ostream& (*os)(std::ostream&));

	void UpdateTime();

private:
	std::tm tm;
	std::time_t time;

	std::ostream& os1_;
	std::ostream& os2_;
	std::ofstream* ofs_; // Pointer is not owned. DO NOT DELETE
};

void StartConsole();