#include <ZXRenderer/Screen.h>

namespace zxrenderer {

Screen::Screen(uint16_t width, uint16_t height)
    : _Width(width)
    , _Height(height) {
}

std::pair<uint32_t, uint32_t> Screen::GetSize() const {
	return { _Width, _Height };
}

}  // namespace zxrenderer
