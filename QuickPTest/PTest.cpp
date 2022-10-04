#define PLUGIN_EXPORT

#include "PTest.h"

#define PROFILE_SCOPE(name) std::cout << ##name <<std::endl;
#define PROFILE_FUNC PROFILE_SCOPE(__FUNCSIG__)