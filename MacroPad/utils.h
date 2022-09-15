#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

#ifdef CPP11
#define TIME_FORMAT_STRING "%T   %F :  "
#else
#define TIME_FORMAT_STRING "%c :  "
#endif

enum outputs {
	OStream1 = 0x01,
	OStream2 = 0x02,
	OFstream = 0x04
};

typedef unsigned char LoggerOutputFlags;

class OStreamManager {
public:
	void UpdateTime();

	OStreamManager(std::ostream& os1, std::ostream& os2, LoggerOutputFlags output_flags = 0x03) :
		os1_(os1), os2_(os2), output_flags(output_flags) {
			UpdateTime();
	};
	OStreamManager(std::ostream& os1, std::string const & filename, LoggerOutputFlags output_flags = 0x05) :
		os1_(os1), os2_(std::cerr), ofs_(filename.c_str(), std::ios::out), output_flags(output_flags) {
			UpdateTime();
	};
	OStreamManager(LoggerOutputFlags output_flags = 0x03) :
		os1_(std::cout), os2_(std::cerr), output_flags(output_flags) {
			UpdateTime();
	};

	LoggerOutputFlags output_flags;

	template<class T>
	OStreamManager& operator<<(const T& x) {
		UpdateTime();
		if (output_flags & OStream1) os1_ << x;
		if (output_flags & OStream2) os2_ << x;
		if (output_flags & OFstream) ofs_ << x;
		return *this;
	}

	OStreamManager& operator<<(std::ostream& (*os)(std::ostream&));

	OStreamManager& LogTime();

private:
	std::tm tm;
	std::time_t time;

	std::ostream& os1_;
	std::ostream& os2_;
	std::ofstream ofs_;
};

void StartConsole();