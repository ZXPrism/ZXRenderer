#pragma once

#include <ZXRenderer/RenderTarget.h>

#include <cstdint>
#include <memory>
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
	uint32_t _Width, _Height;  // screen size
	std::shared_ptr<RenderTarget> _FrameBuffer;

protected:
	/**
	 * @brief Inits the framebuffer
	 *
	 * @param n_color_comp The number of color components
	 *
	 * @note Whether to use double buffering is up to the implementation
	 * We only ensure that one screen must have at least one buffer
	 */
	virtual void _InitFrameBuffer(uint8_t n_color_comp) = 0;

public:
	/**
	 * @brief Constructs a new Screen object with initial size
	 *
	 * Create a render target with a color attachment, in RGB format
	 *
	 * @param width The width of the screen
	 * @param height The height of the screen
	 */
	Screen(uint32_t width, uint32_t height);

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
	 * @param color The color of the pixel
	 */
	virtual void WritePixel(uint16_t row, uint16_t col, uint32_t color) = 0;

	/**
	 * @brief Reads color from the target pixel
	 *
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @return uint32_t The color of the pixel
	 */
	virtual uint32_t ReadPixel(uint16_t row, uint16_t col) const = 0;

	/**
	 * @brief Clears the back buffer with desired color
	 *
	 * @param clear_color The clear color
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

	/**
	 * @brief Get the pointer to the screen's render target (back buffer)
	 *
	 */
	std::shared_ptr<RenderTarget> GetRenderTarget();
};

}  // namespace zxrenderer
