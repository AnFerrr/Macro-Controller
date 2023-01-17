#pragma once
// Some code based on https://pastebin.com/qw5Neq4U from @davechurchill on github

#include "mppch.h"

namespace macropad::profiling
{
	struct timing_profile
	{
		const std::string name;
		long long start, end;
		size_t thread_id;
	};
}
