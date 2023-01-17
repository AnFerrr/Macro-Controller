#pragma once

#include "MacroPadCommons.h"

namespace macropad
{
	struct CORE_DLL Version4
	{
		int major;
		int minor;
		int patch;
		int build;

		Version4();
		Version4(const char* version_str);
		Version4(const Version4& version);
		friend std::ostream& operator<<(std::ostream& output, const Version4& version);
	};

	namespace version
	{
		bool is_version_string(const char* version);
		constexpr const char* regex_str = "\\d+\\.\\d+\\.\\d+\\.\\d+";
	}
}

