#include <ZXRenderer/DesktopScreen.h>
#include <ZXRenderer/Logger.h>

#include <SDL3/SDL.h>

namespace zxrenderer {

DesktopScreen::DesktopScreen(uint16_t width, uint16_t height)
    : Screen(width, height) {
	SDL_SetAppMetadata(ZXRENDERER_WINDOW_NAME, ZXRENDERER_VERSION, "com.zxprism.zxrenderer");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		gLogger.error("Couldn't initialize SDL: {}", SDL_GetError());
		return;
	}

	_SDLWindow = SDL_CreateWindow(ZXRENDERER_WINDOW_NAME, width, height, 0);
	if (!_SDLWindow) {
		gLogger.error("Couldn't create window: {}", SDL_GetError());
		return;
	}

	_WindowSurface = SDL_GetWindowSurface(_SDLWindow);
	_WindowSurfaceFormat = SDL_GetPixelFormatDetails(_WindowSurface->format);
}

DesktopScreen::~DesktopScreen() {
	SDL_DestroyWindow(_SDLWindow);
	SDL_Quit();
}

void DesktopScreen::WritePixel(uint16_t row, uint16_t col, uint32_t color) {
	auto pixels = static_cast<Uint32 *>(_WindowSurface->pixels);
	Uint32 pixel_color = SDL_MapRGBA(_WindowSurfaceFormat, nullptr, color >> 24, color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff);

	pixels[row * _Width + col] = pixel_color;
}

uint32_t DesktopScreen::ReadPixel(uint16_t row, uint16_t col) const {
	uint32_t res = 0;
	uint8_t *byte_ptr = reinterpret_cast<uint8_t *>(&res);

	auto pixels = static_cast<Uint32 *>(_WindowSurface->pixels);
	SDL_GetRGBA(pixels[row * _Width + col], _WindowSurfaceFormat, nullptr, byte_ptr + 3, byte_ptr + 2, byte_ptr + 1, byte_ptr);

	return res;
}

void DesktopScreen::Clear(uint32_t clear_color) {
	Uint32 color = SDL_MapRGBA(_WindowSurfaceFormat, nullptr, clear_color >> 24, clear_color >> 16 & 0xff, clear_color >> 8 & 0xff, clear_color & 0xff);
	SDL_Rect rect{ 0, 0, _WindowSurface->w, _WindowSurface->h };
	SDL_FillSurfaceRect(_WindowSurface, &rect, color);
}

void DesktopScreen::Present() {
	SDL_UpdateWindowSurface(_SDLWindow);
}

}  // namespace zxrenderer
