#pragma once

namespace zxrenderer {

/**
 * @brief Represents a payload in rendering operations
 *
 * Any class that needs to be packed into rendering commands should inherit from this class
 */
class PayloadObject {
public:
	virtual ~PayloadObject() = default;
};

}  // namespace zxrenderer
