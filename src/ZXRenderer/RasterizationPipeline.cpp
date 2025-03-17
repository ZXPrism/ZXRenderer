#include <ZXRenderer/RasterizationPipeline.h>

namespace zxrenderer {

bool RasterizationPipeline::IsComplete() const {
	return _VertexShader && _FragmentShader && _PrimitiveType.has_value();
}

void RasterizationPipeline::SetVertexShader(std::shared_ptr<Shader> vertex_shader) {
	_VertexShader = vertex_shader;
}

void RasterizationPipeline::SetFragmentShader(std::shared_ptr<Shader> fragment_shader) {
	_FragmentShader = fragment_shader;
}

void RasterizationPipeline::SetPrimitiveType(PrimitiveType primitive_type) {
	_PrimitiveType = primitive_type;
}

}  // namespace zxrenderer
