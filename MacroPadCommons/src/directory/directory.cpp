#include "mppch.h"

#include "directory.h"

#include "Log/Log.h"
#include "profiling/profiling_timer.h"

namespace macropad::directory_management
{
	int check_directory(const std::string& dir)
	{
		TIMING_FUNCTION();
		
		if (!std::filesystem::is_directory(dir)) {
			MP_CORE_WARN("{} doesn't exist.", dir);

			return -1;
		}
		if (std::filesystem::is_empty(dir)) {
			MP_CORE_WARN("{} is empty.", dir);

			return -2;
		}

		MP_CORE_INFO("Directory exists and isn't empty");

		return 1;
	}

	bool create_directory(const std::string& dir)
	{
		TIMING_FUNCTION();

		if (!std::filesystem::create_directories(dir)) {
			MP_CORE_WARN("Creationg of {} failed...", dir);

			return false;
		}

		MP_CORE_INFO("Directory exists and isn't empty");

		return true;
	}

	void list_regular_files(const std::string& dir, std::vector<std::string>& filenames)
	{
		TIMING_FUNCTION();
		for (const auto& entry : std::filesystem::directory_iterator(dir))
			if (std::filesystem::is_regular_file(entry))
				filenames.push_back(entry.path().filename().string());
	}
}