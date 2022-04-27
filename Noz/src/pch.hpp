#pragma once
#ifdef NOZ_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#include <Windows.h>
#endif

#include <memory>

#include "Utils/Log/Log.hpp"
#include "Utils/Cryptor/Cryptor.hpp"