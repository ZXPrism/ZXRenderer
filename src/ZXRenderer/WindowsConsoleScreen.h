#pragma once

#ifdef _WIN32

#	include <ZXRenderer/Screen.h>

#	include <string>

namespace zxrenderer {

/**
 * @brief Represents a screen on the legacy windows console
 *
 */
class WindowsConsoleScreen : public Screen {
private:
	std::string _ColorMap;
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
	 * @param color The color of the pixel, see notes below
	 *
	 * @note The legacy console supports a rather limited set of colors,
	 * so I decide not to use normal colors, instead, use different chars
	 * to represent the grey levels, see "docs/ConsoleColors.md" for more information
	 */
	virtual void WritePixel(uint16_t row, uint16_t col, uint32_t color) override;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return uint32_t The color of the pixel, see notes below
	 *
	 * @note The legacy console supports a rather limited set of colors,
	 * so I decide not to use normal colors, instead, use different chars
	 * to represent the grey levels, see "docs/ConsoleColors.md" for more information
	 */
	virtual uint32_t ReadPixel(uint16_t row, uint16_t col) const override;

	/**
	 * @brief Clears the back buffer with desired color
	 *
	 * @param clear_color The clear color, see notes below
	 *
	 * @note The legacy console supports a rather limited set of colors,
	 * so I decide not to use normal colors, instead, use different chars
	 * to represent the grey levels, see "docs/ConsoleColors.md" for more information
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

	/**
	 * @brief Maps an integer color into normalized form ([0, 1])
	 *
	 * @param color The input color
	 * @return float The normalized color
	 */
	float _MapColor(uint32_t color) const;

	/**
	 * @brief Maps a normalized color back into its interger form
	 *
	 * @param color The normalized color
	 * @return uint32_t The integer color
	 */
	uint32_t _MapColorInv(float color) const;
};

}  // namespace zxrenderer

#endif
