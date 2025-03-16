#include <ZXRenderer/Logger.h>

namespace zxrenderer {

static auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ZXRenderer.log", true);
static auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

spdlog::logger gLogger("logger", { consoleSink, fileSink });

void InitLogger() {
	fileSink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
	consoleSink->set_pattern("[%H:%M:%S] [%^%l%$] %v");
}

}  // namespace zxrenderer
