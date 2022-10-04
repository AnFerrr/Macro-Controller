#pragma once

#include <chrono>
#include <iostream>

#include "Instrumentor.h"

namespace AnFer {
	namespace Benchmark {
		class Timer
		{
		public:
			Timer(const char* name);
			~Timer();
			void Stop();

		private:
			AnFer::Benchmark::ProfileResult m_result_;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_starting_point_;
			bool m_stopped_ = false;
		};
	}
}
