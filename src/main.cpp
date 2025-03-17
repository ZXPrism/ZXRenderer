#include <SDL3/SDL.h>

#include <ZXRenderer/DesktopScreen.h>
#include <ZXRenderer/RasterizationPipeline.h>
#include <ZXRenderer/Renderer.h>
#include <ZXRenderer/UniformBuffer.h>
#include <ZXRenderer/VertexBuffer.h>
#include <ZXRenderer/WindowsConsoleScreen.h>

#include <chrono>
#include <memory>
#include <random>
#include <thread>

int main(int argc, char *argv[]) {
	using namespace zxrenderer;

	Renderer renderer;
	DesktopScreen screen{ 1280, 720 };
	// WindowsConsoleScreen screen{ 128, 32 };

	std::vector<float> vertices{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	auto vertex_buffer = std::make_shared<VertexBuffer>(vertices, 3);
	vertex_buffer->BindAttribute(VertexBindingPoint::_0, 0, 3);

	auto pipeline = std::make_shared<RasterizationPipeline>();
	pipeline->SetPrimitiveType(PrimitiveType::TRIANGLE_LIST);

	auto uniform_buffer = std::make_shared<UniformBuffer>();

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}

		screen.Clear(0xffffffff);
		// screen.Clear(0);

		renderer.BeginRender();
		renderer.BeginRenderPass();
		renderer.BindVertexBuffer(vertex_buffer);
		renderer.BindUniformBuffer(uniform_buffer);
		renderer.BindPipeline(pipeline);
		renderer.BindRenderTarget(screen.GetRenderTarget());
		renderer.Draw(0, 3);
		renderer.EndRenderPass();
		renderer.EndRender();

		screen.Present();
	}

	return 0;
}
