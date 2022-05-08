#pragma once

#ifdef _MSC_VER
	#pragma comment(linker, "/NODEFAULTLIB:LIBCMT.lib")
#endif

#include <memory>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_map>
#include <string>

#include "Utils/Log/Log.hpp"
#include "Utils/Cryptor/Cryptor.hpp"

#include <bx/bx.h>
#include <bgfx/bgfx.h>

#ifdef BX_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#include <Windows.h>
#endif