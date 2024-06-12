#include "functions.hpp"

// Carrega uma cor de um node
Color load_color(const toml::v3::node_view<toml::v3::node>& node) {
  return {(unsigned char)node[0].value_or(255), (unsigned char)node[1].value_or(0),
          (unsigned char)node[2].value_or(255), (unsigned char)node[3].value_or(255)};
}

// Converte de graus para radianos
float degrees_to_radians(float angle) {
  return angle * (M_PI / 180.f);
}
// Converte de radianos para graus
float radians_to_degrees(float radians) {
  return radians * (180.f / M_PI);
}

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