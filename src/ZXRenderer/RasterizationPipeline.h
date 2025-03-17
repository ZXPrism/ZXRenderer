#pragma once

#include <ZXRenderer/PrimitiveType.h>
#include <ZXRenderer/Shader.h>
#include <zxrenderer/Pipeline.h>

#include <memory>
#include <optional>

namespace zxrenderer {

/**
 * @brief Represents a rasterization based rendering pipeline
 *
 */
class RasterizationPipeline : public Pipeline {
	friend class Renderer;

private:
	std::shared_ptr<Shader> _VertexShader;
	std::shared_ptr<Shader> _FragmentShader;
	std::optional<PrimitiveType> _PrimitiveType;

public:
	/**
	 * @brief Checks if the pipeline is complete (ready to be used)
	 *
	 */
	virtual bool IsComplete() const override;

	/**
	 * @brief Set the vertex shader of the pipeline
	 *
	 * @param vertex_shader The smart pointer to the vertex shader
	 */
	void SetVertexShader(std::shared_ptr<Shader> vertex_shader);

	/**
	 * @brief Set the fragment shader of the pipeline
	 *
	 * @param fragment_shader The smart pointer to the fragment shader
	 */
	void SetFragmentShader(std::shared_ptr<Shader> fragment_shader);

	/**
	 * @brief Set the primitive type
	 *
	 * @param primitive_type The desired primitive stype
	 */
	void SetPrimitiveType(PrimitiveType primitive_type);
};

}  // namespace zxrenderer
