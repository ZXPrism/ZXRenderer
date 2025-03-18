#pragma once

#include <ZXRenderer/Shader.h>

namespace zxrenderer {

/**
 * @brief (TODO)
 *
 */
class TriangleShader : public Shader {
private:
public:
	virtual void Vertex(RenderState &$) override;

	virtual void Fragment(RenderState &$) override;
};

}  // namespace zxrenderer
