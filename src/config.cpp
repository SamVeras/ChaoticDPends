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

/* Interpola linearmente entre dois ângulos por um p(eso) entre 0.0 e 1.0 */
float angle_interpolation(float from, float to, float p) {
  return from + (to - from) * p;
}

/* Interpola entre duas cores por um p(eso) entre 0.0 e 1.0 */
Color color_interpolation(const Color& from, const Color& to, float p) {
  unsigned char r = (unsigned char)(from.r + (to.r - from.r) * p);
  unsigned char g = (unsigned char)(from.g + (to.g - from.g) * p);
  unsigned char b = (unsigned char)(from.b + (to.b - from.b) * p);
  unsigned char a = (unsigned char)(from.a + (to.a - from.a) * p);
  return {r, g, b, a};
}
/* ------------------------------------------------------------------------ */
/*                           Construtor de Config                           */
/* ------------------------------------------------------------------------ */

Config::Config() {
  auto config = toml::parse_file("config.toml");

  // Window settings
  title            = config["window"]["title"].value_or("Failed to load title");
  win_width        = config["window"]["width"].value_or(10);
  win_height       = config["window"]["height"].value_or(10);
  framerate        = config["window"]["framerate"].value_or(60);
  background_color = load_color(config["window"]["background"]);

  // General settings
  origin  = {config["pendulums"]["origin"][0].value_or(0.f),
             config["pendulums"]["origin"][1].value_or(0.f)};
  count   = config["pendulums"]["count"].value_or(1);
  damping = config["pendulums"]["damping"].value_or(0.5f);

  // First arm
  length_1        = config["first_arm"]["length"].value_or(100);
  mass_1          = config["first_arm"]["mass"].value_or(1.f);
  initial_theta_1 = config["first_arm"]["initial_theta"].value_or(0.f);
  final_theta_1   = config["first_arm"]["final_theta"].value_or(0.f);
  initial_color_1 = load_color(config["first_arm"]["initial_color"]);
  final_color_1   = load_color(config["first_arm"]["final_color"]);

  // Second arm
  length_2        = config["second_arm"]["length"].value_or(100);
  mass_2          = config["second_arm"]["mass"].value_or(1.f);
  initial_theta_2 = config["second_arm"]["initial_theta"].value_or(0.f);
  final_theta_2   = config["second_arm"]["final_theta"].value_or(0.f);
  initial_color_2 = load_color(config["second_arm"]["initial_color"]);
  final_color_2   = load_color(config["second_arm"]["final_color"]);
}

/* ------------------------------------------------------------------------ */