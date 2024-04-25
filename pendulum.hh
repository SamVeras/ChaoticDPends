#pragma once
#include "game.hh"

namespace SM {

class Pendulum : public Drawable {
 private:
  SDL_Point origin;

  int   arm_length_1;
  float mass_1;
  float angle_1;
  float angle_1_velocity;
  float angle_1_acceleration;

  int   arm_length_2;
  float mass_2;
  float angle_2;
  float angle_2_velocity;
  float angle_2_acceleration;

  SDL_Point bob_1;
  SDL_Point bob_2;

  SDL_Color color;

 public:
  Pendulum(int x, int y, int l1, int l2, float t1, float t2, float m1, float m2, SDL_Color c);

  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

}  // namespace SM
