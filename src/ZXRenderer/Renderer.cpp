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

		std::vector<RenderState> render_state_vec(3);
		for (int i = 0; i < 3; i++) {
			render_state_vec[i]._VertexBuffer = vertex_buffer;
		}
		RenderState render_state_frag;

		// suppose the primitive is a triangle
		for (size_t i = offset_vertices; i < offset_vertices + n_vertices; i += 3) {
			// v0
			render_state_vec[0]._CurrentVertexID = i;
			shader->Vertex(render_state_vec[0]);
			auto v1 = render_state_vec[0]._OutputVec4["_Position"];

			// v1
			render_state_vec[1]._CurrentVertexID = i + 1;
			shader->Vertex(render_state_vec[1]);
			auto v2 = render_state_vec[1]._OutputVec4["_Position"];

			// v2
			render_state_vec[2]._CurrentVertexID = i + 2;
			shader->Vertex(render_state_vec[2]);
			auto v3 = render_state_vec[2]._OutputVec4["_Position"];

			auto inside_canonical_cube = [](const zxmath::Vector4f &point) -> bool {
				float z = std::abs(point[3]);
				return (point[0] >= -z && point[0] <= z &&
				        point[1] >= -z && point[1] <= z &&
				        point[2] >= -z && point[2] <= z);
			};

			if (!inside_canonical_cube(v1) && !inside_canonical_cube(v2) && !inside_canonical_cube(v3)) {
				continue;
			}

			auto p1_norm = zxmath::NormHomogeneous(v1);
			auto p2_norm = zxmath::NormHomogeneous(v2);
			auto p3_norm = zxmath::NormHomogeneous(v3);

			zxmath::Vector3f p1{ p1_norm[0], p1_norm[1], p1_norm[2] };
			zxmath::Vector3f p2{ p2_norm[0], p2_norm[1], p2_norm[2] };
			zxmath::Vector3f p3{ p3_norm[0], p3_norm[1], p3_norm[2] };

			// viewport transform
			auto viewport_t = [&](zxmath::Vector3f &point) {
				point[0] = point[0] * (1.0f * w / 2) + 1.0f * w / 2;
				point[1] = point[1] * (1.0f * h / 2) + 1.0f * h / 2;
			};

			viewport_t(p1);
			viewport_t(p2);
			viewport_t(p3);

			// compute bounding box
			int min_x = static_cast<int>(std::max(0.0f, std::min({ p1[0], p2[0], p3[0] })));
			int max_x = static_cast<int>(std::min(1.0f * w, std::ceilf(std::max({ p1[0], p2[0], p3[0] }))));
			int min_y = static_cast<int>(std::max(0.0f, std::min({ p1[1], p2[1], p3[1] })));
			int max_y = static_cast<int>(std::min(1.0f * h, std::ceilf(std::max({ p1[1], p2[1], p3[1] }))));

			// rasterization
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

			auto barycentric = [&](const zxmath::Vector3f &point) -> std::tuple<float, float, float, float> {
				float alpha{}, beta{}, gamma{}, z{};
				auto x = point[0], y = point[1];
				alpha = (-(x - p2[0]) * (p3[1] - p2[1]) + (y - p2[1]) * (p3[0] - p2[0])) /
				        (-(p1[0] - p2[0]) * (p3[1] - p2[1]) + (p1[1] - p2[1]) * (p3[0] - p2[0]));
				beta = (-(x - p3[0]) * (p1[1] - p3[1]) + (y - p3[1]) * (p1[0] - p3[0])) /
				       (-(p2[0] - p3[0]) * (p1[1] - p3[1]) + (p2[1] - p3[1]) * (p1[0] - p3[0]));
				gamma = 1.0f - alpha - beta;
				z = alpha * p1[2] + beta * p2[2] + gamma * p3[2];
				// NEED CORRECTION!!
				return { alpha, beta, gamma, z };
			};

			auto interp = [&](float alpha, float beta, float gamma) {
				// gLogger.warn("using {} {} {}", alpha, beta, gamma);

				for (auto &[name, val] : render_state_vec[0]._OutputFloat) {
					auto &target = render_state_frag._OutputFloat[name];
					auto &v1 = val;
					auto &v2 = render_state_vec[1]._OutputFloat[name];
					auto &v3 = render_state_vec[2]._OutputFloat[name];
					target = alpha * v1 + beta * v2 + gamma * v3;
				}

				for (auto &[name, val] : render_state_vec[0]._OutputVec2) {
					auto &target = render_state_frag._OutputVec2[name];
					auto &v1 = val;
					auto &v2 = render_state_vec[1]._OutputVec2[name];
					auto &v3 = render_state_vec[2]._OutputVec2[name];
					target = alpha * v1 + beta * v2 + gamma * v3;
				}

				for (auto &[name, val] : render_state_vec[0]._OutputVec3) {
					auto &target = render_state_frag._OutputVec3[name];
					auto &v1 = val;
					auto &v2 = render_state_vec[1]._OutputVec3[name];
					auto &v3 = render_state_vec[2]._OutputVec3[name];
					target = alpha * v1 + beta * v2 + gamma * v3;
				}

				for (auto &[name, val] : render_state_vec[0]._OutputVec4) {
					auto &target = render_state_frag._OutputVec4[name];
					auto &v1 = val;
					auto &v2 = render_state_vec[1]._OutputVec4[name];
					auto &v3 = render_state_vec[2]._OutputVec4[name];
					target = alpha * v1 + beta * v2 + gamma * v3;
				}
			};

			for (int i = min_x; i <= max_x; i++) {
				for (int j = min_y; j <= max_y; j++) {
					zxmath::Vector3f point{ i + 0.5f, j + 0.5f, 0.0f };

					if (inside(point)) {
						auto [alpha, beta, gamma, z] = barycentric(point);

						float recorded_depth;
						render_target->ReadPixel(AttachmentType::DEPTH, h - 1 - j, i, &recorded_depth);
						if (z < recorded_depth) {
							continue;
						}
						render_target->WritePixel(AttachmentType::DEPTH, h - 1 - j, i, &z);

						// interpolate output attributes of VS
						interp(alpha, beta, gamma);

						shader->Fragment(render_state_frag);

						auto color = render_state_frag._OutputVec4["_FragColor"].Data();
						render_target->WritePixel(AttachmentType::COLOR, h - 1 - j, i, color);
					}
				}
			}
		}
	}
}

}  // namespace zxrenderer
