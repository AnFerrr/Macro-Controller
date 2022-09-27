#ifdef CORE_EXPORT
#define CORE_DLL extern "C" __declspec(dllexport)
#else
#define CORE_DLL extern "C" __declspec(dllimport)
#endif