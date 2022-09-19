#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <stdexcept>

#define TIME_FORMAT_STRING "%c :  "
#define TIME_MARGIN "\t\t     "
#define DEFAULT_THROW_ON_OSM_DANGER false

enum outputs {
	OStream1 = 0x01, // Is used to select Output Stream one
	OStream2 = 0x02, // Is used to select Output Stream two
	OFStream = 0x04 // Is used to select the Output File Stream
}; // Enum of the flags used by OStreamMangaer to select which output to write to

typedef unsigned char LoggerOutputFlags; // Flags used by OStreamMangaer to select which output to write to

class OStreamManager {
//Methods ++++++++++++++++++++++++++
public:
	void UpdateTime();

	OStreamManager(
		std::ostream& os1, std::ostream& os2,
		const LoggerOutputFlags flags = OStream1 | OStream2,
		bool throw_on_danger = DEFAULT_THROW_ON_OSM_DANGER);
	OStreamManager(
		std::ostream& os1, std::string const& filename,
		LoggerOutputFlags flags = OStream1 | OFStream,
		bool throw_on_danger = DEFAULT_THROW_ON_OSM_DANGER);
	OStreamManager(
		LoggerOutputFlags flags = OStream1 | OStream2,
		bool throw_on_danger = DEFAULT_THROW_ON_OSM_DANGER);

	/**
	 * @brief Checks if the OStreamManager output scheme matches the currently defined streams
	 * @return true: when the current scheme is in line with the defined streams
	 * false: when OStreamManager is set to output to undefined streams
	*/
	bool IsOutputSchemeValid();
	/**
	 * @brief Checks if the OStreamManager output scheme matches the currently defined streams.
	 * Warns on std::cerr if the current stream is unclear.
	 * Throws an error if the Macro THROW_ON_OSM_DANGER is set to true.
	 * @return The value of IsOutputSchemeValid()
	*/
	bool TestOutputSchemeValidity();

	/**
	 * @brief Writes the time and date to the currently selected streams
	*/
	void LogTime();


	/**
	 * @brief Writes the value of x given to the right of the "<<" operator, to the currently selected streams
	 * @tparam T Type of X
	 * @param x Value to be writen to the selected streams
	*/
	template<class T>
	OStreamManager& operator<<(const T& x) {
		TestOutputSchemeValidity();
		if (output_flags & OStream1) os1_ << x;
		if (output_flags & OStream2) os2_ << x;
		if (output_flags & OFStream) ofs_ << x;
		return* this;
	}
	/**
	 * @brief Writes the value of x given to the right of the "<<" operator, to the currently selected streams
	 * @param os Value to be writen to the selected streams
	*/
	OStreamManager& operator<<(std::ostream& (*os)(std::ostream&));
//END Methods ++++++++++++++++++++++++++

//Attributes ++++++++++++++++++++++++++
public:
	LoggerOutputFlags output_flags; // Binary mask used to select which streams to output to

private:
	std::tm tm_; // Used when writing time to streams
	std::time_t time_; // Used when writing time to streams

	std::ostream& os1_; // Output stream n1
	std::ostream& os2_; // Output stream n2
	std::ofstream ofs_; // Output file stream

	LoggerOutputFlags defined_ouputs_; // Binary flags used to keep track of the currently defined streams

	bool throw_on_danger_; // Controls whether or not the OSM should throw on dangerous output scheme
//END Attributes -----------------------
};

void StartConsole();