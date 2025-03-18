#include <shaders/TriangleShader.h>

#include <ZXRenderer/ShaderDataType.h>

#include <ZXMath/ZXMath.h>

namespace zxrenderer {

using namespace ShaderDataType;

void TriangleShader::Vertex(RenderState &$) {
	auto position = $.Layout<vec3>(VertexBindingPoint::_0);
	auto color = $.Layout<vec3>(VertexBindingPoint::_1);

	vec4 pos{ position[0], position[1], position[2], 1.0f };

	$.Output<vec4>("_Position", pos);
	$.Output<vec3>("color", color);
}

void TriangleShader::Fragment(RenderState &$) {
	auto &interp_color = $.Input<vec3>("color");
	vec4 color{ interp_color[0], interp_color[1], interp_color[2], 1.0f };

	$.Output<vec4>("_FragColor", color);
}

}  // namespace zxrenderer
