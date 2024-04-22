#include "classes.hh"
#include "draw_utils.hh"
#include "game.hh"
#include "globals.hh"
#include "usefunctions.hh"

void SM::Game::run() {
  while (!input()) {
    paused ? SM::set_color(ren, SM::GREY) : SM::set_color(ren, SM::WHITE);
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

  // auto sp1 = make_unique<SM::SPendulum>(SDL_Point{50, 50}, 40, M_PI * 0.6, 1,
  // 7,
  //                                       SM::RED);

  // game.add_drawable(move(sp1));
  SDL_Point o{40, 40};
  float t1 = SM::degree_to_radians(30);
  float t2 = SM::degree_to_radians(-60);
  auto dp = make_unique<SM::DPendulum>(o, 30, 30, t1, t2, 1, 1, 6, 6, SM::RED,
                                       SM::BLUE);
  game.add_drawable(move(dp));

  game.run();
}