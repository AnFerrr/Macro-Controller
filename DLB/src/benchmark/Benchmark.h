#pragma once

#if defined(__FUNCSIG__)
#define MP_FUNC_SIG __FUNCSIG__
#elif defined(__PRETTY_FUNCTION__)
#define MP_FUNC_SIG __PRETTY_FUNCTION__
#else
#define MP_FUNC_SIG __func__
#endif

#define PROFILING 1

#if PROFILING == 1
#define PROFILE_SCOPE(name)		AnFer::Benchmark::Timer timer##__func__##__LINE__(name);
#define PROFILE_FUNCTION PROFILE_SCOPE(MP_FUNC_SIG)
#else
#define PROFILE_SCOPE(name)
#endif