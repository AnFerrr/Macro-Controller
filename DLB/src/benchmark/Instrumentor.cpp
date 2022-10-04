#include <mutex>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "Instrumentor.h"

namespace AnFer {
	namespace Benchmark {

		Instrumentor& Instrumentor::Instance()
		{
			static Instrumentor instance;
			return instance;
		}

		Instrumentor::~Instrumentor()
		{
			EndSession();
		}

		void Instrumentor::BeginSession(const char* name, const char* filepath)
		{
			if (m_active_session_) {
				EndSession();
			}
			m_active_session_ = true;
			m_output_stream_.open(filepath, std::ios::out);
			WriteHeader();
			m_session_name_ = name;
		}

		void Instrumentor::EndSession()
		{
			if (!m_active_session_) {
				return;
			}
			m_active_session_ = false;
			WriteFooter();
			m_output_stream_.close();
			m_profile_count_ = 0;
		}

		void Instrumentor::WriteProfile(const ProfileResult& result)
		{
			std::lock_guard<std::mutex> lock(m_lock_);

			if (m_profile_count_++ > 0) { m_output_stream_ << ","; }

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_output_stream_ << "{";
			m_output_stream_ << "\"cat\":\"function\",";
			m_output_stream_ << "\"dur\":" << (result.end - result.start) << ',';
			m_output_stream_ << "\"name\":\"" << name << "\",";
			m_output_stream_ << "\"ph\":\"X\",";
			m_output_stream_ << "\"pid\":0,";
			m_output_stream_ << "\"tid\":" << result.threadID << ",";
			m_output_stream_ << "\"ts\":" << result.start;
			m_output_stream_ << "}";

			m_output_stream_.flush();
		}

		void Instrumentor::WriteHeader()
		{
			m_output_stream_ << "{\"otherData\": {},\"traceEvents\":[";
			m_output_stream_.flush();
		}

		void Instrumentor::WriteFooter()
		{
			m_output_stream_ << "]}";
		}
	}
}