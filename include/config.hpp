#pragma once
#include <raylib.h>
#include <string>

class Config {
 public:
  std::string title;
  int         win_width, win_height, framerate;
  Color       background_color;

  Vector2 origin;
  size_t  count;
  float   damping;

  int    length_1, length_2;
  float  mass_1, mass_2;
  double initial_theta_1, initial_theta_2;  // Angulos iniciais
  double final_theta_1, final_theta_2;      // Angulos finais
  Color  initial_color_1, initial_color_2;  // Cores iniciais
  Color  final_color_1, final_color_2;      // Cores finais

  bool        show_fps, debug_mode, paused, show_timer, camera_debug, maximized;
  std::string font_path;
  float       font_size;
  Font        font;

 public:
  void init_font();

  Config() = delete;
  Config(const std::string& file_path);
  ~Config() = default;
};
