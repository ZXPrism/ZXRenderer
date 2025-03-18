#pragma once

#include <zxrenderer/Pipeline.h>

#include <memory>
#include <optional>

namespace zxrenderer {

/**
 * @brief Represents a ray tracing based rendering pipeline
 *
 */
class RayTracingPipeline : public Pipeline {
private:
public:
	bool IsComplete() const;
};

}  // namespace zxrenderer
