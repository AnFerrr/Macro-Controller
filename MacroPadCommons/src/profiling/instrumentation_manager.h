#pragma once
// Some code based on https://pastebin.com/qw5Neq4U from @davechurchill on github

#include "mppch.h"
#include "profiling_types.h"

// Todo: rework to allow for more profiling types
namespace macropad::profiling
{
	/**
	 * @brief Manages the various profiling tools.
	 * 
	 * Get from InstrumentationManager::Instance().
	 */
	class InstrumentationManager
	{
		std::string session_name = "None";
		std::ofstream output_stream;
		int profile_count = 0;
		std::mutex mutex_lock;
		bool is_session_active = false;

		InstrumentationManager() {}

	public:

		/**
		 * @return Returns a pointer to the manager.
		 */
		static InstrumentationManager& Instance()
		{
			static InstrumentationManager instance;
			return instance;
		}

		~InstrumentationManager()
		{
			EndSession();
		}

		/**
		 * @brief Starts an instrumentation session.
		 *
		 * @param name: name of the session.
		 * @param filepath: path to the file to fill with profiling data.
		 */
		void BeginSession(const std::string& name, const std::string& filepath = "profiling_result.json")
		{
			if (is_session_active)
				EndSession();

			is_session_active = true;
			output_stream.open(filepath);
			WriteHeader();
			session_name = name;
		}

		/**
		 * @brief Ends the profiling session.
		 */
		void EndSession()
		{
			if (!is_session_active)
				return;

			is_session_active = false;
			WriteFooter();
			output_stream.close();
			is_session_active = 0;
		}

		/**
		 * @brief Writes the given results to file.
		 * 
		 * @param result: results to write.
		 */
		void WriteProfile(const macropad::profiling::timing_profile& result)
		{
			std::lock_guard<std::mutex> lock(mutex_lock);

			if (profile_count++ > 0)
				output_stream << ",";

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			output_stream << "{";
			output_stream << "\"cat\":\"function\",";
			output_stream << "\"dur\":" << (result.end - result.start) << ',';
			output_stream << "\"name\":\"" << name << "\",";
			output_stream << "\"ph\":\"X\",";
			output_stream << "\"pid\":0,";
			output_stream << "\"tid\":" << result.thread_id << ",";
			output_stream << "\"ts\":" << result.start;
			output_stream << "}";
		}

		void WriteHeader()
		{
			output_stream << "{\"otherData\": {},\"traceEvents\":[";
		}

		void WriteFooter()
		{
			output_stream << "]}";
		}
	};
}