#pragma once

#include <ZXRenderer/Screen.h>

#include <SDL3/SDL.h>

namespace zxrenderer {

/**
 * @brief Represents a screen on desktop OSs, e.g. Windows, Linux and Mac OS
 * @details Its main functionality relies on SDL3. This class will firstly
 * inits SDL3, then creates a window and retrieves the surface of it as the framebuffer
 */
class DesktopScreen : public Screen {
public:
	DesktopScreen(size_t width, size_t height);

private:
	SDL_Window *_SDLWindow;      // window context
	SDL_Renderer *_SDLRenderer;  // only for debugging, like displaying the debug texts
};

}  // namespace zxrenderer
