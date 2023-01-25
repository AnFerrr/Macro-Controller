#include "mppch.h"

#include "version.h"


// TODO : Make sure plugins can't modify core versions
namespace macropad
{
	Version4::Version4() : major(0), minor(0), patch(0), build(0) {};

	Version4::Version4(const Version4& version) : major(version.major), minor(version.minor), patch(version.patch), build(version.build) {};

	Version4::Version4(const char* version_str)
	{
		if (!version::is_version_string(version_str)) {
			major = -1;
			minor = -1;
			patch = -1;
			build = -1;
			return;
		}

		std::stringstream string_stream(version_str);
		std::vector<int> values;
		int value;

		while (string_stream >> value) {
			values.push_back(value);
			if (string_stream.peek() == '.') {
				string_stream.ignore();
			}
		}

		major = values[0];
		minor = values[1];
		patch = values[2];
		build = values[3];
	}

	bool version::is_version_string(const char* version_str)
	{
		std::regex regex(macropad::version::version_format);

		if (std::regex_match(version_str, regex))
			return true;

		return false;
	}
}

std::ostream& operator<<(std::ostream& output, const macropad::Version4& version)
{
	return output << version.major << "." << version.minor << "." << version.patch << "." << version.build;
}