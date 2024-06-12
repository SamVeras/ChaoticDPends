#include <iostream>
#include <toml++/toml.hpp>
#include "classes.hpp"

/* ------------------------------------------------------------------------ */
/*                              Funções helpers                             */
/* ------------------------------------------------------------------------ */
// Nota: Por essas funções estarem apenas no arquivo .cpp,
// não são "visíveis" por nenhum outro arquivo.
/* ---------------------- TOML array -> Raylib Color ---------------------- */
Color load_color(const toml::v3::node_view<toml::v3::node>& node) {
  return {(unsigned char)node[0].value_or(255), (unsigned char)node[1].value_or(0),
          (unsigned char)node[2].value_or(255), (unsigned char)node[3].value_or(255)};
}

/* ------------------------- Funções de conversão ------------------------- */
float degrees_to_radians(float angle) {
  return angle * (M_PI / 180.f);
}
float radians_to_degrees(float radians) {
  return radians * (180.f / M_PI);
}

/* ------------------------ Funções de interpolação ----------------------- */
float angle_interpolation(float from, float to, float t) {
  return from + t * (to - from);
}

/* ------------------------------------------------------------------------ */
/*                           Construtor de Config                           */
/* ------------------------------------------------------------------------ */

Config::Config() {
  auto config = toml::parse_file("config.toml");

  // Window settings
  title      = config["window"]["title"].value_or("Failed to load title");
  win_width  = config["window"]["width"].value_or(10);
  win_height = config["window"]["height"].value_or(10);
  framerate  = config["window"]["framerate"].value_or(60);

  // Colors
  background_color = load_color(config["colors"]["background"]);

  // Pendulum settings
  pendulum_count = config["pendulum"]["count"].value_or(1);
  damping        = config["pendulum"]["damping"].value_or(0.5f);
}

/* ------------------------------------------------------------------------ */