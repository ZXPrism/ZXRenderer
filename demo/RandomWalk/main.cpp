#include <SDL3/SDL.h>

#include <ZXRenderer/DesktopScreen.h>

#include <memory>
#include <random>

int main(int argc, char *argv[]) {
	auto screen = std::make_unique<zxrenderer::DesktopScreen>(512, 512);
	auto [width, height] = screen->GetSize();
	screen->Clear(0x00ffffff);

	std::mt19937_64 engine;
	std::random_device rd;
	engine.seed(rd());
	std::uniform_int_distribution<int> dist(0, 3);

	constexpr int dx[] = {
		0, 0, -1, 1
	};
	constexpr int dy[] = {
		-1, 1, 0, 0
	};
	int x = width / 2, y = height / 2;

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

		screen->WritePixel(y, x, 0x00ff0000);
		int nx = 0, ny = 0;
		do {
			int dir = dist(engine);
			nx = x + dx[dir], ny = y + dy[dir];
		} while (!(nx >= 0 && nx < static_cast<int>(width) && ny >= 0 && ny < static_cast<int>(height)));
		x = nx, y = ny;

		screen->Present();
	}

	return 0;
}
