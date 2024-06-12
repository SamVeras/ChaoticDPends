#pragma once
#include <memory>
#include <toml++/toml.hpp>
#include <vector>
#include "classes.hpp"

/* ------------------------------------------------------------------------ */
/*                                Game class                                */
/* ------------------------------------------------------------------------ */
class Game {
 private:
  Config                                 settings;
  std::vector<std::unique_ptr<Drawable>> drawables;

  void display_fps();
  void display_debug();

 public:
  void add_drawable(std::unique_ptr<Drawable> ptr);
  void run();

  Game();
  ~Game();
};

/* ------------------------------------------------------------------------ */