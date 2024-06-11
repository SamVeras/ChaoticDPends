#pragma once
#include <raylib.h>
#include <cstddef>

namespace Setup {
constexpr char*  title      = (char*)"Pendulos";
constexpr size_t win_width  = 600;
constexpr size_t win_height = 600;
constexpr size_t framerate  = 60;
constexpr Color  background = {0, 0, 0, 255};
};  // namespace Setup

namespace Global {
constexpr float gravity = 9.8f;
constexpr float damping = 0.9999;
};  // namespace Global