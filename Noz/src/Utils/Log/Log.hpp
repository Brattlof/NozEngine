#pragma once

#include <consoleapi.h>
#include <ctime>

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <fmt/chrono.h>

namespace Noz
{
	static std::time_t s_Time;

	class Log
	{
	public:
		static inline void Allocate()
		{
			AllocConsole();
			freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
			freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		}

		static inline void Free()
		{
			FreeConsole();
		}

		template <class ...T>
		static inline void Error(const char* format, T... args)
		{
			time(&s_Time);

			printf(fmt::format("{:%H:%M:%S} [NOZ_ERROR] {}\n",
				fmt::localtime(s_Time),
				format).c_str(),
				args...);
		}

		template <class ...T>
		static inline void Info(const char* format, T... args)
		{
			time(&s_Time);

			printf(fmt::format("{:%H:%M:%S} [NOZ_INFO] {}\n",
				fmt::localtime(s_Time),
				format).c_str(),
				args...);
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