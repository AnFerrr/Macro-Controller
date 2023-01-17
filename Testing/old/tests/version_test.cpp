#include "mppch.h"

//#define MP_TESTING
#ifdef MP_TESTING
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <sstream>
#include "version/version.h"

namespace macropad::commons::version::tests
{
	TEST_CLASS(Version4)
	{
	public:
		TEST_METHOD(Create_empty)
		{
			macropad::Version4 version;

			Assert::AreEqual(version.major, 0);
			Assert::AreEqual(version.minor, 0);
			Assert::AreEqual(version.patch, 0);
			Assert::AreEqual(version.build, 0);
		}

		TEST_METHOD(Create_from_valid_string)
		{
			macropad::Version4 version("1.2.3.4");

			Assert::AreEqual(version.major, 1);
			Assert::AreEqual(version.minor, 2);
			Assert::AreEqual(version.patch, 3);
			Assert::AreEqual(version.build, 4);
		}

		TEST_METHOD(Create_from_invalid_string)
		{
			macropad::Version4 version("Hello, World!");

			Assert::AreEqual(version.major, -1);
			Assert::AreEqual(version.minor, -1);
			Assert::AreEqual(version.patch, -1);
			Assert::AreEqual(version.build, -1);
		}

		TEST_METHOD(Create_from_valid_Version4)
		{
			macropad::Version4 version2("6.9.4.2");
			macropad::Version4 version(version2);

			Assert::AreEqual(version.major, 6);
			Assert::AreEqual(version.minor, 9);
			Assert::AreEqual(version.patch, 4);
			Assert::AreEqual(version.build, 2);
		}

		TEST_METHOD(Copy_from_valid_string)
		{
			macropad::Version4 version2("0.6.6.6");
			macropad::Version4 version = version2;

			Assert::AreEqual(version.major, 0);
			Assert::AreEqual(version.minor, 6);
			Assert::AreEqual(version.patch, 6);
			Assert::AreEqual(version.build, 6);
		}

		TEST_METHOD(Output_operator_overload)
		{
			std::stringstream ss;
			macropad::Version4 version("1.4.2.0");

			ss << version;

			Assert::AreEqual(ss.str().c_str(), "1.4.2.0");
		}

		// TODO : Other tests I guess
	};
}
#endif