#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace zxrenderer {

extern spdlog::logger gLogger;

void InitLogger();

}  // namespace zxrenderer
