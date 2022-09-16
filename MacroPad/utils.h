#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <stdexcept>

#ifdef CPP11
#define TIME_FORMAT_STRING "%T   %F :  "
#else
#define TIME_FORMAT_STRING "%c :  "
#endif

enum outputs {
	OStream1 = 0x01,
	OStream2 = 0x02,
	OFStream = 0x04
};

typedef unsigned char LoggerOutputFlags;

class OStreamManager {
public:
	void UpdateTime();

	OStreamManager(std::ostream& os1, std::ostream& os2, const LoggerOutputFlags flags = OStream1 | OStream2) :
		os1_(os1), os2_(os2),
		output_flags(flags),
		defined_ouputs_(OStream1 | OStream2) {
			UpdateTime();
	};

	OStreamManager(std::ostream& os1, std::string const & filename, LoggerOutputFlags flags = OStream1 | OFStream) :
		os1_(os1), os2_(std::cerr), ofs_(filename.c_str(), std::ios::out),
		output_flags(flags),
		defined_ouputs_(OStream1 | OFStream) {
			UpdateTime();
	};

	OStreamManager(LoggerOutputFlags flags = OStream1 | OStream2) :
		os1_(std::cout), os2_(std::cerr),
		output_flags(flags),
		defined_ouputs_(OStream1 | OStream2) {
			UpdateTime();
	};

	LoggerOutputFlags output_flags;

	template<class T>
	OStreamManager& operator<<(const T& x) {
		if ((output_flags & (output_flags + 1)) != 0)
			throw std::invalid_argument("Manager set to write to file even though none have been open.");
		if (output_flags & OStream1) os1_ << x;
		if (output_flags & OStream2) os2_ << x;
		if (output_flags & OFStream) ofs_ << x;
		return *this;
	}

	OStreamManager& operator<<(std::ostream& (*os)(std::ostream&));

	void LogTime();

private:
	std::tm tm;
	std::time_t time;

	std::ostream& os1_;
	std::ostream& os2_;
	std::ofstream ofs_;

	LoggerOutputFlags defined_ouputs_;
};

void StartConsole();