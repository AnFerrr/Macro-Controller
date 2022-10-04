#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "OStreamManager.h"
#include "local_utils.h"

#include "benchmark/Benchmark.h"

OStreamManager::OStreamManager(std::ostream& os1, std::ostream& os2,
	const LoggerOutputFlags& flags, const bool& throw_on_danger)
	: os1_(os1), os2_(os2),
	output_flags(flags), defined_ouputs_(OStream1 | OStream2),
	throw_on_danger_(throw_on_danger)
{
	PROFILE_FUNCTION;
	TestOutputSchemeValidity();
};

OStreamManager::OStreamManager(std::ostream& os1, const char* filename,
	const LoggerOutputFlags& flags, const bool& throw_on_danger)
	: os1_(os1), os2_(std::cerr), ofs_(filename, std::ios::out),
	output_flags(flags), defined_ouputs_(OStream1 | OFStream),
	throw_on_danger_(throw_on_danger)
{
	PROFILE_FUNCTION;
	UpdateTime();
	if (!ofs_.is_open()) {
		output_flags &= ~OFStream;
		defined_ouputs_ &= ~OFStream;
		std::cerr << std::put_time(&tm_, TIME_FORMAT_STRING);
		std::cerr << "Given file couldn't be opened" << std::endl;
		if (throw_on_danger_)
			throw std::runtime_error("Could not open file");
	}
	TestOutputSchemeValidity();
};

OStreamManager::OStreamManager(const LoggerOutputFlags& flags, const bool& throw_on_danger)
	: os1_(std::cout), os2_(std::cerr),
	output_flags(flags),
	defined_ouputs_(OStream1 | OStream2),
	throw_on_danger_(throw_on_danger)
{
	PROFILE_FUNCTION;
	TestOutputSchemeValidity();
};

OStreamManager& OStreamManager::operator<<(std::ostream& (*os)(std::ostream&))
{
	PROFILE_FUNCTION;
	TestOutputSchemeValidity();
	if (output_flags & OStream1) os1_ << os;
	if (output_flags & OStream2) os2_ << os;
	if (output_flags & OFStream) ofs_ << os;
	return *this;
}

void OStreamManager::LogTime()
{
	PROFILE_FUNCTION;
	TestOutputSchemeValidity();
	if (output_flags & OStream1) os1_ << std::put_time(&tm_, TIME_FORMAT_STRING);
	if (output_flags & OStream2) os2_ << std::put_time(&tm_, TIME_FORMAT_STRING);
	if (output_flags & OFStream) ofs_ << std::put_time(&tm_, TIME_FORMAT_STRING);

}
void OStreamManager::UpdateTime()
{
	PROFILE_FUNCTION;
	time_ = std::time(nullptr);
	localtime_s(&tm_, &time_);
}

bool OStreamManager::IsOutputSchemeValid() const
{
	PROFILE_FUNCTION;
	char masked_output_flags = defined_ouputs_ | ~output_flags;
	return ((masked_output_flags & (masked_output_flags + 1)) == 0);
}

bool OStreamManager::TestOutputSchemeValidity()
{
	PROFILE_FUNCTION;
	bool output_scheme_validity = IsOutputSchemeValid();
	if (!output_scheme_validity) {
		UpdateTime();
		std::cerr << std::put_time(&tm_, TIME_FORMAT_STRING);
		std::cerr << "Manager set to write to a stream that wasn't setup" << std::endl <<
			TIME_MARGIN << "This may result in undefined behavior" << std::endl;
	}
	if (throw_on_danger_)
		throw std::invalid_argument("Manager set to write to a stream that wasn't setup");
	return (output_scheme_validity);
}