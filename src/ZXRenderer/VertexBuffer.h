#pragma once

#include <ZXRenderer/PayloadObject.h>

#include <array>
#include <cstdint>
#include <vector>

namespace zxrenderer {

enum class VertexBindingPoint : uint8_t {
	_0,
	_1,
	_2,
	_3,
	_4
};

/**
 * @brief Represents a buffer that stores vertex attributes (e.g. positions, colors, normals..)
 *
 */
class VertexBuffer : public PayloadObject {
	friend class Renderer;

private:
	std::vector<float> _Data;
	std::array<std::pair<uint8_t, uint8_t>, 16> _BindingPoints;  // <offset_floats, n_floats>

	uint8_t _StepFloats;

public:
	/**
	 * @brief Constructs a new Vertex Buffer object
	 *
	 * @param data The vertices data
	 * @param step_floats The number of floats for one vertex
	 */
	VertexBuffer(const std::vector<float> &data, uint8_t step_floats);

	/**
	 * @brief Specify a vertex attribute
	 *
	 * @param binding_point The index of binding point
	 * @param offset_floats The offset within one vertex, in floats
	 * @param n_floats The length of the attibute, in floats
	 *
	 * @note Out of bounds or overlap between attributes will cause undefined behavior
	 */
	void BindAttribute(VertexBindingPoint binding_point, uint8_t offset_floats, uint8_t n_floats);
};

}  // namespace zxrenderer
