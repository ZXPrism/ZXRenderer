#pragma once

#include <cstdint>

namespace zxrenderer {

enum class PrimitiveType : uint8_t {
	POINT_LIST,
	TRIANGLE_LIST,
	LINE_LIST,
	LINE_STRIP
};

}
