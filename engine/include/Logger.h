#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <string>

class Logger {
private:
	static std::shared_ptr<spdlog::logger> s_SpdLogger;

public:
	template<typename... Args>
	static void info(spdlog::format_string_t<Args...>fmt,Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->info(fmt, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void warning(spdlog::format_string_t<Args...>fmt, Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->warn(fmt, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void error(spdlog::format_string_t<Args...>fmt, Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->error(fmt, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void trace(spdlog::format_string_t<Args...>fmt, Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->trace(fmt, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void debug(spdlog::format_string_t<Args...>fmt, Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->debug(fmt, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void critical(spdlog::format_string_t<Args...>fmt, Args&&... args) {
		if (s_SpdLogger) {
			s_SpdLogger->critical(fmt, std::forward<Args>(args)...);
		}
	}
	static void init() {
		//tworzenie sinka
		auto ConsoleSink = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		//tworzenie loggera na wskazniku
		s_SpdLogger = std::make_shared <spdlog::logger>("console", ConsoleSink);
		//ustawianie level i pattern na loggerze, a nie na sinku
		s_SpdLogger->set_level(spdlog::level::trace);
		spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%^%l%$] [%@] %v");
	}
};