#pragma once

#include <ZXRenderer/PayloadObject.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace zxrenderer {

enum class UniformType : uint8_t {
	BOOL,
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4
};

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
	 * @tparam type The type of the uniform variable
	 * @param name The name of the uniform variable
	 * @param data The data pointer to the uniform variable
	 *
	 * @note If the uniform varible already exists, only update its value,
	 * or, allocate new space for the variable and init it
	 */
	template<UniformType type>
	void SetUniform(const std::string &name, uint8_t *data) {
		auto iter = _UniformMap.find(name);
		size_t offset, size;

		if constexpr (type == UniformType::BOOL) {
			size = 1;
		} else if constexpr (type == UniformType::INT) {
			size = 4;
		} else if constexpr (type == UniformType::FLOAT) {
			size = 4;
		} else if constexpr (type == UniformType::VEC2) {
			size = 8;
		} else if constexpr (type == UniformType::VEC3) {
			size = 12;
		} else if constexpr (type == UniformType::VEC4) {
			size = 16;
		} else if constexpr (type == UniformType::MAT2) {
			size = 16;
		} else if constexpr (type == UniformType::MAT3) {
			size = 36;
		} else if constexpr (type == UniformType::MAT4) {
			size = 64;
		}

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
	 * @tparam type The type of the uniform variable
	 * @param name The name of the uniform variable
	 * @param buf The uniform data
	 *
	 */
	template<UniformType type>
	void GetUniform(const std::string &name, uint8_t *buf) {
		auto iter = _UniformMap.find(name);
		size_t offset, size;

		if constexpr (type == UniformType::BOOL) {
			size = 1;
		} else if constexpr (type == UniformType::INT) {
			size = 4;
		} else if constexpr (type == UniformType::FLOAT) {
			size = 4;
		} else if constexpr (type == UniformType::VEC2) {
			size = 8;
		} else if constexpr (type == UniformType::VEC3) {
			size = 12;
		} else if constexpr (type == UniformType::VEC4) {
			size = 16;
		} else if constexpr (type == UniformType::MAT2) {
			size = 16;
		} else if constexpr (type == UniformType::MAT3) {
			size = 36;
		} else if constexpr (type == UniformType::MAT4) {
			size = 64;
		}

		if (iter != _UniformMap.end()) {
			offset = _Data[iter->second];
			std::memcpy(buf, &_Data[offset], size);
		}
	}
};

}  // namespace zxrenderer
