#include <SDL3/SDL.h>

#include <ZXRenderer/DesktopScreen.h>
#include <ZXRenderer/RasterizationPipeline.h>
#include <ZXRenderer/Renderer.h>
#include <ZXRenderer/UniformBuffer.h>
#include <ZXRenderer/VertexBuffer.h>
#include <ZXRenderer/WindowsConsoleScreen.h>

#include <shaders/TriangleShader.h>

#include <ZXMath/ZXMath.h>

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
		// Triangle 1
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	std::vector<size_t> indices{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8
	};

	auto vertex_buffer = std::make_shared<VertexBuffer>(vertices, indices, 6);
	vertex_buffer->BindAttribute(VertexBindingPoint::_0, 0, 3);
	vertex_buffer->BindAttribute(VertexBindingPoint::_1, 3, 3);

	auto uniform_buffer = std::make_shared<UniformBuffer>();

	auto shader = std::make_shared<TriangleShader>();

	auto pipeline = std::make_shared<RasterizationPipeline>();
	pipeline->SetPrimitiveType(PrimitiveType::TRIANGLE_LIST);
	pipeline->SetShader(shader);

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
