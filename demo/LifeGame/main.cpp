#include <ZXRenderer/WindowsConsoleScreen.h>

#include <chrono>
#include <memory>
#include <random>
#include <thread>

int main(int argc, char *argv[]) {
	auto screen = std::make_unique<zxrenderer::WindowsConsoleScreen>(120, 30);
	auto [width, height] = screen->GetSize();

	std::mt19937_64 engine;
	std::random_device rd;
	engine.seed(rd());
	std::uniform_int_distribution<int> dist(2, std::min(width, height) / 3);

	constexpr int DEAD = 0;
	constexpr int ALIVE = 1;
	std::vector<std::vector<int>> cells_prev(height, std::vector<int>(width, DEAD));
	std::vector<std::vector<int>> cells_curr(height, std::vector<int>(width, DEAD));

	int rule_alive[] = { DEAD, DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD };
	int rule_dead[] = { DEAD, DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD };

	// seed the cells
	std::bernoulli_distribution dist_alive(0.2);
	for (uint16_t row = 0; row < height; row++) {
		for (uint16_t col = 0; col < width; col++) {
			if (dist_alive(engine)) {
				cells_prev[row][col] = ALIVE;
			}
		}
	}

	while (1) {
		// update cells
		for (uint16_t row = 0; row < height; row++) {
			for (uint16_t col = 0; col < width; col++) {
				int alive_cnt = -cells_prev[row][col];  // exclude the current cell itself
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						int nrow = static_cast<int>(row) + i;
						int ncol = static_cast<int>(col) + j;
						if (nrow >= 0 && nrow < height && ncol >= 0 && ncol < width) {
							alive_cnt += cells_prev[nrow][ncol];
						}
					}
				}
				cells_curr[row][col] = (cells_curr[row][col] ? rule_alive[alive_cnt] : rule_dead[alive_cnt]);
			}
		}

		// render cells
		screen->Clear(0x00);
		for (uint16_t row = 0; row < height; row++) {
			for (uint16_t col = 0; col < width; col++) {
				if (cells_curr[row][col] == ALIVE) {
					screen->WritePixel(row, col, 0x08);
				}
			}
		}
		screen->Present();

		// prepare for next update
		cells_curr.swap(cells_prev);

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	return 0;
}
