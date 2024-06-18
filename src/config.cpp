#include "config.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <toml++/toml.hpp>
#include "functions.hpp"

/* ------------------------------------------------------------------------ */
/*                           Construtor de Config                           */
/* ------------------------------------------------------------------------ */

Config::Config(const std::string& file_path) : paused(false) {
  auto config = toml::parse_result{};

  try {
    config = toml::parse_file(file_path);
  } catch (const toml::parse_error& err) {
    std::cerr << "AVISO: Arquivo '" << file_path << "' inexistente!\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  // Window settings
  title            = config["window"]["title"].value_or("Failed to load title");
  win_width        = config["window"]["width"].value_or(300);
  win_height       = config["window"]["height"].value_or(300);
  framerate        = config["window"]["framerate"].value_or(60);
  background_color = load_color(config["window"]["background"]);
  font_path        = config["window"]["font"].value_or("res/romulus.png");
  font_size        = config["window"]["font_size"].value_or(10);

  // Debug settings
  show_fps     = config["debug"]["show_fps"].value_or(false);
  debug_mode   = config["debug"]["debug_mode"].value_or(false);
  show_timer   = config["debug"]["show_timer"].value_or(true);
  camera_debug = config["debug"]["camera_debug"].value_or(false);

  // General settings
  origin.x = config["pendulums"]["origin"][0].value_or(100.f);
  origin.y = config["pendulums"]["origin"][1].value_or(100.f);
  count    = config["pendulums"]["count"].value_or(10);
  damping  = config["pendulums"]["damping"].value_or(0.01f);

  // First arm
  length_1        = config["first_arm"]["length"].value_or(100);
  mass_1          = config["first_arm"]["mass"].value_or(1.f);
  initial_theta_1 = config["first_arm"]["initial_theta"].value_or(rand_angle());
  final_theta_1   = config["first_arm"]["final_theta"].value_or(initial_theta_1 + 0.001);
  initial_color_1 = load_color(config["first_arm"]["initial_color"]);
  final_color_1   = load_color(config["first_arm"]["final_color"]);

  // Second arm
  length_2        = config["second_arm"]["length"].value_or(100);
  mass_2          = config["second_arm"]["mass"].value_or(1.f);
  initial_theta_2 = config["second_arm"]["initial_theta"].value_or(rand_angle());
  final_theta_2   = config["second_arm"]["final_theta"].value_or(initial_theta_2 + 0.001);
  initial_color_2 = load_color(config["second_arm"]["initial_color"]);
  final_color_2   = load_color(config["second_arm"]["final_color"]);

  // Conversão
  initial_theta_1 = degrees_to_radians(initial_theta_1);
  final_theta_1   = degrees_to_radians(final_theta_1);
  initial_theta_2 = degrees_to_radians(initial_theta_2);
  final_theta_2   = degrees_to_radians(final_theta_2);

  // Sanity checks
  if (damping < 0.f || damping > 1.f)
    damping = 0.5f;
  if (count < 1)
    count = 0;
  if (font_size < 1)
    font_size = 1;
  if (framerate < 10)
    framerate = 10;
  if (win_width < 50)
    win_width = 50;
  if (win_height < 50)
    win_height = 50;
}

void Config::init_font() {
  // Carrega a fonte de forma diferente, caso seja PNG
  if (IsFileExtension(font_path.c_str(), ".png")) {
    font      = LoadFont(font_path.c_str());
    font_size = font.baseSize;
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
  } else {
    font = LoadFontEx(font_path.c_str(), int(font_size), NULL, 1024);
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
  }
}
/* ------------------------------------------------------------------------ */