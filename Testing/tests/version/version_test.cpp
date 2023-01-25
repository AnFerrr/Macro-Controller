#include <gtest/gtest.h>

#include <version/version.h>

using namespace macropad;

TEST(Version_Testing, Uninitialized)
{
	Version4 version;

	EXPECT_EQ(version.major, 0);
	EXPECT_EQ(version.minor, 0);
	EXPECT_EQ(version.patch, 0);
	EXPECT_EQ(version.build, 0);
}

TEST(Version_Testing, Valid_init_string)
{
	Version4 version("1.2.3.4");

	EXPECT_EQ(version.major, 1);
	EXPECT_EQ(version.minor, 2);
	EXPECT_EQ(version.patch, 3);
	EXPECT_EQ(version.build, 4);
}

TEST(Version_Testing, Invalid_init_string)
{
	Version4 version("Hello, World!");

	EXPECT_EQ(version.major, -1);
	EXPECT_EQ(version.minor, -1);
	EXPECT_EQ(version.patch, -1);
	EXPECT_EQ(version.build, -1);
}

TEST(Version_Testing, Copy_constructor)
{
	Version4 version2("6.9.4.2");
	Version4 version(version2);

	EXPECT_EQ(version.major, 6);
	EXPECT_EQ(version.minor, 9);
	EXPECT_EQ(version.patch, 4);
	EXPECT_EQ(version.build, 2);
}

TEST(Version_Testing, Copy_attribution)
{
	Version4 version2("0.6.6.6");
	Version4 version = version2;

	EXPECT_EQ(version.major, 0);
	EXPECT_EQ(version.minor, 6);
	EXPECT_EQ(version.patch, 6);
	EXPECT_EQ(version.build, 6);
}

TEST(Version_Testing, Output_operator_overload)
{
	std::stringstream ss;
	Version4 version("1.4.2.0");
	ss << version;

	EXPECT_EQ(ss.str(), "1.4.2.0");
}