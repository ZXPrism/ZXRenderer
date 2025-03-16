#pragma once

#ifdef _WIN32

#	include <ZXRenderer/Screen.h>

namespace zxrenderer {

/**
 * @brief Represents a screen on the legacy windows console
 *
 */
class WindowsConsoleScreen : public Screen {
private:
	void *_FrontBuffer;
	void *_BackBuffer;

public:
	/**
	 * @brief Constructs a new WindowsConsoleScreen object with initial size
	 *
	 * @param width The width of the screen
	 * @param height The height of the screen
	 */
	WindowsConsoleScreen(uint16_t width, uint16_t height);

	/**
	 * @brief Destroys the WindowsConsoleScreen object
	 *
	 * @details Frees all SDL3 resources
	 */
	~WindowsConsoleScreen();

	/**
	 * @brief Writes color to the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @param color The color of the pixel, in windows console standard colors
	 *
	 * @note You can get the list of standard colors using command "color /?"
	 */
	virtual void WritePixel(uint16_t row, uint16_t col, uint32_t color) override;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return uint32_t The color of the pixel, in windows console standard colors
	 *
	 * @note You can get the list of standard colors using command "color /?"
	 */
	virtual uint32_t ReadPixel(uint16_t row, uint16_t col) const override;

	/**
	 * @brief Clears the back buffer with desired color
	 *
	 * @param clear_color The clear color, in windows console standard colors
	 *
	 * @note You can get the list of standard colors using command "color /?"
	 */
	virtual void Clear(uint32_t clear_color) override;

	/**
	 * @brief Presents the image on the back buffer to the screen
	 *
	 * @note This opeation is often called "swap buffers"
	 */
	virtual void Present() override;
};

}  // namespace zxrenderer

#endif
