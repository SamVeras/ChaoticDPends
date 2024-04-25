#include <iostream>
#include "fun.hh"
#include "fun_sdl.hh"
#include "game.hh"
#include "globals.hh"
#include "pendulum.hh"

void SM::Game::run() {
  while (!input()) {
    paused ? SM::set_renderer_color(ren, SM::GREY)
           : SM::set_renderer_color(ren, SM::BLACK);
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

  int o = SM::SCR_W / 2;
  int k = SM::SCR_H / 2;

  for (float i = 0; i < SM::NUM_OF_PENDULUMS; i++) {
    uint8_t r, g, b;

    r = (i / SM::NUM_OF_PENDULUMS) * 255;
    b = 255 - (i / SM::NUM_OF_PENDULUMS) * 255;
    g = 0;

    float th_1 = SM::degrees_to_radians(160 + i / 10000);
    float th_2 = SM::degrees_to_radians(100 - i / 10000);

    SDL_Color C{r, g, b, 255};

    auto Q = make_unique<SM::Pendulum>(o, k, 220, 220, th_1, th_2, 1, 1, C);
    game.add_drawable(move(Q));
  }

  game.run();
};