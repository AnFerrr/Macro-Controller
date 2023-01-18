#include "gtest/gtest.h"

#include <directory/directory.h>
#include <log/Log.h>

#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

class DirectoryTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		macropad::logging::Log::Init();

		fs::create_directories(empty_directory);
		fs::create_directories(non_empty_directory);

		std::ofstream file(text_file);
		file << "Testing check_directory on regular file" << std::endl;
	}

	void TearDown() override
	{
		fs::remove_all(tmp_test_directory);
	}

public:
	const fs::path tmp_test_directory = fs::temp_directory_path() / "macropad_testing";
	const fs::path empty_directory = tmp_test_directory / "empty_directory";
	const fs::path non_empty_directory = tmp_test_directory / "non_empty_directory";
	const fs::path text_file = non_empty_directory / "text_file.txt";
};

TEST_F(DirectoryTest, EmptyDirectory)
{
	EXPECT_EQ(macropad::directory_management::check_directory(empty_directory.string()), -2);

}