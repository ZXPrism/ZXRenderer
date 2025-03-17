#pragma once

#include <ZXRenderer/Screen.h>

#include <SDL3/SDL.h>

namespace zxrenderer {

/**
 * @brief Represents a screen on desktop OSs, e.g. Windows, Linux and Mac OS
 *
 * @details Its main functionality relies on SDL3. This class will firstly
 * inits SDL3, then creates a window and retrieves the surface of it as the framebuffer
 */
class DesktopScreen : public Screen {
private:
	SDL_Window *_SDLWindow;
	SDL_Surface *_WindowSurface;
	const SDL_PixelFormatDetails *_WindowSurfaceFormat;

public:
	/**
	 * @brief Constructs a new DesktopScreen object with initial size
	 *
	 * @param width The width of the screen
	 * @param height The height of the screen
	 */
	DesktopScreen(uint32_t width, uint32_t height);

	/**
	 * @brief Destroys the DesktopScreen object
	 *
	 * @details Frees all SDL3 resources
	 */
	~DesktopScreen();

	/**
	 * @brief Writes color to the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @param color The color of the pixel, in R8G8B8 format
	 */
	virtual void WritePixel(uint16_t row, uint16_t col, uint32_t color) override;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return uint32_t The color of the pixel, in R8G8B8 format
	 */
	virtual uint32_t ReadPixel(uint16_t row, uint16_t col) const override;

	/**
	 * @brief Clears the back buffer with desired color
	 *
	 * @param clear_color The clear color, in R8G8B8 format
	 */
	virtual void Clear(uint32_t clear_color) override;

	/**
	 * @brief Presents the image on the back buffer to the screen
	 *
	 * @note This opeation is often called "swap buffers"
	 */
	virtual void Present() override;

private:
	/**
	 * @brief Inits the framebuffer
	 *
	 * @param n_color_comp The number of color components
	 *
	 * @note Whether to use double buffering is up to the implementation
	 * We only ensure that one screen must have at least one buffer
	 */
	virtual void _InitFrameBuffer(uint8_t n_color_comp) override;
};

}  // namespace zxrenderer
