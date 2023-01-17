#include "mppch.h"

//#define MP_TESTING
#ifdef MP_TESTING
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <sstream>
#include "version/version.h"

namespace macropad::tests::commons
{
	TEST_CLASS(Version_tests)
	{
	public:
		TEST_METHOD(Empty)
		{
			Version4 version;

			Assert::AreEqual(version.major, 0);
			Assert::AreEqual(version.minor, 0);
			Assert::AreEqual(version.patch, 0);
			Assert::AreEqual(version.build, 0);
		}

		TEST_METHOD(Valid_String)
		{
			Version4 version("1.2.3.4");

			Assert::AreEqual(version.major, 1);
			Assert::AreEqual(version.minor, 2);
			Assert::AreEqual(version.patch, 3);
			Assert::AreEqual(version.build, 4);
		}

		TEST_METHOD(Inalid_String)
		{
			Version4 version("Hello, World!");

			Assert::AreEqual(version.major, -1);
			Assert::AreEqual(version.minor, -1);
			Assert::AreEqual(version.patch, -1);
			Assert::AreEqual(version.build, -1);
		}

		TEST_METHOD(Copy_construction_par)
		{
			Version4 version2("1.2.3.4");
			Version4 version(version2);

			Assert::AreEqual(version.major, 1);
			Assert::AreEqual(version.minor, 2);
			Assert::AreEqual(version.patch, 3);
			Assert::AreEqual(version.build, 4);
		}

		TEST_METHOD(Copy_construction_eq)
		{
			Version4 version2("1.2.3.4");
			Version4 version = version2;

			Assert::AreEqual(version.major, 1);
			Assert::AreEqual(version.minor, 2);
			Assert::AreEqual(version.patch, 3);
			Assert::AreEqual(version.build, 4);
		}

		TEST_METHOD(Output_operator_overload)
		{
			std::stringstream ss;
			Version4 version("1.2.3.4");

			ss << version;

			Assert::AreEqual(ss.str().c_str(), "1.2.3.4");
		}

		// TODO : Other tests I guess
	};
}
#endif