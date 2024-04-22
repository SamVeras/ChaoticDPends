#include "classes.hh"
#include "draw_utils.hh"
#include "game.hh"
#include "globals.hh"

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

  auto simple_pendulum = make_unique<SM::SPendulum>(
      SDL_Point{SM::SCR_TW / 2, 200}, 300, M_PI * 0.6, 20, SM::RED);

  game.add_drawable(move(simple_pendulum));

  game.run();
}