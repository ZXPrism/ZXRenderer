#include <SDL3/SDL.h>

#include <ZXRenderer/DesktopScreen.h>

int main(int argc, char *argv[]) {
	zxrenderer::DesktopScreen screen{ 1024, 1024 };

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.scancode == SDLK_ESCAPE) {
					running = false;
				}
				// Handle other key events here
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				// Handle mouse button down events here
				break;
			case SDL_EVENT_MOUSE_MOTION:
				// Handle mouse motion events here
				break;
				// Handle other events as needed
			}
		}

		screen.Clear(0xFF000000);
		auto [width, height] = screen.GetSize();
		for (uint32_t row = 0; row < height; row++) {
			for (uint32_t col = 0; col < width; col++) {
				int n = 512, i = row, j = col;
				if (std::abs(n - 1 - i) + std::abs(n - 1 - j) < 512) {
					screen.WritePixel(row, col, 0x00FF0000);
				}
			}
		}
		screen.Present();

		SDL_Delay(16);
	}

	return 0;
}
