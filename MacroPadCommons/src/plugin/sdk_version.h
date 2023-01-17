#pragma once

namespace macropad
{
#define MP_SDK_VERSION_MAJOR 0
#define MP_SDK_VERSION_MINOR 1
#define MP_SDK_VERSION_PATCH 12
#define MP_SDK_VERSION_BUILD 0

#define MP_SDK_VERSION stringify(MP_SDK_VERSION_MAJOR) "." stringify(MP_SDK_VERSION_MINOR) "." stringify(MP_SDK_VERSION_PATCH) "." stringify(MP_SDK_VERSION_BUILD)
}
