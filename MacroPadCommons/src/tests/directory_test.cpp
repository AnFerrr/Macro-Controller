#include "mppch.h"

#define MP_TESTING_DIRECTORY
#ifdef MP_TESTING_DIRECTORY
#include "CppUnitTest.h"

#include <directory/directory.h>
#include <log/Log.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace fs = std::filesystem;

namespace macropad::tests::commons
{
	const fs::path tmp_test_directory(fs::temp_directory_path() / "macropad_testing");

	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		macropad::logging::Log::Init();

		Assert::AreEqual(fs::create_directories(tmp_test_directory), true);
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		fs::remove_all(tmp_test_directory);
	}

	TEST_CLASS(Directory)
	{
	public:
		TEST_METHOD(Empty_directory)
		{
			Logger::WriteMessage("Testing empty directory.\n");
			Assert::AreEqual(macropad::directory_management::check_directory(tmp_test_directory.string()), -2);
		}

		TEST_METHOD(Missing_directory)
		{
			Logger::WriteMessage("Testing missing Directory.\n");
			Assert::AreEqual(macropad::directory_management::check_directory((tmp_test_directory / "missing").string()), -1);
		}
	};
}
#endif