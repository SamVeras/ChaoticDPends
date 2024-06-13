#pragma once
#include <raylib.h>
#include <toml++/toml.hpp>

/* ------------------------------------------------------------------------ */
/*                              Funções helpers                             */
/* ------------------------------------------------------------------------ */

/* ---------------------- TOML array -> Raylib Color ---------------------- */

Color load_color(const toml::v3::node_view<toml::v3::node>& node);

/* ------------------------- Funções de conversão ------------------------- */

float degrees_to_radians(float angle);
float radians_to_degrees(float radians);

/* ------------------------ Funções de interpolação ----------------------- */

float angle_interpolation(float from, float to, float p);
Color color_interpolation(const Color& from, const Color& to, float p);

/* ------------------------------------------------------------------------ */

float angle_difference(float from, float to);

/* ------------------------------------------------------------------------ */

std::string format_float(float n, float dec);

/* ------------------------------------------------------------------------ */