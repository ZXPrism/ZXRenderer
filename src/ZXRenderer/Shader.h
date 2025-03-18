#pragma once

#include <ZXRenderer/RenderState.h>

namespace zxrenderer {

/**
 * @brief Shader interface
 *
 * To add custom shaders, you can write your own shader class
 * derived from this class and implement the virt. functions
 */
class Shader {
private:
public:
	/**
	 * @brief Destroy the Shader object
	 *
	 */
	virtual ~Shader() = default;

	virtual void Vertex(RenderState &$) = 0;
	//{
	// 	// auto & vert = Layout(binding_point = 1, type = ?);
	// 	// // ...
	// 	// auto &... = Uniform(name = ..., type = ...);

	// 	// Output(...);
	// 	// Output(...);
	// }

	virtual void Fragment(RenderState &$) = 0;
	//{
	// 	// auto &... = Input(...);
	// 	// Output(...);
	// }
};

}  // namespace zxrenderer
