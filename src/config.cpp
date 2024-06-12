#include <iostream>
#include <toml++/toml.hpp>
#include "classes.hpp"

Color load_color(const toml::v3::node_view<toml::v3::node>& node) {
  return {(unsigned char)node[0].value_or(255), (unsigned char)node[1].value_or(0),
          (unsigned char)node[2].value_or(255), (unsigned char)node[3].value_or(255)};
}

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
