#include <ZXRenderer/RasterizationPipeline.h>

namespace zxrenderer {

bool RasterizationPipeline::IsComplete() const {
	return _VertexShader && _FragmentShader && _PrimitiveType.has_value();
}

}  // namespace zxrenderer
