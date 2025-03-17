#pragma once

#include <ZXRenderer/PayloadObject.h>

namespace zxrenderer {

/**
 * @brief Represents a rendering pipeline
 *
 */
class Pipeline : public PayloadObject {
protected:
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
