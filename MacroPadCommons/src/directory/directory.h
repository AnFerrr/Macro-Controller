#pragma once

#include "MacroPadCommons.h"

#include "mppch.h"

namespace macropad::directory_management
{
	/**
	 * @brief Checks if a given directory exists and is not empty.
	 *
	 * @param dir: The path to the directory to check.
	 *
	 * @return True if the directory exists and is not empty, false otherwise
	 */
	CORE_DLL int check_directory(const std::string& dir);

	/**
	 * @brief Creates a given directory.
	 *
	 * @param dir: The path to the directory to create.
	 *
	 * @return True if the directory was created succesfully, false otherwise
	 */
	CORE_DLL bool create_directory(const std::string& dir);

	/**
	 * @brief Lists all regular files in the specified directory
	 *
	 * @param dir: The directory to list filenames from
	 * @param filenames: Vector that will be filled with the names
	 */
	CORE_DLL void list_regular_files(const std::string& dir, std::vector<std::string>& filenames);
}