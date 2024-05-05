#include <deque>
#include "game.hh"

namespace SM {
class Trail : public Drawable {
 private:
  std::deque<SDL_Point> points;
  SDL_Color             color;
  int                   trail_size;

 public:
  Trail(SDL_Color trail_color, int trail_size);
  void add_point(SDL_Point& point);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

class NonTerribleTrail : public Drawable {
 private:
  std::deque<SDL_Point> points;
  SDL_Color             color;
  int                   trail_size;

 public:
  NonTerribleTrail(SDL_Color trail_color, int trail_size);
  void add_point(SDL_Point& point);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};
}  // namespace SM
