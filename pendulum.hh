#pragma once
#include "game.hh"
#include "trail.hh"

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

  Trail trail;

 public:
  Pendulum(int       x,
           int       y,
           int       l1,
           int       l2,
           float     t1,
           float     t2,
           float     m1,
           float     m2,
           SDL_Color c,
           int       tl,
           SDL_Color tc);

  void update() override;
  void draw(SDL_Renderer* ren) const override;
};

// class PendulumSystem : public Drawable {
//  private:
//   std::vector<std::unique_ptr<Pendulum>> pendulums;

//  public:
//   PendulumSystem(SDL_Point    O,
//                  unsigned int N,
//                  float        A1,
//                  float        A2,
//                  float        T1,
//                  float        T2,
//                  float        M1,
//                  float        M2,
//                  int          L1,
//                  int          L2,
//                  SDL_Color    C1,
//                  SDL_Color    C2,
//                  int          TL,
//                  SDL_Color    TC1,
//                  SDL_Color    TC2);
//   void update() override;
//   void draw(SDL_Renderer* ren) const override;
// };

}  // namespace SM
