#include <ZXRenderer/Renderer.h>

#include <ZXRenderer/Logger.h>
#include <ZXRenderer/RasterizationPipeline.h>
#include <ZXRenderer/RenderState.h>
#include <ZXRenderer/Utils.h>

#include <ZXMath/Vector.h>
#include <ZXMath/VectorUtils.h>

namespace zxrenderer {

Renderer::Renderer() {
}

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
			pipeline = std::static_pointer_cast<Pipeline>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_VERTEX_BUFFER:
			vertex_buffer = std::static_pointer_cast<VertexBuffer>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_UNIFORM_BUFFER:
			uniform_buffer = std::static_pointer_cast<UniformBuffer>(cmd._PayloadObject);
			break;
		case RenderOp::BIND_RENDER_TARGET:
			render_target = std::static_pointer_cast<RenderTarget>(cmd._PayloadObject);
			break;
		case RenderOp::DRAW_CALL:
			_ExecDrawCall(cmd._PayloadInt[0], cmd._PayloadInt[1]);
			break;
		case RenderOp::END_RENDER_PASS:
			break;
		default:
			break;
		}
	}
}

void Renderer::_ExecDrawCall(size_t offset_vertices, size_t n_vertices) {
	if (pipeline->_Type == PipelineType::RASTERIZATION) {
		auto rst_pipeline = std::static_pointer_cast<RasterizationPipeline>(pipeline);
		if (!rst_pipeline->IsComplete()) {
			gLogger.warn("Incomplete pipeline! Draw call cancelled!");
			return;
		}

		auto shader = rst_pipeline->_Shader;

		auto [w, h] = render_target->GetExtent();

		RenderState render_state;
		render_state._VertexBuffer = vertex_buffer;

		// suppose the primitive is a triangle
		for (size_t i = offset_vertices; i < offset_vertices + n_vertices; i += 3) {
			// v0
			render_state._CurrentVertexID = i;
			shader->Vertex(render_state);
			auto v1 = render_state._OutputVec4["_Position"];

			// v1
			render_state._CurrentVertexID = i + 1;
			shader->Vertex(render_state);
			auto v2 = render_state._OutputVec4["_Position"];

			// v2
			render_state._CurrentVertexID = i + 2;
			shader->Vertex(render_state);
			auto v3 = render_state._OutputVec4["_Position"];

			auto p1_norm = zxmath::NormHomogeneous(v1);
			auto p2_norm = zxmath::NormHomogeneous(v2);
			auto p3_norm = zxmath::NormHomogeneous(v3);

			zxmath::Vector3f p1{ p1_norm[0], p1_norm[1], p1_norm[2] };
			zxmath::Vector3f p2{ p2_norm[0], p2_norm[1], p2_norm[2] };
			zxmath::Vector3f p3{ p3_norm[0], p3_norm[1], p3_norm[2] };

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

			int min_x = static_cast<int>(std::min({ p1[0], p2[0], p3[0] }));
			int max_x = static_cast<int>(std::ceilf(std::max({ p1[0], p2[0], p3[0] })));
			int min_y = static_cast<int>(std::min({ p1[1], p2[1], p3[1] }));
			int max_y = static_cast<int>(std::ceilf(std::max({ p1[1], p2[1], p3[1] })));
			for (int i = min_x; i <= max_x; i++) {
				for (int j = min_y; j <= max_y; j++) {
					zxmath::Vector3f point{ i + 0.5f, j + 0.5f, 0 };
					if (inside(point)) {
						shader->Fragment(render_state);
						auto color = render_state._OutputVec4["_FragColor"].Data();
						render_target->WritePixel(AttachmentType::COLOR, h - 1 - j, i, color);
					}
				}
			}
		}
	}
}

}  // namespace zxrenderer
