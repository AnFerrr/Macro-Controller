#include "mppch.h"

//#define MP_TESTING_DIRECTORY
#ifdef MP_TESTING_DIRECTORY
#include "CppUnitTest.h"

#include <directory/directory.h>
#include <log/Log.h>

#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace fs = std::filesystem;

namespace macropad::commons::directory_management::tests
{
	const fs::path tmp_test_directory(fs::temp_directory_path() / "macropad_testing");
	const fs::path empty_directory(tmp_test_directory / "empty_directory");
	const fs::path non_empty_directory(tmp_test_directory / "non_empty_directory");
	const fs::path text_file(non_empty_directory / "text_file.txt");

	TEST_CLASS(Check_Directory)
	{

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			macropad::logging::Log::Init();

			fs::create_directories(empty_directory);
			fs::create_directories(non_empty_directory);

			std::ofstream file(text_file);
			file << "Testing check_directory on regular file" << std::endl;
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			fs::remove_all(tmp_test_directory);
		}
	public:
		TEST_METHOD(Empty_directory)
		{
			Assert::AreEqual(macropad::directory_management::check_directory(empty_directory.string()), -2);
		}
			
		TEST_METHOD(Unexistant_directory)
		{
			Assert::AreEqual(macropad::directory_management::check_directory((tmp_test_directory / "missing").string()), -1);
		}

		TEST_METHOD(Non_empty_directory)
		{
			Assert::AreEqual(macropad::directory_management::check_directory((non_empty_directory).string()), 1);
		}

		TEST_METHOD(Regular_file)
		{
			Assert::AreEqual(macropad::directory_management::check_directory(text_file.string()), -1);
		}
	};
}
#endif