#include "mppch.h"

#include <system_error>

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

	int create_directory(const std::string& dir)
	{
		TIMING_FUNCTION();

		std::error_code error;

		if (!std::filesystem::create_directories(dir, error)) {
			std::string log("Creationg of " + dir + " failed.");

			if (error.value() == (int)std::errc::file_exists) {
				log += " Directory already exists.\n";
				MP_CORE_WARN(log);

				return -1;
			}

			log += "\n";
			MP_CORE_WARN(log);

			return -2;
		}

		MP_CORE_INFO("Directory exists and isn't empty");

		return 1;
	}

	void list_regular_files(const std::string& dir, std::vector<std::string>& filenames)
	{
		TIMING_FUNCTION();
		for (const auto& entry : std::filesystem::directory_iterator(dir))
			if (std::filesystem::is_regular_file(entry))
				filenames.push_back(entry.path().filename().string());
	}
}