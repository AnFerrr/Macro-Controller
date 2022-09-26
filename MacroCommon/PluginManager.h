#pragma once

#ifdef PLUGIN_EXPORT
#define PLUGIN_SDK extern "C" __declspec(dllexport)
#else
#define PLUGIN_SDK extern "C" __declspec(dllimport)
#endif

class ITest {
public:
	virtual ~ITest() = default;

	virtual const char* getValue() const = 0;
};

class Test : public ITest {
	public:
		Test() {};
		~Test() {};

	char value[3] = "ah";
	const char* getValue() const {
		return value;
	};
};

PLUGIN_SDK int __stdcall return_int(int a);
PLUGIN_SDK ITest* __stdcall return_test();
