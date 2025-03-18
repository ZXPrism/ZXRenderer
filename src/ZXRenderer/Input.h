#pragma once

#include <functional>

namespace zxrenderer {

class Input {
private:
public:
	/**
	 * @brief
	 *
	 * @return Input&
	 */
	static Input &GetInstance();

	/**
	 * @brief Destroy the Input object
	 *
	 */
	virtual ~Input() = default;

	/**
	 * @brief
	 *
	 */
	virtual void PollEvents() = 0;
};

}  // namespace zxrenderer
