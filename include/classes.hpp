#pragma once
#include "raylib.h"

/* ------------------------------- Abstrata ------------------------------- */
class Drawable {
 public:
  void virtual update(float dt) = 0;
  void virtual draw() const     = 0;
};

/* ------------------------------- Concreta ------------------------------- */
struct PendulumArm {
  int   length;
  float mass, theta, theta_v, theta_a;
  Color color;
};

class SimplePendulum : public Drawable {
 private:
  Vector2     origin;
  PendulumArm arm;

 public:
  SimplePendulum(Vector2 o, int l, float m, float t, Color c);
  ~SimplePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};

class DoublePendulum : public Drawable {
 private:
  Vector2     origin;
  PendulumArm arm1, arm2;

 public:
  DoublePendulum(Vector2 o,
                 int     l1,
                 float   m1,
                 float   t1,
                 Color   c1,
                 int     l2,
                 float   m2,
                 float   t2,
                 Color   c2);
  ~DoublePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};