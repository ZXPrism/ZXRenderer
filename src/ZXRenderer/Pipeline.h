#pragma once

#include <ZXRenderer/PayloadObject.h>

#include <cstdint>

namespace zxrenderer {

enum class PipelineType : uint8_t {
	UNDEFINED,
	RASTERIZATION,
	RAYTRACING
};

/**
 * @brief Represents a rendering pipeline
 *
 */
class Pipeline : public PayloadObject {
	friend class Renderer;

protected:
	PipelineType _Type;

public:
	/**
	 * @brief Destroys the Pipeline object
	 *
	 */
	virtual ~Pipeline() = default;

	/**
	 * @brief Checks if the pipeline is complete (ready to be used)
	 *
	 */
	virtual bool IsComplete() const = 0;
};

}  // namespace zxrenderer
