#pragma once

#include <ZXRenderer/PayloadObject.h>
#include <ZXRenderer/ShaderDataType.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace zxrenderer {

/**
 * @brief A buffer that stores uniform variables
 *
 * Uniform variables are read-only (for shaders) and can be shared across multiple shaders
 * during a render pass
 */
class UniformBuffer : public PayloadObject {
	friend class Renderer;

private:
	std::unordered_map<std::string, size_t> _UniformMap;  // offset_bytes
	std::vector<uint8_t> _Data;

public:
	/**
	 * @brief Add a uniform variable to the buffer
	 *
	 * @tparam T The type of the uniform variable
	 * @param name The name of the uniform variable
	 * @param data The data pointer to the uniform variable
	 *
	 * @note If the uniform varible already exists, only update its value,
	 * or, allocate new space for the variable and init it
	 */
	template<typename T>
	void SetUniform(const std::string &name, uint8_t *data) {
		auto iter = _UniformMap.find(name);
		size_t offset, size = sizeof(T);

		if (iter != _UniformMap.end()) {
			offset = _Data[iter->second];
		} else {
			offset = _Data.size();
			_Data.resize(_Data.size() + size);
		}
		std::memcpy(&_Data[offset], data, size);
	}

	/**
	 * @brief Get a uniform variable from the buffer
	 *
	 * @tparam T The type of the uniform variable
	 * @param name The name of the uniform variable
	 * @param buf The uniform data
	 *
	 */
	template<typename T>
	void GetUniform(const std::string &name, uint8_t *buf) {
		auto iter = _UniformMap.find(name);
		size_t offset, size = sizeof(T);

		if (iter != _UniformMap.end()) {
			offset = _Data[iter->second];
			std::memcpy(buf, &_Data[offset], size);
		}
	}
};

}  // namespace zxrenderer
