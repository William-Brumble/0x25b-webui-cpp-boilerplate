#pragma once

#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> create_logger(const spdlog::level::level_enum log_level);
