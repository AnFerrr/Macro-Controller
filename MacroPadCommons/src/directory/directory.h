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
	 * @return true if the directory exists and is not empty, false otherwise
	 */
	CORE_DLL int check_directory(const std::string& dir);

	/**
	 * @brief Creates a given directory.
	 *
	 * @param dir: The path to the directory to create.
	 *
	 * @return 1 if the directory was created successfully, -1 if the directory already exists, -2 for other errors.
	 */
	CORE_DLL int create_directory(const std::string& dir);

	/**
	 * @brief Lists all regular files in the specified directory
	 *
	 * @param dir: The directory to list filenames from
	 * @param filenames: Vector that will be filled with the names
	 */
	CORE_DLL void list_regular_files(const std::string& dir, std::vector<std::string>& filenames);
}