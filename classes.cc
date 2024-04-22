#include "classes.hh"
#include <SDL2/SDL.h>
#include <iostream>
#include "draw_utils.hh"
#include "globals.hh"

namespace SM {
Square::Square(SDL_Point pos, int side, SDL_Color color)
    : position(pos), side(side), color(color) {}
void Square::update() {
  return;
}
void Square::Square::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::BLACK);
  SDL_Rect r{position.x, position.y, side, side};
  SDL_RenderDrawRect(ren, &r);
}

Triangle::Triangle(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Color color)
    : p1(a), p2(b), p3(c), color(color) {}
void Triangle::update() {}
void Triangle::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::RED);
  SDL_Point ps[4]{p1, p2, p3, p1};
  SDL_RenderDrawLines(ren, ps, 4);
}

Circle::Circle(SDL_Point pos, float r, SDL_Color color)
    : position(pos), radius(r), color(color){};
void Circle::update() {};
void Circle::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, color);
  SM::draw_circle(ren, position.x, position.y, radius);
};
SDL_Point Circle::get_pos() const {
  return position;
};
void Circle::set_pos(SDL_Point new_pos) {
  position = new_pos;
};

SPendulum::SPendulum(SDL_Point o, int l, float a, float br, SDL_Color bc)
    : origin(o),
      arm_length(l),
      angle(a),
      angular_acc(0),
      angular_vel(0),
      bob({0, 0}, br, bc) {}
void SPendulum::update() {
  angular_acc = (-1 * SM::GRAVITY / arm_length) * sin(angle);
  angular_vel += angular_acc;
  angular_vel *= SM::DAMPING;
  angle += angular_vel;

  float x = origin.x + -sin(angle) * arm_length;
  float y = origin.y + cos(angle) * arm_length;
  bob.set_pos({static_cast<int>(x), static_cast<int>(y)});
}
void SPendulum::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::WHITE);
  SDL_Point points[2]{origin, bob.get_pos()};
  SDL_RenderDrawLines(ren, points, 2);
  bob.draw(ren);
}

}  // namespace SM
