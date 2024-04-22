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

Bob::Bob(SDL_Point pos, float m, float r, SDL_Color col)
    : position(pos), mass(m), radius(r), color(col){};
void Bob::update() {};
void Bob::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, color);
  SM::draw_circle(ren, position.x, position.y, radius);
};
void Bob::set_pos(SDL_Point new_pos) {
  position = new_pos;
};
SDL_Point Bob::get_pos() const {
  return position;
};
float Bob::get_mass() const {
  return mass;
};

SPendulum::SPendulum(SDL_Point o,
                     int l,
                     float a,
                     float bm,
                     float br,
                     SDL_Color bc)
    : origin(o),
      arm_length(l),
      angle(a),
      angular_acc(0),
      angular_vel(0),
      bob(Bob({0, 0}, bm, br, bc)) {}
void SPendulum::update() {
  angular_acc = (-1 * bob.get_mass() * SM::GRAVITY / arm_length) * sin(angle);
  angular_vel += angular_acc;
  angular_vel *= SM::DAMPING;
  angle += angular_vel;

  float x = origin.x + -sin(angle) * arm_length;
  float y = origin.y + cos(angle) * arm_length;
  bob.set_pos({static_cast<int>(x), static_cast<int>(y)});
}
void SPendulum::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::BLACK);
  SDL_Point points[2]{origin, bob.get_pos()};
  SDL_RenderDrawLines(ren, points, 2);
  bob.draw(ren);
}
DPendulum::DPendulum(SDL_Point o,
                     int l1,
                     int l2,
                     float a1,
                     float a2,
                     float bm1,
                     float bm2,
                     float br1,
                     float br2,
                     SDL_Color bc1,
                     SDL_Color bc2)
    : origin(o),
      l1(l1),
      l2(l2),
      a1(a1),
      a2(a2),
      bob1({0, 0}, bm1, br1, bc1),
      bob2({0, 0}, bm2, br2, bc2){};
void DPendulum::update() {
  float x1 = origin.x + -sin(a1) * l1;
  float y1 = origin.y + cos(a1) * l1;
  float x2 = x1 + -sin(a2) * l2;
  float y2 = y1 + cos(a2) * l2;

  bob1.set_pos({static_cast<int>(x1), static_cast<int>(y1)});
  bob2.set_pos({static_cast<int>(x2), static_cast<int>(y2)});
};
void DPendulum::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::BLACK);
  SDL_Point points[3]{origin, bob1.get_pos(), bob2.get_pos()};
  SDL_RenderDrawLines(ren, points, 3);
  bob1.draw(ren);
  bob2.draw(ren);
};

}  // namespace SM
