#pragma once

#include <ZXRenderer/ShaderDataType.h>
#include <ZXRenderer/VertexBuffer.h>

#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace zxrenderer {

/**
 * @brief (TODO)
 *
 */
class RenderState {

	friend class Renderer;

private:
	size_t _CurrentVertexID;
	std::shared_ptr<VertexBuffer> _VertexBuffer;

	std::unordered_map<std::string, ShaderDataType::_float> _OutputFloat;
	std::unordered_map<std::string, ShaderDataType::vec2> _OutputVec2;
	std::unordered_map<std::string, ShaderDataType::vec3> _OutputVec3;
	std::unordered_map<std::string, ShaderDataType::vec4> _OutputVec4;

public:
	template<typename T>
	    requires(std::is_same_v<T, ShaderDataType::_float> ||
	             std::is_same_v<T, ShaderDataType::vec2> ||
	             std::is_same_v<T, ShaderDataType::vec3> ||
	             std::is_same_v<T, ShaderDataType::vec4>)
	T Layout(VertexBindingPoint binding_point) const {
		if constexpr (std::is_same_v<T, ShaderDataType::_float>) {
			return *_VertexBuffer->GetVertexAttribute(binding_point, _CurrentVertexID);
		} else {
			return T{ _VertexBuffer->GetVertexAttribute(binding_point, _CurrentVertexID) };
		}
	}

	template<typename T>
	    requires(std::is_same_v<T, ShaderDataType::_float> ||
	             std::is_same_v<T, ShaderDataType::vec2> ||
	             std::is_same_v<T, ShaderDataType::vec3> ||
	             std::is_same_v<T, ShaderDataType::vec4>)
	const T &Input(const std::string &name) {
		if constexpr (std::is_same_v<T, ShaderDataType::_float>) {
			return _OutputFloat[name];
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec2>) {
			return _OutputVec2[name];
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec3>) {
			return _OutputVec3[name];
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec4>) {
			return _OutputVec4[name];
		}
		return {};
	}

	template<typename T>
	    requires(std::is_same_v<T, ShaderDataType::_float> ||
	             std::is_same_v<T, ShaderDataType::vec2> ||
	             std::is_same_v<T, ShaderDataType::vec3> ||
	             std::is_same_v<T, ShaderDataType::vec4>)
	void Output(const std::string &name, const T &src) {
		if constexpr (std::is_same_v<T, ShaderDataType::_float>) {
			_OutputFloat[name] = src;
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec2>) {
			_OutputVec2[name] = src;
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec3>) {
			_OutputVec3[name] = src;
		} else if constexpr (std::is_same_v<T, ShaderDataType::vec4>) {
			_OutputVec4[name] = src;
		}
	}
};

}  // namespace zxrenderer
