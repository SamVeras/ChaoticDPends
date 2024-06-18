#pragma once
#include <raylib.h>
#include <toml++/toml.hpp>

/* ------------------------------------------------------------------------ */
/*                              Funções helpers                             */
/* ------------------------------------------------------------------------ */

/* -------------------------- Funções aleatórias -------------------------- */
unsigned char rand_char();
double        rand_angle();

/* --------------------------- Funções de cores --------------------------- */

Color load_color(const toml::v3::node_view<toml::v3::node>& node);
Color invert_color(const Color& color);

/* ------------------------- Funções de conversão ------------------------- */

double degrees_to_radians(double angle);
double radians_to_degrees(double radians);

/* ------------------------ Funções de interpolação ----------------------- */

double angle_interpolation(double from, double to, double p);
Color  color_interpolation(const Color& from, const Color& to, double p);

/* --------------------------------- Misc. -------------------------------- */

float  measure_strings_width(const std::vector<std::string>& strings, Font& font, float font_size);
double angle_difference(double from, double to);
std::string format_float(float n, float dec);
void        toggle_maximized();

/* ------------------------------------------------------------------------ */