#pragma once
#include "raylib.h"

/* ------------------------------- Abstrata ------------------------------- */
class Drawable {
 public:
  void virtual update(float dt) = 0;
  void virtual draw() const     = 0;
};

/* ------------------------------- Concreta ------------------------------- */
class PendulumArm : public Drawable {
 private:
  int   length;
  float mass, theta, theta_v, theta_a;
  Color color;

 public:
  PendulumArm(int l, float m, float t, Color c);
  ~PendulumArm() = default;

  void update(float dt) override;
  void draw() const override;
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

class DoublePendulum : public Drawable {};