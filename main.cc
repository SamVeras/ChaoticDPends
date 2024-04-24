#include <iostream>
#include "classes.hh"
#include "draw_utils.hh"
#include "game.hh"
#include "globals.hh"
#include "usefunctions.hh"

void SM::Game::run() {
  while (!input()) {
    paused ? SM::set_color(ren, SM::GREY) : SM::set_color(ren, SM::BLACK);
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
  using std::make_unique, std::unique_ptr;
  SM::Game game;

  SDL_Point o{SM::SCR_W / 2, 140};

  for (int i = 0; i < 5; i++) {
    float t1 = SM::degree_to_radians(-100 + i);
    float t2 = SM::degree_to_radians(140 + i);
    auto dp = make_unique<SM::DPendulum>(o, 120, 50, t1, t2, 1, 1, 6, 6,
                                         SM::BLUE, SM::RED, SM::RED);
    game.add_drawable(move(dp));
  }

  std::cout << "Done adding!\n";

  game.run();
}