#include <chrono>
#include <iostream>

#define MP_BUILD_TIMER_DLL

#include "Timer.h"
#include "Instrumentor.h"

namespace AnFer {
	namespace Benchmark {
		Timer::Timer(const char* name) :
			m_result_({ name, 0, 0, 0 })
		{
			m_starting_point_ = std::chrono::high_resolution_clock::now();
		}

		Timer::~Timer()
		{
			if(!m_stopped_)
				Stop();
		}

		void Timer::Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			m_result_.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_starting_point_).time_since_epoch().count();
			m_result_.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

			auto duration = m_result_.end - m_result_.start;
			double ms = duration * 0.001;

			std::cout << "Execution time: " << duration << " (us) " << ms << " ms " << std::endl;
			std::cout.flush();

			m_result_.threadID = std::hash<std::thread::id>()(std::this_thread::get_id());

			AnFer::Benchmark::Instrumentor::Instance().WriteProfile(m_result_);

			m_stopped_ = true;
		}
	}
}
