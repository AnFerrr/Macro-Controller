#pragma once

#include "MacroPadCommons.h"

namespace macropad
{
	/**
	 * @brief Holds a version composed of 4 integers.
	 */
	struct CORE_DLL Version4
	{
		int major; /**< @brief major identifier */
		int minor; /**< @brief minor identifier */
		int patch; /**< @brief patch identifier */
		int build; /**< @brief build identifier */

		/**
		 * @brief Creates an empty Version4. Sets all attributes to 0.
		 */
		Version4();
		/**
		 * @brief Creates an Version4 from a valid string.
		 * 
		 * @param version_str: The string used to initiate the Version4.
		 * Must follow the version::version_format regex constexpr.
		 */
		Version4(const char* version_str);
		/**
		 * @brief Creates an Version4 from a valid string.
		 *
		 * @param version: The existing Version4 used to initiate the new Version4.
		 */
		Version4(const Version4& version);
	};

	namespace version
	{
		/**
		 * @brief Checks if a string is a valid version string. Aka: matches version::version_format.
		 * 
		 * @param version_str: The string to be tested.
		 * 
		 * @return: true when the string is a valid version string, false otherwise.
		 */
		CORE_DLL bool is_version_string(const char* version_str);
		constexpr const char* version_format = "\\d+\\.\\d+\\.\\d+\\.\\d+";
	}
}

/**
 * @brief Outputs to a stream the version as "x.x.x.x", where x is replaced by integers.
 */
CORE_DLL std::ostream& operator<<(std::ostream& output, const macropad::Version4& version);




