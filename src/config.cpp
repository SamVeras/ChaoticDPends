#include <iostream>
#include <toml++/toml.hpp>
#include "classes.hpp"
#include "functions.hpp"

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

  initial_theta_1 = degrees_to_radians(initial_theta_1);
  final_theta_1   = degrees_to_radians(final_theta_1);
  initial_theta_2 = degrees_to_radians(initial_theta_2);
  final_theta_2   = degrees_to_radians(final_theta_2);
}

/* ------------------------------------------------------------------------ */