#pragma once

#include <cstdint>

#include <ZXMath/ZXMath.h>

namespace zxrenderer {

namespace ShaderDataType {

using _bool = bool;
using _int = int;
using _float = float;
using vec2 = zxmath::Vector2f;
using vec3 = zxmath::Vector3f;
using vec4 = zxmath::Vector4f;
using mat2 = zxmath::Matrix2f;
using mat3 = zxmath::Matrix3f;
using mat4 = zxmath::Matrix4f;

}  // namespace ShaderDataType

}  // namespace zxrenderer
