#pragma once

#define FMT_HEADER_ONLY
#pragma warning(push, 0)
#include <fmt/format.h>
#include <fmt/chrono.h>
#pragma warning(pop)

namespace Noz
{
	class Log
	{
	public:
		template <typename ...T>
		static inline void Error(const char* format, T... args)
		{
			std::time_t _time;
			time(&_time);

			printf(fmt::format("{:%H:%M:%S} [NOZ_ERROR] {}\n",
				fmt::localtime(_time),
				format).c_str(),
				args...);
		}

		template <typename ...T>
		static inline void Info(const char* format, T... args)
		{
			std::time_t _time;
			time(&_time);

			printf(fmt::format("{:%H:%M:%S} [NOZ_INFO] {}\n",
				fmt::localtime(_time),
				format).c_str(),
				args...);
		}
	};
}

// Macros for logger class

#ifdef NOZ_DEBUG
#define NOZ_LOG_ERROR(...) ::Noz::Log::Error(__VA_ARGS__)
#define NOZ_LOG_INFO(...) ::Noz::Log::Info(__VA_ARGS__)
#else
#define NOZ_LOG_ERROR
#define NOZ_LOG_INFO
#endif