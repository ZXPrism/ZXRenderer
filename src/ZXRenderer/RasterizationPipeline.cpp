#include <ZXRenderer/RasterizationPipeline.h>

namespace zxrenderer {

RasterizationPipeline::RasterizationPipeline() {
	_Type = PipelineType::RASTERIZATION;
}

bool RasterizationPipeline::IsComplete() const {
	return _Shader && _PrimitiveType.has_value();
}

void RasterizationPipeline::SetShader(std::shared_ptr<Shader> shader) {
	_Shader = shader;
}

void RasterizationPipeline::SetPrimitiveType(PrimitiveType primitive_type) {
	_PrimitiveType = primitive_type;
}

}  // namespace zxrenderer
