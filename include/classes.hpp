#pragma once
#include <raylib.h>

/* ------------------------------------------------------------------------ */
/*                                Estruturas                                */
/* ------------------------------------------------------------------------ */

struct PendulumArm {
  int   length;
  float mass, theta, theta_v, theta_a;
  Color color;
};

/* ------------------------------------------------------------------------ */
/*                             Classes Abstratas                            */
/* ------------------------------------------------------------------------ */

class Drawable {
 public:
  void virtual update(float dt) = 0;
  void virtual draw() const     = 0;
};

/* ------------------------------------------------------------------------ */
/*                             Classes Concretas                            */
/* ------------------------------------------------------------------------ */

class SimplePendulum : public Drawable {
 private:
  Vector2     origin;
  PendulumArm arm;
  float       damping;

 public:
  SimplePendulum(Vector2 o, int l, float m, float t, Color c, float d);
  ~SimplePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};

/* ------------------------------------------------------------------------ */

class DoublePendulum : public Drawable {
 private:
  Vector2     origin;
  PendulumArm arm1, arm2;
  float       damping;

 public:
  DoublePendulum(Vector2 o,
                 int     l1,
                 float   m1,
                 float   t1,
                 Color   c1,
                 int     l2,
                 float   m2,
                 float   t2,
                 Color   c2,
                 float   d);
  ~DoublePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};

/* ------------------------------------------------------------------------ */