#include <ZXRenderer/Screen.h>

namespace zxrenderer {

Screen::Screen(size_t width, size_t height)
    : _Width(width)
    , _Height(height) {
}

std::pair<size_t, size_t> Screen::GetSize() const {
	return { _Width, _Height };
}

}  // namespace zxrenderer
