#pragma once

#include <ZXRenderer/PayloadObject.h>

#include <cstdint>
#include <memory>

namespace zxrenderer {

enum class RenderOp : uint8_t {
	BEGIN_RENDER_PASS,
	BIND_PIPELINE,
	BIND_VERTEX_BUFFER,
	BIND_UNIFORM_BUFFER,
	BIND_RENDER_TARGET,
	DRAW_CALL,
	END_RENDER_PASS
};

struct RenderCommand {
	RenderOp _Op;
	std::shared_ptr<PayloadObject> _PayloadObject;
	size_t _PayloadInt[4];
};

}  // namespace zxrenderer
