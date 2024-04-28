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
  using std::make_unique, std::move, SM::PendulumSystem;
  SM::Game game;

  SDL_Point    origin_point    = {SM::SCR_W / 2, SM::SCR_H / 2};
  unsigned int pendulum_amount = 500;
  float        first_angle1    = 90;
  float        first_angle2    = 90.001;
  float        secnd_angle1    = 240;
  float        secnd_angle2    = 240.001;
  unsigned int arm_length1     = 125;
  unsigned int arm_length2     = 185;
  SDL_Color    color1          = {255, 255, 0, 255};
  SDL_Color    color2          = {0, 255, 255, 255};
  unsigned int trail_length    = 45;
  SDL_Color    trail_color1    = {255, 255, 255, 255};
  SDL_Color    trail_color2    = {0, 0, 255, 255};

  auto PS = make_unique<PendulumSystem>(origin_point, pendulum_amount, first_angle1, first_angle2,
                                        secnd_angle1, secnd_angle2, 1, 1, arm_length1, arm_length2,
                                        color1, color2, trail_length, trail_color1, trail_color2);
  game.add_drawable(move(PS));

  game.run();
};