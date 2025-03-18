#include <ZXRenderer/Logger.h>
#include <ZXRenderer/RenderTarget.h>

#include <cstring>

namespace zxrenderer {

RenderTarget::RenderTarget(uint32_t width, uint32_t height)
    : _Width(width)
    , _Height(height) {
}

void RenderTarget::AddAttachment(AttachmentType attachment_type, uint8_t step_floats) {
	uint8_t type = static_cast<uint8_t>(attachment_type);
	_Attachments[type].resize(_Width * _Height * step_floats);
	_StepFloats[type] = step_floats;
}

void RenderTarget::WritePixel(AttachmentType attachment_type, uint16_t row, uint16_t col, const float *src) {
	uint8_t type = static_cast<uint8_t>(attachment_type);
	uint8_t step = _StepFloats[type];
	std::memcpy(&_Attachments[type][(row * _Width + col) * step], src, step * sizeof(float));
}

void RenderTarget::ReadPixel(AttachmentType attachment_type, uint16_t row, uint16_t col, float *dest) const {
	uint8_t type = static_cast<uint8_t>(attachment_type);
	uint8_t step = _StepFloats[type];
	std::memcpy(dest, &_Attachments[type][(row * _Width + col) * step], step * sizeof(float));
}

void RenderTarget::Clear(AttachmentType attachment_type, float *src) {
	uint8_t type = static_cast<uint8_t>(attachment_type);
	uint8_t step = _StepFloats[type];

	auto &data = _Attachments[type];
	size_t n_data = data.size();

	for (size_t i = 0; i < n_data; i += step) {
		std::memcpy(&data[i], src, step * sizeof(float));
	}
}

std::pair<uint32_t, uint32_t> RenderTarget::GetExtent() const {
	return { _Width, _Height };
}

}  // namespace zxrenderer
