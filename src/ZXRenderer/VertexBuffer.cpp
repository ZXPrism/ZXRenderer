#include <ZXRenderer/VertexBuffer.h>

namespace zxrenderer {

VertexBuffer::VertexBuffer(const std::vector<float> &data, const std::vector<size_t> &index, uint8_t step_floats)
    : _VertexData(data)
    , _VertexIndex(index)
    , _StepFloats(step_floats) {
	for (auto &[offset_floats, n_floats] : _BindingPoints) {
		n_floats = 0;
	}
}

void VertexBuffer::BindAttribute(VertexBindingPoint binding_point,
                                 uint8_t offset_floats,
                                 uint8_t n_floats) {
	// TODO: check validity of the parameters
	auto bp = static_cast<uint8_t>(binding_point);
	_BindingPoints[bp] = { offset_floats, n_floats };
}

float *VertexBuffer::GetVertexAttribute(VertexBindingPoint binding_point, size_t vertex_id) {
	auto bp = static_cast<uint8_t>(binding_point);
	return &_VertexData[_VertexIndex[vertex_id] * _StepFloats + _BindingPoints[bp].first];
}

}  // namespace zxrenderer
