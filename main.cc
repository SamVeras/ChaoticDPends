#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include "fun.hh"
#include "fun_sdl.hh"
#include "game.hh"
#include "globals.hh"
#include "json_setup.hh"
#include "nlohmann/json.hpp"
#include "pendulum.hh"

void SM::Game::run() {
  unsigned int before = SDL_GetTicks();
  while (!input()) {
    unsigned int now  = SDL_GetTicks();
    unsigned int diff = now - before;
    before            = now;

    float calculated_delta_t = (float)diff / 1000;
    calculated_delta_t *= 100;
    paused ? SM::set_renderer_color(ren, SM::GREY) : SM::set_renderer_color(ren, SM::BLACK);
    SDL_RenderClear(ren);

    for (const auto& d : drawables) {
      if (!paused)
        d->update(calculated_delta_t);
      d->draw(ren);
    }

    SDL_RenderPresent(ren);
    // SDL_Delay(SM::DELAY_MS);
  }
}

int main() {
  SM::Game game;

  std::ifstream  file("setup.json");
  nlohmann::json setup = nlohmann::json::parse(file);

  std::unique_ptr<PendulumSetup> PS = std::make_unique<PendulumSetup>(setup);

  game.add_drawable(std::move(PS));

  game.run();
};