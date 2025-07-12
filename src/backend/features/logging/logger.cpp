#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger>
create_logger(const spdlog::level::level_enum log_level) {
  // ISO 8601 timestamp format: 2025-06-28T10:00:00-0500
  const std::string pattern = "[%Y-%m-%dT%H:%M:%S%z] [%^%l%$] %v";

  // Create sinks
  const auto console_sink =
      std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_pattern(pattern);

  const auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "app.log",       // log file name
      1024 * 1024 * 5, // 5 MB max file size
      10               // max 10 rotated files
  );
  file_sink->set_pattern(pattern);

  std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

  // Create logger with multiple sinks
  auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(),
                                                 sinks.end());

  // Optional: set global logger
  spdlog::set_default_logger(logger);

  // Set global log level
  spdlog::set_level(log_level); // or info, warn, etc.

  return logger;
}
