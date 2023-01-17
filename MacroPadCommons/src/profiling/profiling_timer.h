#pragma once
// Some code based on https://pastebin.com/qw5Neq4U from @davechurchill on github

#include "mppch.h"
#include "profiling_types.h"
#include "instrumentation_manager.h"

namespace macropad::profiling
{
	class ProfilingTimer
	{
		macropad::profiling::timing_profile result;

		std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
		bool is_stopped;

	public:

		ProfilingTimer(const std::string& name)
			: result({ name, 0, 0, 0 })
			, is_stopped(false)
		{
			start_timepoint = std::chrono::high_resolution_clock::now();
		}

		~ProfilingTimer()
		{
			if (!is_stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			result.start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
			result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
			result.thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
			InstrumentationManager::Instance().WriteProfile(result);

			is_stopped = true;
		}
	};
}

#ifdef PROFILING
#define TIMING_SCOPE(name) macropad::profiling::ProfilingTimer timer##__LINE__(name)
#define TIMING_FUNCTION()  TIMING_SCOPE(__FUNCTION__)
#else
#define TIMINGE_SCOPE(name)
#define TIMING_FUNCTION()
#endif