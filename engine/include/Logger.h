#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <string>

class Logger {
private:
	static std::shared_ptr<spdlog::logger> s_SpdLogger;

public:
	static void info(std::string_view description) {
		s_SpdLogger->info(description);
	}
	static void warning(std::string_view description) {
		s_SpdLogger->warn(description);
	}
	static void error(std::string_view description) {
		s_SpdLogger->error(description);
	}
	static void trace(std::string_view description) {
		s_SpdLogger->trace(description);
	}
	static void debug(std::string_view description) {
		s_SpdLogger->debug(description);
	}
	static void critical(std::string_view description) {
		s_SpdLogger->critical(description);
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