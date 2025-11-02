#pragma once

#include <string>
#include <stdio.h>

#define TOY_PRINT_COLOR_WHITE	"\x1b[0m"
#define TOY_PRINT_COLOR_GREEN	"\x1b[32m"
#define TOY_PRINT_COLOR_YELLOW	"\x1b[33m"
#define TOY_PRINT_COLOR_RED		"\x1b[31m"
#define TOY_PRINT_COLOR_MAGENTA	"\x1b[35m"

namespace Toy
{
	class Logger
	{
	public:
		Logger(const std::string& name = "@") : name(name) {}

		template<class... argT> void trace(const std::string& format, argT... args)
		{
			print(TOY_PRINT_COLOR_WHITE, format, args...);
		}

		template<class... argT> void info(const std::string& format, argT... args)
		{
			print(TOY_PRINT_COLOR_GREEN, format, args...);
		}
		template<class... argT> void warn(const std::string& format, argT... args)
		{
			print(TOY_PRINT_COLOR_YELLOW, format, args...);
		}
		template<class... argT> void error(const std::string& format, argT... args)
		{
			print(TOY_PRINT_COLOR_RED, format, args...);
		}
		template<class... argT> void critical(const std::string& format, argT... args)
		{
			print(TOY_PRINT_COLOR_MAGENTA, format, args...);
		}
	private:
		std::string name;

		template<class... argT> void print(const std::string& color, const std::string& format, argT... args)
		{
			printf((color + "[%s] : " + format + TOY_PRINT_COLOR_WHITE + '\n').c_str(), name.c_str(), args...);
		}
	};
}


namespace Toy
{
	extern Logger coreLogger;
	template<class ...argT>
	void TraceC(const std::string& format, argT ...args)
	{
		coreLogger.trace(format, args...);
	}
	template<class ...argT>
	void InfoC(const std::string& format, argT ...args)
	{
		coreLogger.info(format, args...);
	}
	template<class ...argT>
	void WarnC(const std::string& format, argT ...args)
	{
		coreLogger.warn(format, args...);
	}
	template<class ...argT>
	void ErrorC(const std::string& format, argT ...args)
	{
		coreLogger.error(format, args...);
	}
	template<class ...argT>
	void CriticalC(const std::string& format, argT ...args)
	{
		coreLogger.critical(format, args...);
	}
}


#define TOY_CORE_TRACE(...) ::Toy::TraceC(__VA_ARGS__)
#define TOY_CORE_INFO(...) ::Toy::InfoC(__VA_ARGS__)
#define TOY_CORE_WARN(...) ::Toy::WarnC(__VA_ARGS__)
#define TOY_CORE_ERROR(...) ::Toy::ErrorC(__VA_ARGS__)
#define TOY_CORE_CRITICAL(...) ::Toy::CriticalC(__VA_ARGS__)

