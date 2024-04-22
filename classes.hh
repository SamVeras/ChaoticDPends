#pragma once
#include "game.hh"

namespace SM {
class Square : public Drawable {
 private:
  SDL_Point position;
  SDL_Color color;
  int side;

 public:
  Square(SDL_Point pos, int side, SDL_Color color);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

class Triangle : public Drawable {
 private:
  SDL_Point p1;
  SDL_Point p2;
  SDL_Point p3;
  SDL_Color color;

 public:
  Triangle(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Color color);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

class Circle : public Drawable {
 private:
  SDL_Point position;
  float radius;
  SDL_Color color;

 public:
  Circle(SDL_Point pos, float r, SDL_Color color);
  void update() override;
  void draw(SDL_Renderer* ren) const override;

  SDL_Point get_pos() const;
  void set_pos(SDL_Point new_pos);
};

class SPendulum : public Drawable {
 private:
  SDL_Point origin;
  int arm_length;
  float angle;
  float angular_vel;
  float angular_acc;
  SM::Circle bob;

 public:
  SPendulum(SDL_Point o, int l, float a, float br, SDL_Color bc);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

}  // namespace SM