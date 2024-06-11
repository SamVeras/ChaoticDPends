#pragma once
#include <memory>
#include <vector>
#include "classes.hpp"

class Game {
 private:
  std::vector<std::unique_ptr<Drawable>> drawables;

 public:
  void add_drawable(std::unique_ptr<Drawable> ptr);
  void run();
  Game();
  ~Game();
};
