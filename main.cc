#include "draw_utils.hh"
#include "game.hh"
#include "globals.hh"

class Square : public SM::Drawable {
private:
  int x, y;
  int side;

public:
  Square(int x, int y, int side) : x(x), y(y), side(side){};

  void update() override{};

  void draw(SDL_Renderer *ren) const override {
    SM::set_color(ren, SM::WHITE);
    SDL_Rect r{x, y, side, side};
    SDL_RenderDrawRect(ren, &r);
  }
};

void SM::Game::run() {
  while (!input()) {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderClear(ren);

    for (const auto &d : drawables) {
      if (!paused)
        d->update();
      d->draw(ren);
    }

    SDL_RenderPresent(ren);
    SDL_Delay(SM::DELAY_MS);
  }
}

int main() {
  SM::Game game;
  auto s = std::make_unique<Square>(30, 30, 20);
  game.add_drawable(move(s));
  // game.add_drawable(move(std::make_unique<Square>(30, 30, 20)));

  game.run();
}