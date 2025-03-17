#include <ZXRenderer/Renderer.h>

namespace zxrenderer {

void Renderer::BeginRender() {
}

void Renderer::BeginRenderPass() {
}

void Renderer::BindPipeline(std::shared_ptr<Pipeline> pipeline) {
}

void Renderer::BindVertexBuffer(std::shared_ptr<VertexBuffer> vertex_buffer) {
}

void Renderer::BindUniformBuffer(std::shared_ptr<UniformBuffer> uniform_buffer) {
}

void Renderer::BindRenderTarget(std::shared_ptr<RenderTarget> render_target) {
}

void Renderer::Draw(size_t offset_vertices, size_t n_vertices) {
}

void Renderer::EndRenderPass() {
}

void Renderer::EndRender() {
}

}  // namespace zxrenderer
