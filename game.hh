#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#define ERROR_SDL_INIT_FAIL -1

namespace SM {

class Drawable {
public:
  void virtual update() = 0;
  void virtual draw(SDL_Renderer *ren) const = 0;
};

class Game {
protected:
  SDL_Window *win;
  SDL_Renderer *ren;
  bool paused;
  std::vector<std::unique_ptr<Drawable>> drawables;

  bool input();  // Returns true to quit
  void toggle_pause();

public:
  // bool is_running();
  // bool is_paused();
  void add_drawable(std::unique_ptr<Drawable> ptr);
  void run();

  Game();
  ~Game();
};

void handle_error(int error_code, const char *message);

}  // namespace SM