#ifdef _WIN32

#	include <ZXRenderer/Logger.h>
#	include <ZXRenderer/WindowsConsoleScreen.h>

#	include <Windows.h>

namespace zxrenderer {

WindowsConsoleScreen::WindowsConsoleScreen(uint16_t width, uint16_t height)
    : Screen(width, height) {
	_FrontBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	_BackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, nullptr);

	if (_BackBuffer == INVALID_HANDLE_VALUE) {
		gLogger.error("Failed to create the back buffer!");
		return;
	}

	COORD buffer_size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleScreenBufferSize(_FrontBuffer, buffer_size);
	SetConsoleScreenBufferSize(_BackBuffer, buffer_size);

	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = false;
	cursor_info.dwSize = 3;
	SetConsoleCursorInfo(_FrontBuffer, &cursor_info);
	SetConsoleCursorInfo(_BackBuffer, &cursor_info);

	_ColorMap = std::string(16, ' ');
	_ColorMap[0] = ' ';
	_ColorMap[1] = '.';
	_ColorMap[2] = ':';
	_ColorMap[3] = '-';
	_ColorMap[4] = '=';
	_ColorMap[5] = '+';
	_ColorMap[6] = '*';
	_ColorMap[7] = '#';
	_ColorMap[8] = '@';
}

WindowsConsoleScreen::~WindowsConsoleScreen() {
	CloseHandle(_BackBuffer);
}

void WindowsConsoleScreen::WritePixel(uint16_t row, uint16_t col, uint32_t color) {
	DWORD n_written;
	COORD write_coord = { static_cast<SHORT>(col), static_cast<SHORT>(row) };
	WriteConsoleOutputCharacter(_BackBuffer, &_ColorMap[color], 1, write_coord, &n_written);
}

uint32_t WindowsConsoleScreen::ReadPixel(uint16_t row, uint16_t col) const {
	char color;
	DWORD n_read;
	COORD read_coord = { static_cast<SHORT>(col), static_cast<SHORT>(row) };
	ReadConsoleOutputCharacter(_BackBuffer, &color, 1, read_coord, &n_read);

	return static_cast<uint32_t>(color);
}

void WindowsConsoleScreen::Clear(uint32_t clear_color) {
	for (uint16_t row = 0; row < _Height; row++) {
		for (uint16_t col = 0; col < _Width; col++) {
			WritePixel(row, col, clear_color);
		}
	}
}

void WindowsConsoleScreen::Present() {
	std::swap(_FrontBuffer, _BackBuffer);
	SetConsoleActiveScreenBuffer(_FrontBuffer);
}

}  // namespace zxrenderer

#endif
