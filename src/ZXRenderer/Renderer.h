#pragma once

#include <ZXRenderer/Pipeline.h>
#include <ZXRenderer/RenderTarget.h>
#include <ZXRenderer/UniformBuffer.h>
#include <ZXRenderer/VertexBuffer.h>

namespace zxrenderer {

/**
 * @brief The heart of ZXRenderer, most of the rendering logics are implemented here
 *
 */
class Renderer {
private:
public:
	/**
	 * @brief Begin a rendering procedure and start recording the rendering commands
	 *
	 * This function should be called only once before any rendering operations in each frame,
	 * it will init related structrues, free unused resources to get ready
	 * for the subsequent rendering procedure.
	 */
	void BeginRender();

	/**
	 * @brief Begin a render pass
	 *
	 * @note This function must be paired with `EndRenderPass()`,
	 * incorrect pairing will cause undefined behavior
	 * @sa EndRenderPass()
	 */
	void BeginRenderPass();

	/**
	 * @brief Bind the pipeline to be used in the current render pass
	 *
	 * @param pipeline The smart pointer to the pipeline
	 */
	void BindPipeline(std::shared_ptr<Pipeline> pipeline);

	/**
	 * @brief Bind the vertex buffer (INPUT) to be used in the current render pass
	 *
	 * @param vertex_buffer The smart pointer to the vertex buffer
	 * @note You can only bind one vertex buffer at a time, re-binding will
	 * override the original one
	 */
	void BindVertexBuffer(std::shared_ptr<VertexBuffer> vertex_buffer);

	/**
	 * @brief Bind the uniform buffer to be used in the current render pass
	 *
	 * @param uniform_buffer The smart pointer to the uniform buffer
	 * @note You can only bind one uniform buffer at a time, re-binding will
	 * override the original one
	 */
	void BindUniformBuffer(std::shared_ptr<UniformBuffer> uniform_buffer);

	/**
	 * @brief Bind the render target (OUTPUT) to be used in the current render pass
	 *
	 * @param uniform_buffer The smart pointer to the uniform buffer
	 * @note You can only bind one render target at a time, re-binding will
	 * override the original one
	 */
	void BindRenderTarget(std::shared_ptr<RenderTarget> render_target);

	/**
	 * @brief Issue a draw call
	 *
	 * @param offset_vertices The starting index of the vertex buffer
	 * @param n_vertices The number of vertices to be rendered
	 * @note The primitive type should be specified in the pipeline
	 */
	void Draw(size_t offset_vertices, size_t n_vertices);

	/**
	 * @brief End a render pass
	 *
	 * @note This function must be paired with `BeginRenderPass()`,
	 * incorrect pairing will cause undefined behavior
	 * @sa BeginRenderPass()
	 */
	void EndRenderPass();

	/**
	 * @brief End the current rendering procedure, submitting rendering commands
	 *
	 */
	void EndRender();

private:
};

}  // namespace zxrenderer
