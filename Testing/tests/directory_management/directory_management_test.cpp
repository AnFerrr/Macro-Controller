#include <gtest/gtest.h>

#include <directory/directory.h>
#include <log/Log.h>

#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

class Directory_Testing : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		macropad::logging::LoggingManager::Init();

		fs::create_directories(empty_directory);
		fs::create_directories(non_empty_directory);

		std::ofstream file(text_file);
		file << "Testing check_directory on regular file" << std::endl;
	}

	static void TearDownTestSuite()
	{
		fs::remove_all(tmp_test_directory);
	}

public:
	static const fs::path tmp_test_directory;
	static const fs::path empty_directory;
	static const fs::path non_empty_directory;
	static const fs::path text_file;
};

const fs::path Directory_Testing::tmp_test_directory = fs::temp_directory_path() / "macropad_testing";
const fs::path Directory_Testing::empty_directory = tmp_test_directory / "empty_directory";
const fs::path Directory_Testing::non_empty_directory = tmp_test_directory / "non_empty_directory";
const fs::path Directory_Testing::text_file = non_empty_directory / "text_file.txt";

TEST_F(Directory_Testing, Empty_directory)
{
	EXPECT_EQ(macropad::directory_management::check_directory(empty_directory.string()), -2);
}

TEST_F(Directory_Testing, Non_existant_directory)
{
	EXPECT_EQ(macropad::directory_management::check_directory((tmp_test_directory / "missing").string()), -1);
}

TEST_F(Directory_Testing, Non_empty)
{
	EXPECT_EQ(macropad::directory_management::check_directory((non_empty_directory).string()), 1);
}

TEST_F(Directory_Testing, Regular_file)
{
	EXPECT_EQ(macropad::directory_management::check_directory(text_file.string()), -1);
}