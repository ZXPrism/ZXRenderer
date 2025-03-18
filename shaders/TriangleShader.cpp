#include <shaders/TriangleShader.h>

#include <ZXRenderer/ShaderDataType.h>

#include <ZXMath/ZXMath.h>

namespace zxrenderer {

using namespace ShaderDataType;

void TriangleShader::Vertex(RenderState &$) {
	auto position = $.Layout<vec3>(VertexBindingPoint::_0);
	vec4 pos{ position[0], position[1], position[2], 1.0f };
	$.Output<vec4>("_Position", pos);
}

void TriangleShader::Fragment(RenderState &$) {
	vec4 color{ 0.0f, 1.0f, 0.0f, 1.0f };
	$.Output<vec4>("_FragColor", color);
}

}  // namespace zxrenderer
