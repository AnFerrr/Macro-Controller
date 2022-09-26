#pragma once

#define PLUGIN_EXPORT

#include "MacroCommon.h"

class PTest : public APTest
{
public:
	PTest() = default;
	~PTest() = default;

	int finalFunction() const {
		return 4;
	}
	void setsomething(ITest* itest, int val) {
		itest->setValue(val);
	}
	int getValue() const {
		return return_int(666);
	}
};

PLUGIN_DLL IPTest* __stdcall Load() {
	return new PTest;
}