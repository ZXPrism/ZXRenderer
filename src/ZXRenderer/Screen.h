#pragma once

#include <cstdint>
#include <utility>

namespace zxrenderer {

/**
 * @brief Represents an abstract screen
 *
 * @details `Screen` is capable of displaying images via its framebuffer.
 * The framebuffer must supports writing data at specific memory addresses,
 * while reading data from it is not necessarily required.
 */
class Screen {
protected:
	uint16_t _Width, _Height;  // screen size

public:
	/**
	 * @brief Constructs a new Screen object with initial size
	 *
	 * @param width The width of the screen
	 * @param height The height of the screen
	 */
	Screen(uint16_t width, uint16_t height);

	/**
	 * @brief Destroys the Screen object
	 *
	 */
	virtual ~Screen() = default;

	/**
	 * @brief Writes color to the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @param color The color of the pixel, in R8G8B8A8 format
	 */
	virtual void WritePixel(uint16_t row, uint16_t col, uint32_t color) = 0;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return uint32_t The color of the pixel, in R8G8B8A8 format
	 */
	virtual uint32_t ReadPixel(uint16_t row, uint16_t col) const = 0;

	/**
	 * @brief Clears the back buffer with desired color
	 *
	 * @param clear_color The clear color, in R8G8B8A8 format
	 */
	virtual void Clear(uint32_t clear_color) = 0;

	/**
	 * @brief Presents the image on the back buffer to the screen
	 *
	 * @note This opeation is often called "swap buffers"
	 */
	virtual void Present() = 0;

	/**
	 * @brief Get the size of the screen, in order <width, height>
	 *
	 * @return std::pair<uint32_t, uint32_t> The size of the screen, in order <width, height>
	 */
	std::pair<uint32_t, uint32_t> GetSize() const;
};

}  // namespace zxrenderer
