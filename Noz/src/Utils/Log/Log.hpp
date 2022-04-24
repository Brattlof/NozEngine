#pragma once

#include <stdio.h>
#include <string>
#include <consoleapi.h>

namespace Noz
{
	class Log
	{
	public:
		static inline void Allocate()
		{
			FILE* f;
			AllocConsole();
			freopen_s(&f, "CONOUT$", "w", stdout);
		}

		static inline void Free()
		{
			FreeConsole();
		}

		template <class ...T>
		static inline void Error(const char* format, T... args)
		{
			// Concanate format with prefix and newline;
			std::string ret("[- NOZ -] ");
			ret += format;
			ret += "\n";

			// Print to console
			printf(ret.c_str(), args...);
		}

		template <class ...T>
		static inline void Info(const char* format, T... args)
		{
			// Concanate format with prefix and newline;
			std::string ret("[/ NOZ /] ");
			ret += format;
			ret += "\n";

			// Print to console
			printf(ret.c_str(), args...);
		}
	};
}

// Macros for logger class

#ifdef NOZ_DEBUG
#define NOZ_ALLOCATE_CONSOLE ::Noz::Log::Allocate();
#define NOZ_FREE_CONSOLE ::Noz::Log::Free();
#define NOZ_LOG_ERROR(...) ::Noz::Log::Error(__VA_ARGS__)
#define NOZ_LOG_INFO(...) ::Noz::Log::Info(__VA_ARGS__)
#else
#define NOZ_ALLOCATE_CONSOLE
#define NOZ_FREE_CONSOLE
#define NOZ_LOG_ERROR
#define NOZ_LOG_INFO
#endif