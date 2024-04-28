#include <iostream>
#include "fun.hh"
#include "fun_sdl.hh"
#include "game.hh"
#include "globals.hh"
#include "pendulum.hh"

void SM::Game::run() {
  while (!input()) {
    paused ? SM::set_renderer_color(ren, SM::GREY) : SM::set_renderer_color(ren, SM::BLACK);
    SDL_RenderClear(ren);

    for (const auto& d : drawables) {
      if (!paused)
        d->update();
      d->draw(ren);
    }

    SDL_RenderPresent(ren);
    SDL_Delay(SM::DELAY_MS);
  }
}

int main() {
  using std::make_unique, std::move;
  SM::Game game;

  int       x  = SM::SCR_W / 2;
  int       y  = SM::SCR_H / 2;
  float     t1 = 100, t2 = 100.05;
  float     t3 = 200, t4 = 200.05;
  SDL_Color cf = {9, 255, 9, 255};
  SDL_Color cs = {255, 0, 0, 255};

  for (float i = 0; i < SM::NUM_OF_PENDULUMS; i++) {
    float proportion = i / SM::NUM_OF_PENDULUMS;

    float angle_1 = SM::degrees_to_radians(SM::angle_interpolate(t1, t2, proportion));
    float angle_2 = SM::degrees_to_radians(SM::angle_interpolate(t3, t4, proportion));

    SDL_Color color = SM::color_interpolate(cf, cs, proportion);

    auto Q = make_unique<SM::Pendulum>(x, y, 200, 200, angle_1, angle_2, 1, 1, color,
                                       SM::TRAIL_LIFETIME, SDL_Color{255, 255, 255, 255});

    game.add_drawable(move(Q));
  }

  game.run();
};