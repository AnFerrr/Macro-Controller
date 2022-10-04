#pragma once

#include <string>
#include <fstream>
#include <mutex>

namespace AnFer {
	namespace Benchmark {
		struct ProfileResult
		{
			const char* name;
			long long start, end;
			size_t threadID;
		};

		class Instrumentor
		{
		private:
			std::string m_session_name_ = "None";
			std::ofstream m_output_stream_;
			int m_profile_count_ = 0;
			std::mutex m_lock_;
			bool m_active_session_ = false;
			Instrumentor() {};

		public:

			~Instrumentor();

			static Instrumentor& Instance();

			void BeginSession(const char* name, const char* filepath = "time_trace.json");

			void EndSession();

			void WriteProfile(const ProfileResult& result);

			void WriteHeader();

			void WriteFooter();
		};
	}
}