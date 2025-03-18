#pragma once

#include <ZXRenderer/Pipeline.h>
#include <ZXRenderer/PrimitiveType.h>
#include <ZXRenderer/Shader.h>

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
	std::shared_ptr<Shader> _Shader;
	std::optional<PrimitiveType> _PrimitiveType;

public:
	/**
	 * @brief (TODO)
	 *
	 */
	RasterizationPipeline();

	/**
	 * @brief Checks if the pipeline is complete (ready to be used)
	 *
	 */
	virtual bool IsComplete() const override;

	/**
	 * @brief Set the shader of the pipeline
	 *
	 * @param vertex_shader The smart pointer to the shader
	 *
	 * @note For simplicity, different types of shaders are combined into one shader class
	 * @sa Shader
	 */
	void SetShader(std::shared_ptr<Shader> shader);

	/**
	 * @brief Set the primitive type
	 *
	 * @param primitive_type The desired primitive stype
	 */
	void SetPrimitiveType(PrimitiveType primitive_type);
};

}  // namespace zxrenderer
