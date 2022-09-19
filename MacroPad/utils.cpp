#include "utils.h"

OStreamManager::OStreamManager(std::ostream& os1, std::ostream& os2,
		const LoggerOutputFlags flags, bool throw_on_danger) :
	os1_(os1), os2_(os2),
	output_flags(flags),
	defined_ouputs_(OStream1 | OStream2),
	throw_on_danger_(throw_on_danger) {
	TestOutputSchemeValidity();
};

OStreamManager::OStreamManager(std::ostream& os1, std::string const& filename,
		LoggerOutputFlags flags, bool throw_on_danger) :
	os1_(os1), os2_(std::cerr), ofs_(filename.c_str(), std::ios::out),
	output_flags(flags),
	defined_ouputs_(OStream1 | OFStream),
	throw_on_danger_(throw_on_danger) {
	TestOutputSchemeValidity();
};

OStreamManager::OStreamManager(LoggerOutputFlags flags, bool throw_on_danger) :
	os1_(std::cout), os2_(std::cerr),
	output_flags(flags),
	defined_ouputs_(OStream1 | OStream2),
	throw_on_danger_(throw_on_danger) {
	TestOutputSchemeValidity();
};

bool OStreamManager::IsOutputSchemeValid() {
	UpdateTime();
	char masked_output_flags = output_flags | ~defined_ouputs_;
	return ((masked_output_flags & (masked_output_flags + 1)) == 0);
}

bool OStreamManager::TestOutputSchemeValidity() {
	bool output_scheme_validity = IsOutputSchemeValid();
	if (!output_scheme_validity) {
		UpdateTime();
		std::cerr << std::put_time(&tm_, TIME_FORMAT_STRING);
		std::cerr << "Manager set to write to a stream that wasn't setup" << std::endl <<
			TIME_MARGIN << "This may result in undefined behavior" << std::endl;
	}
	if (DEFAULT_THROW_ON_OSM_DANGER)
		throw std::invalid_argument("Manager set to write to a stream that wasn't setup");
	return (output_scheme_validity);
}

void OStreamManager::UpdateTime() {
	time_ = std::time(nullptr);
	localtime_s(&tm_, &time_);
}

void OStreamManager::LogTime() {
	TestOutputSchemeValidity();
	if (output_flags & OStream1) os1_ << std::put_time(&tm_, TIME_FORMAT_STRING);
	if (output_flags & OStream2) os2_ << std::put_time(&tm_, TIME_FORMAT_STRING);
	if (output_flags & OFStream) ofs_ << std::put_time(&tm_, TIME_FORMAT_STRING);
}

OStreamManager& OStreamManager::operator<<(std::ostream& (*os)(std::ostream&)) {
	TestOutputSchemeValidity();
	if (output_flags & OStream1) os1_ << os;
	if (output_flags & OStream2) os2_ << os;
	if (output_flags & OFStream) ofs_ << os;
	return *this;
}

void StartConsole() {
	AllocConsole();

	FILE* newstdout = stdout, * newstdin = stdin, * newsterr = stderr;

	freopen_s(&newstdout, "CONOUT$", "w", stdout);
	freopen_s(&newsterr, "CONOUT$", "w", stderr);
	freopen_s(&newstdin, "CONIN$", "r", stdin);

	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}