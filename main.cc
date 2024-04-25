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

  int o = SM::SCR_W / 2;

  for (float i = 0; i < 1000; i++) {
    uint8_t r, g, b;

    r = (i / 1000) * 255;
    b = 255 - (i / 1000) * 255;
    g = 0;

    float th_1 = SM::degrees_to_radians(110 + i / 100);
    float th_2 = SM::degrees_to_radians(-100 - i / 100);

    // std::cout << "Angle 1: " << th_1 << ".\tAngle 2:" << th_2 << "\n";

    SDL_Color C{r, g, b, 255};

    auto Q = make_unique<SM::Pendulum>(o, 110, 100, 100, th_1, th_2, 1, 1, C);
    game.add_drawable(move(Q));
  }

  game.run();
};