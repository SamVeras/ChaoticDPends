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
      angle_acc(0),
      angle_vel(0),
      bob(Bob({0, 0}, bm, br, bc)) {}
void SPendulum::update() {
  angle_acc = (-1 * bob.get_mass() * SM::GRAVITY / arm_length) * sin(angle);
  angle_vel += angle_acc;
  angle_vel *= SM::DAMPING;
  angle += angle_vel;

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
                     SDL_Color bc2,
                     SDL_Color tc)
    : origin(o),
      arm_l1(l1),
      arm_l2(l2),
      t1(a1),
      t2(a2),
      bob1({0, 0}, bm1, br1, bc1),
      bob2({0, 0}, bm2, br2, bc2),
      trailer(tc){};
void DPendulum::update() {
  float L1 = arm_l1;
  float L2 = arm_l2;
  float m1 = bob1.get_mass();
  float m2 = bob2.get_mass();
  float g = SM::GRAVITY;

  float t1_vel2 = t1_vel * t1_vel;
  float t2_vel2 = t2_vel * t2_vel;

  float n1p1, n1p2, n2p1, n2p2;  // Número x parte y
  float d1, d2, d;               // Denominador x

  n1p1 = (-g * (2 * m1 + m2) * sin(t1)) - (m2 * g * sin(t1 - 2 * t2));
  n1p2 = 2 * sin(t1 - t2) * m2 * (t2_vel2 * L2 + t1_vel2 * L1 * cos(t1 - t2));

  n2p1 = 2 * sin(t1 - t2);
  n2p2 = t1_vel2 * L1 * (m1 + m2) + g * (m1 + m2) * cos(t1) +
         t2_vel2 * L2 * m2 * cos(t1 - t2);

  d = (2 * m1 + m2 - m2 * cos(2 * t1 - 2 * t2));
  d1 = L1 * d;
  d2 = L2 * d;

  t1_acc = (n1p1 - n1p2) / d1;
  t2_acc = (n2p1 * n2p2) / d2;

  t1_vel += t1_acc;
  t2_vel += t2_acc;

  t1_vel *= SM::DAMPING;
  t2_vel *= SM::DAMPING;

  t1 += t1_vel;
  t2 += t2_vel;

  float x1 = origin.x + sin(t1) * arm_l1;
  float y1 = origin.y + cos(t1) * arm_l1;
  float x2 = x1 + sin(t2) * arm_l2;
  float y2 = y1 + cos(t2) * arm_l2;

  bob1.set_pos({static_cast<int>(x1), static_cast<int>(y1)});
  bob2.set_pos({static_cast<int>(x2), static_cast<int>(y2)});

  trailer.add_point(x2, y2);
  trailer.update();
};
void DPendulum::draw(SDL_Renderer* ren) const {
  trailer.draw(ren);
  SM::set_color(ren, SM::WHITE);
  SDL_Point points[3]{origin, bob1.get_pos(), bob2.get_pos()};
  SDL_RenderDrawLines(ren, points, 3);
  bob1.draw(ren);
  bob2.draw(ren);
};

TrailPoint::TrailPoint(SDL_Point pos)
    : position(pos), lifetime(SM::TRAIL_LIFETIME){};
void TrailPoint::update() {
  lifetime--;
};
void TrailPoint::draw(SDL_Renderer* ren) const {
  SM::set_color(ren, SM::CYAN);
  SDL_Rect r{position.x, position.y, 2, 2};
  SDL_RenderDrawRect(ren, &r);
};
SDL_Point TrailPoint::get_position() const {
  return position;
};
unsigned int TrailPoint::get_lifetime() const {
  return lifetime;
};

Trailer::Trailer(SDL_Color c) : color(c), points(){};
void Trailer::update() {
  // std::cout << "Trailer Update\n";
  for (auto t = points.begin(); t != points.end();) {
    if (t->get_lifetime() == 0)
      t = points.erase(t);
    else {
      t->update();
      t++;
    }
  }
  // std::cout << "Trailer Update Done\n";
};
void Trailer::draw(SDL_Renderer* ren) const {
  // std::cout << "Trailer Draw\n";
  auto previous = points.front();
  bool first = true;
  // std::cout << "Is points.front() the culprit?\n";

  for (const auto& tp : points) {
    if (first) {
      first = false;
      continue;
    }

    float a = 255 * (tp.get_lifetime() / (float)SM::TRAIL_LIFETIME);

    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, a);
    SM::draw_line(ren, previous.get_position(), tp.get_position());

    previous = tp;
  }
  // std::cout << "Trailer Draw Done\n";
};
void Trailer::add_point(float x, float y) {
  points.push_back(TrailPoint(SDL_Point{(int)x, (int)y}));
};

}  // namespace SM
