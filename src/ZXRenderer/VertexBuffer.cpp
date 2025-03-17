#include <ZXRenderer/VertexBuffer.h>

namespace zxrenderer {

VertexBuffer::VertexBuffer(const std::vector<float> &data, uint8_t step_floats)
    : _Data(data)
    , _StepFloats(step_floats) {
}

void VertexBuffer::BindAttribute(VertexBindingPoint binding_point,
                                 uint8_t offset_floats,
                                 uint8_t n_floats) {
	// TODO: check validity of the parameters
	auto bp = static_cast<uint8_t>(binding_point);
	_BindingPoints[bp] = { offset_floats, n_floats };
}

}  // namespace zxrenderer
