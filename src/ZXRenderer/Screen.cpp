#include <ZXRenderer/Screen.h>

namespace zxrenderer {

Screen::Screen(uint32_t width, uint32_t height)
    : _Width(width)
    , _Height(height) {
}

std::pair<uint32_t, uint32_t> Screen::GetSize() const {
	return { _Width, _Height };
}

std::shared_ptr<RenderTarget> Screen::GetRenderTarget() {
	return _FrameBuffer;
}

}  // namespace zxrenderer
