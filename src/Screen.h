#pragma once

#include <utility>

namespace zxrenderer {

/**
 * @brief Represents an abstract screen
 * @details `Screen` is capable of displaying images via its framebuffer.
 * The framebuffer must supports writing data at specific memory addresses,
 * while reading data from it is not necessarily required.
 */
class Screen {
public:
	/**
	 * @brief Constructs a new Screen object with initial size
	 *
	 * @param width The width of the screen
	 * @param height The height of the screen
	 */
	Screen(size_t width, size_t height);

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
	 * @param color The color of the pixel, in R8G8B8A8 mode
	 */
	virtual void WritePixel(size_t row, size_t col, size_t color) = 0;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return size_t The color of the pixel, in R8G8B8A8 mode
	 */
	virtual size_t ReadPixel(size_t row, size_t col);

	/**
	 * @brief Get the size of the screen, in order <width, height>
	 *
	 * @return std::pair<size_t, size_t> The size of the screen, in order <width, height>
	 */
	std::pair<size_t, size_t> GetSize() const;

private:
	size_t _Width, _Height;  // screen size
};

}  // namespace zxrenderer
