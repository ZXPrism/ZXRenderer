#include <ZXRenderer/DesktopScreen.h>
#include <ZXRenderer/Logger.h>
#include <ZXRenderer/Utils.h>

#include <SDL3/SDL.h>

namespace zxrenderer {

DesktopScreen::DesktopScreen(uint32_t width, uint32_t height)
    : Screen(width, height) {
	_InitFrameBuffer(3);

	SDL_SetAppMetadata(ZXRENDERER_WINDOW_NAME, ZXRENDERER_VERSION, "com.zxprism.zxrenderer");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		gLogger.error("Couldn't initialize SDL: {}", SDL_GetError());
		return;
	}

	_SDLWindow = SDL_CreateWindow(ZXRENDERER_WINDOW_NAME, width, height, 0);
	if (!_SDLWindow) {
		gLogger.error("Couldn't create window: {}", SDL_GetError());
		return;
	}

	_WindowSurface = SDL_GetWindowSurface(_SDLWindow);
	_WindowSurfaceFormat = SDL_GetPixelFormatDetails(_WindowSurface->format);
}

DesktopScreen::~DesktopScreen() {
	SDL_DestroyWindow(_SDLWindow);
	SDL_Quit();
}

void DesktopScreen::_InitFrameBuffer(uint8_t n_color_comp) {
	_FrameBuffer = std::make_shared<RenderTarget>(_Width, _Height);
	_FrameBuffer->AddAttachment(AttachmentType::COLOR, n_color_comp);
	_FrameBuffer->AddAttachment(AttachmentType::DEPTH, 1);
}

void DesktopScreen::WritePixel(uint16_t row, uint16_t col, uint32_t color) {
	float color_vec[3];
	RGB24ToColorVec(color, color_vec);
	_FrameBuffer->WritePixel(AttachmentType::COLOR, row, col, color_vec);
}

uint32_t DesktopScreen::ReadPixel(uint16_t row, uint16_t col) const {
	float color_vec[3];
	_FrameBuffer->ReadPixel(AttachmentType::COLOR, row, col, color_vec);
	return ColorVec2RGB24(color_vec);
}

void DesktopScreen::Clear(uint32_t clear_color) {
	float color_vec[3];
	RGB24ToColorVec(clear_color, color_vec);
	_FrameBuffer->Clear(AttachmentType::COLOR, color_vec);

	constexpr float clear_depth = -std::numeric_limits<float>::max();
	_FrameBuffer->Clear(AttachmentType::DEPTH, &clear_depth);
}

void DesktopScreen::Present() {
	auto pixels = static_cast<Uint32 *>(_WindowSurface->pixels);
	for (uint16_t row = 0; row < _Height; row++) {
		for (uint16_t col = 0; col < _Width; col++) {
			uint32_t color = ReadPixel(row, col);
			Uint32 pixel_color = SDL_MapRGB(_WindowSurfaceFormat, nullptr, color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff);
			pixels[row * _Width + col] = pixel_color;
		}
	}
	SDL_UpdateWindowSurface(_SDLWindow);
}

}  // namespace zxrenderer
