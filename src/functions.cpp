#include "functions.hpp"
#include <iomanip>
#include <sstream>

/* ------------------------------------------------------------------------ */
/*                                  Funções                                 */
/* ------------------------------------------------------------------------ */

// Gera um u_char aleatório
unsigned char rand_char() {
  return static_cast<unsigned char>(rand() % 256);
}

// Gera um angulo aleatório
double rand_angle() {
  return static_cast<double>(rand() % 72000 - 36000) / 100.0;
}

/* ------------------------------------------------------------------------ */

// Carrega uma cor de um node
Color load_color(const toml::v3::node_view<toml::v3::node>& node) {
  unsigned char r = node[0].value_or(rand_char());
  unsigned char g = node[1].value_or(rand_char());
  unsigned char b = node[2].value_or(rand_char());
  unsigned char a = node[3].value_or(255);
  return {r, g, b, a};
}

/* ------------------------------------------------------------------------ */
// Inverte uma cor
Color invert_color(const Color& color) {
  unsigned char R = 255 - color.r;
  unsigned char G = 255 - color.g;
  unsigned char B = 255 - color.b;
  return {R, G, B, color.a};
}

/* ------------------------------------------------------------------------ */

// Converte de graus para radianos
double degrees_to_radians(double angle) {
  return angle * (M_PI / 180.f);
}
/* ------------------------------------------------------------------------ */

// Converte de radianos para graus
double radians_to_degrees(double radians) {
  return radians * (180.f / M_PI);
}

/* ------------------------------------------------------------------------ */

/* Interpola linearmente entre dois ângulos por um p(eso) entre 0.0 e 1.0 */
double angle_interpolation(double from, double to, double p) {
  return from + (to - from) * p;
}

/* ------------------------------------------------------------------------ */

/* Interpola entre duas cores por um p(eso) entre 0.0 e 1.0 */
Color color_interpolation(const Color& from, const Color& to, double p) {
  unsigned char r = static_cast<unsigned char>(from.r + (to.r - from.r) * p);
  unsigned char g = static_cast<unsigned char>(from.g + (to.g - from.g) * p);
  unsigned char b = static_cast<unsigned char>(from.b + (to.b - from.b) * p);
  unsigned char a = static_cast<unsigned char>(from.a + (to.a - from.a) * p);
  return {r, g, b, a};
}

/* ------------------------------------------------------------------------ */

float get_mouse_angle(Vector2 offset) {
  return atan2(GetMouseX() - offset.x, GetMouseY() - offset.y);
}

// Encontrar o tamanho da maior string no vector
float measure_strings_width(const std::vector<std::string>& strings, Font& font, float font_size) {
  float max_title_width = 0;
  for (const auto& t : strings) {  // Encontrar o tamanho da maior string
    float width = MeasureTextEx(font, t.c_str(), font_size, 1).x;
    if (width > max_title_width)
      max_title_width = width;
  }

  return max_title_width;
}

/* ------------------------------------------------------------------------ */

double angle_difference(double from, double to) {
  return (to - from) / from;
}

/* ------------------------------------------------------------------------ */

// Formata um float para um número de casas decimais
std::string format_float(float n, float dec) {
  std::ostringstream s;
  s << std::fixed << std::setprecision(dec) << n;
  return s.str();
}

/* ------------------------------------------------------------------------ */

// Alterna entre estado maximizado ou estado padrão
void toggle_maximized() {
  if (IsWindowMaximized())
    RestoreWindow();
  else
    MaximizeWindow();
}
