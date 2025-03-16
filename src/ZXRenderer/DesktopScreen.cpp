#include <ZXRenderer/DesktopScreen.h>

#include <SDL3/SDL.h>

namespace zxrenderer {

DesktopScreen::DesktopScreen(size_t width, size_t height)
    : Screen(width, height) {
	SDL_SetAppMetadata(ZXRENDERER_WINDOW_NAME, ZXRENDERER_VERSION, "com.zxprism.zxrenderer");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow(ZXRENDERER_WINDOW_NAME, width, height, 0);
	if (!window) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return -1;
	}

	surface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateSoftwareRenderer(surface);
	if (!renderer) {
		SDL_Log("Couldn't create renderer: %s", SDL_GetError());
		return -1;
	}
}

}  // namespace zxrenderer
