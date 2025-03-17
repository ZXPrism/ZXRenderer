#include <ZXRenderer/Logger.h>
#include <ZXRenderer/Renderer.h>
#include <ZXRenderer/Utils.h>

#include <ZXMath/Vector.h>
#include <ZXMath/VectorUtils.h>

namespace zxrenderer {

void Renderer::BeginRender() {
	_CommandQueue.clear();
}

void Renderer::BeginRenderPass() {
	RenderCommand cmd;
	cmd._Op = RenderOp::BEGIN_RENDER_PASS;

	_CommandQueue.push_back(cmd);
}

void Renderer::BindPipeline(std::shared_ptr<Pipeline> pipeline) {
	RenderCommand cmd;
	cmd._Op = RenderOp::BIND_PIPELINE;
	cmd._PayloadObject = pipeline;

	_CommandQueue.push_back(cmd);
}

void Renderer::BindVertexBuffer(std::shared_ptr<VertexBuffer> vertex_buffer) {
	RenderCommand cmd;
	cmd._Op = RenderOp::BIND_VERTEX_BUFFER;
	cmd._PayloadObject = vertex_buffer;

	_CommandQueue.push_back(cmd);
}

void Renderer::BindUniformBuffer(std::shared_ptr<UniformBuffer> uniform_buffer) {
	RenderCommand cmd;
	cmd._Op = RenderOp::BIND_UNIFORM_BUFFER;
	cmd._PayloadObject = uniform_buffer;

	_CommandQueue.push_back(cmd);
}

void Renderer::BindRenderTarget(std::shared_ptr<RenderTarget> render_target) {
	RenderCommand cmd;
	cmd._Op = RenderOp::BIND_RENDER_TARGET;
	cmd._PayloadObject = render_target;

	_CommandQueue.push_back(cmd);
}

void Renderer::Draw(size_t offset_vertices, size_t n_vertices) {
	RenderCommand cmd;
	cmd._Op = RenderOp::DRAW_CALL;
	cmd._PayloadInt[0] = offset_vertices;
	cmd._PayloadInt[1] = n_vertices;

	_CommandQueue.push_back(cmd);
}

void Renderer::EndRenderPass() {
	RenderCommand cmd;
	cmd._Op = RenderOp::END_RENDER_PASS;

	_CommandQueue.push_back(cmd);
}

void Renderer::EndRender() {
	for (auto &cmd : _CommandQueue) {
		switch (cmd._Op) {
		case RenderOp::BEGIN_RENDER_PASS:
			break;
		case RenderOp::BIND_PIPELINE:
			pipeline = std::dynamic_pointer_cast<Pipeline>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_VERTEX_BUFFER:
			vertex_buffer = std::dynamic_pointer_cast<VertexBuffer>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_UNIFORM_BUFFER:
			uniform_buffer = std::dynamic_pointer_cast<UniformBuffer>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_RENDER_TARGET:
			render_target = std::dynamic_pointer_cast<RenderTarget>(cmd._PayloadObject);
			break;
		case RenderOp::DRAW_CALL:
			_ExecDrawCall();
			break;
		case RenderOp::END_RENDER_PASS:
			break;
		default:
			break;
		}
	}
}

void Renderer::_ExecDrawCall() {
	auto [w, h] = render_target->GetExtent();
	size_t n_floats = vertex_buffer->_Data.size();
	for (size_t i = 0; i < n_floats / vertex_buffer->_StepFloats / 3; i++) {
		float *v1 = &vertex_buffer->_Data[i];
		float *v2 = &vertex_buffer->_Data[(i + 1) * vertex_buffer->_StepFloats];
		float *v3 = &vertex_buffer->_Data[(i + 2) * vertex_buffer->_StepFloats];

		zxmath::Vector3f p1{ v1[0], v1[1], v1[2] };
		zxmath::Vector3f p2{ v2[0], v2[1], v2[2] };
		zxmath::Vector3f p3{ v3[0], v3[1], v3[2] };

		auto viewport_t = [&](zxmath::Vector3f &point) {
			point[0] = point[0] * (1.0f * w / 2) + 1.0f * w / 2;
			point[1] = point[1] * (1.0f * h / 2) + 1.0f * h / 2;
		};

		auto inside = [&](const zxmath::Vector3f &point) -> bool {
			auto l1 = p1 - p2;
			auto l2 = p2 - p3;
			auto l3 = p3 - p1;

			auto x1 = point - p1;
			auto x2 = point - p2;
			auto x3 = point - p3;

			int ok = 0;
			if (zxmath::Cross(l1, x1)[2] >= 0) {
				ok |= 1 << 0;
			}
			if (zxmath::Cross(l2, x2)[2] >= 0) {
				ok |= 1 << 1;
			}
			if (zxmath::Cross(l3, x3)[2] >= 0) {
				ok |= 1 << 2;
			}
			return !ok || ok == 7;
		};

		viewport_t(p1);
		viewport_t(p2);
		viewport_t(p3);

		float color[3];
		RGB24ToColorVec(0x00ff0000, color);
		// float color = 4.0f / 8;

		int min_x = static_cast<int>(std::min({ p1[0], p2[0], p3[0] }));
		int max_x = static_cast<int>(std::ceilf(std::max({ p1[0], p2[0], p3[0] })));
		int min_y = static_cast<int>(std::min({ p1[1], p2[1], p3[1] }));
		int max_y = static_cast<int>(std::ceilf(std::max({ p1[1], p2[1], p3[1] })));
		for (int i = min_x; i <= max_x; i++) {
			for (int j = min_y; j <= max_y; j++) {
				zxmath::Vector3f point{ i + 0.5f, j + 0.5f, 0 };
				if (inside(point)) {
					render_target->WritePixel(AttachmentType::COLOR, h - 1 - j, i, color);
				}
			}
		}
	}
}

}  // namespace zxrenderer
