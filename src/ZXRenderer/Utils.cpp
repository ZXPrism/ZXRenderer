#include <ZXRenderer/Utils.h>

namespace zxrenderer {

void RGB24ToColorVec(uint32_t rgb, float *color_vec) {
	color_vec[0] = ((rgb >> 16) & 0xff) / 255.0f;
	color_vec[1] = ((rgb >> 8) & 0xff) / 255.0f;
	color_vec[2] = (rgb & 0xff) / 255.0f;
}

uint32_t ColorVec2RGB24(float *color_vec) {
	uint32_t rgb = 0;
	rgb |= static_cast<std::uint32_t>(color_vec[0] * 255) << 16;
	rgb |= static_cast<std::uint32_t>(color_vec[1] * 255) << 8;
	rgb |= static_cast<std::uint32_t>(color_vec[2] * 255);
	return rgb;
}

}  // namespace zxrenderer
