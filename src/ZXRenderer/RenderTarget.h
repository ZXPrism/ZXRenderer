#pragma once

#include <ZXRenderer/PayloadObject.h>

#include <array>
#include <cstdint>
#include <vector>

namespace zxrenderer {

enum class AttachmentType : uint8_t {
	COLOR,
	DEPTH,
	NORMAL,
	CUSTOM
};

/**
 * @brief Render target is an abstract interface that receives the output of the pipeline
 *
 * It can have multiple attachments, such as color attachment and depth attachment.
 *
 * For simplicity, only 4 attachments are allowed.
 */
class RenderTarget : public PayloadObject {
	friend class Renderer;

private:
	std::array<std::vector<float>, 4> _Attachments;
	std::array<uint8_t, 3> _StepFloats;
	uint32_t _Width, _Height;

public:
	RenderTarget(uint32_t width, uint32_t height);

	/**
	 * @brief Adds a new attachment
	 *
	 * @param attachment_type The type of the attachment
	 * @param step_floats The number of floats used for each pixel
	 * @note Each type of attachment can have at most one active attachment at a time
	 * Adding an attachment will clear the existing one of its type (if any)
	 */
	void AddAttachment(AttachmentType attachment_type, uint8_t step_floats);

	/**
	 * @brief Writes data to the target pixel
	 *
	 * Firstly calculate the starting address `(row * _Width + col) * step_floats`
	 * then copy `step_floats` floats from `src` to that address
	 *
	 * @param attachment_type The target attachment
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @param src The data to write
	 *
	 * @note No bounds checking
	 */
	void WritePixel(AttachmentType attachment_type, uint16_t row, uint16_t col, const float *src);

	/**
	 * @brief Reads data from the target pixel
	 *
	 * Firstly calculate the starting address `(row * _Width + col) * step_floats`
	 * then copy `step_floats` floats from that address to `dest`
	 *
	 * @param attachment_type The target attachment
	 * @param row The vertical offset, in pixels
	 * @param col The horizontal offset, in pixels
	 * @param dest The read buffer
	 *
	 * @note No bounds checking
	 */
	void ReadPixel(AttachmentType attachment_type, uint16_t row, uint16_t col, float *dest) const;

	/**
	 * @brief Clear the target attachment
	 *
	 * @param attachment_type The target attachment
	 * @param src The clear value
	 */
	void Clear(AttachmentType attachment_type, float *src);

	/**
	 * @brief Get the extent of the render target buffer, in order <width, height>
	 *
	 * @return std::pair<uint32_t, uint32_t> The extent of the render target buffer, in order <width, height>
	 */
	std::pair<uint32_t, uint32_t> GetExtent() const;
};

}  // namespace zxrenderer
