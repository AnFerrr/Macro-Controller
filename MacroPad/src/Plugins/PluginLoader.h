#pragma once

#include "MacroPad.h"

#include <Plugin/Plugin.h>

#if MP_PLATFORM_WINDOWS == 1
#define SHARED_LIB_EXTENSION ".*\\.dll$"
#define mp_load_library(lib) LoadLibraryA(lib)
#define mp_load_symbol(handle, symbol) GetProcAddress(handle, symbol)
#define mp_close_library(lib) FreeLibrary(lib)
#elif MP_PLATFORM_LINUX == 1
#include <dlfcn.h>
#define SHARED_LIB_EXTENSION ".*\\.so$"
#define mp_load_library(lib) dlopen(lib, RTLD_LAZY | RTLD_DEEPBIND)
#define mp_load_symbol(handle, symbol) dlsym(handle, symbol)
#define mp_close_library(lib) dlclose(lib)
#endif

void loadPlugins(const std::string& dir, std::vector<macropad::plugin::mp_plugin> &plugins);
void releasePlugins(std::vector<macropad::plugin::mp_plugin>& plugins);

template<typename function_return_type, typename... function_arguments>
function_return_type (*getDLLFunction(plugin_handle& handle, const char* function_name, bool mandatory))(function_arguments...)
{
	using function_pointer = function_return_type(*)(function_arguments...);
	auto function = (function_pointer)mp_load_symbol(handle, function_name);
	if (mandatory && !function) {
		macropad::logging::missing_mandatory_function(function_name);
		MP_CORE_RESET_INDENT();
		throw std::runtime_error("");
	}
	else if (!function) {
		macropad::logging::missing_optional_function(function_name);
		MP_CORE_RESET_INDENT();
		return nullptr;
	}
	else
		return function;
}

template<typename function_return_type>
function_return_type callDLLFunction(plugin_handle& handle, const char* function_name, bool mandatory, function_return_type default_value)
{
	auto function = getDLLFunction<function_return_type>(handle, function_name, mandatory);
	if (function) {
		return function();
	}
	else
		return default_value;
}