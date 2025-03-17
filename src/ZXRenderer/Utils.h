#pragma once

#include <cstdint>

namespace zxrenderer {

/**
 * @brief Convert a color in R8G8B8 format to a color vector (each comp. normalized to 1)
 *
 * @param rgb The input color in R8G8A8 format
 * @param color_vec The output color vector
 */
void RGB24ToColorVec(uint32_t rgb, float *color_vec);

/**
 * @brief Convert a color vector (each comp. normalized to 1) to color in R8G8B8 format
 *
 * @param color_vec The input color vector
 * @return uint32_t The output color in R8G8A8 format
 */
uint32_t ColorVec2RGB24(float *color_vec);

}  // namespace zxrenderer
