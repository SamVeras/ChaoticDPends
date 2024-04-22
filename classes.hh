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
};

class Bob : public Drawable {
 private:
  SDL_Point position;
  float mass;
  float radius;
  SDL_Color color;

 public:
  Bob(SDL_Point pos, float m, float r, SDL_Color col);
  void update() override;
  void draw(SDL_Renderer* ren) const override;

  void set_pos(SDL_Point new_pos);
  SDL_Point get_pos() const;
  float get_mass() const;
};

class SPendulum : public Drawable {
 private:
  SDL_Point origin;
  int arm_length;
  float angle;
  float angular_vel;
  float angular_acc;
  Bob bob;

 public:
  SPendulum(SDL_Point o, int l, float a, float bm, float br, SDL_Color bc);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

class DPendulum : public Drawable {
 private:
  SDL_Point origin;
  int l1;      // Arm length 1
  int l2;      // Arm length 2
  float a1;    // Angle 1
  float a1_v;  // Angle 1 velocity
  float a1_a;  // Angle 1 acceleration
  float a2;    // Angle 2
  float a2_v;  // Angle 2 velocity
  float a2_a;  // Angle 2 acceleration
  Bob bob1;    // Bob / mass 1
  Bob bob2;    // Bob / mass 2

 public:
  DPendulum(SDL_Point o,
            int l1,
            int l2,
            float a1,
            float a2,
            float bm1,
            float bm2,
            float br1,
            float br2,
            SDL_Color bc1,
            SDL_Color bc2);

  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

}  // namespace SM