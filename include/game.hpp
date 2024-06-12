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

 public:
  void add_drawable(std::unique_ptr<Drawable> ptr);
  void run();

  Game();
  ~Game();
};

/* ------------------------------------------------------------------------ */