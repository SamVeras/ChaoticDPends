#pragma once
#include <raylib.h>
#include <toml++/toml.hpp>

/* ------------------------------------------------------------------------ */
/*                              Funções helpers                             */
/* ------------------------------------------------------------------------ */

/* ---------------------------- Color functions --------------------------- */

Color load_color(const toml::v3::node_view<toml::v3::node>& node);
Color invert_color(const Color& color);

/* ------------------------- Funções de conversão ------------------------- */

double degrees_to_radians(double angle);
double radians_to_degrees(double radians);

/* ------------------------ Funções de interpolação ----------------------- */

double angle_interpolation(double from, double to, double p);
Color  color_interpolation(const Color& from, const Color& to, double p);

/* ------------------------------------------------------------------------ */

double angle_difference(double from, double to);

/* ------------------------------------------------------------------------ */

std::string format_float(float n, float dec);

/* ------------------------------------------------------------------------ */

void toggle_maximized();