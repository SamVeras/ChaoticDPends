#include "functions.hpp"
#include <iomanip>
#include <sstream>

/* ------------------------------------------------------------------------ */
/*                                  Funções                                 */
/* ------------------------------------------------------------------------ */

// Carrega uma cor de um node
Color load_color(const toml::v3::node_view<toml::v3::node>& node) {
  return {(unsigned char)node[0].value_or(255), (unsigned char)node[1].value_or(0),
          (unsigned char)node[2].value_or(255), (unsigned char)node[3].value_or(255)};
}

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
  unsigned char r = (unsigned char)(from.r + (to.r - from.r) * p);
  unsigned char g = (unsigned char)(from.g + (to.g - from.g) * p);
  unsigned char b = (unsigned char)(from.b + (to.b - from.b) * p);
  unsigned char a = (unsigned char)(from.a + (to.a - from.a) * p);
  return {r, g, b, a};
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