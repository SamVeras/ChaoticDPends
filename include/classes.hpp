#pragma once
#include <raylib.h>

/* ------------------------------------------------------------------------ */
/*                                Estruturas                                */
/* ------------------------------------------------------------------------ */

struct PendulumArm {
  int    length;
  float  mass;
  double theta, theta_v, theta_a;
  Color  color;
};

/* ------------------------------------------------------------------------ */
/*                             Classes Abstratas                            */
/* ------------------------------------------------------------------------ */

class Drawable {
 public:
  void virtual update(float dt) = 0;
  void virtual draw() const     = 0;

  virtual ~Drawable() = default;
};

class Pendulum : public Drawable {
 protected:
  Vector2 origin;
  float   damping;

 public:
  Pendulum(Vector2 o, float d);
  ~Pendulum() = default;
};

/* ------------------------------------------------------------------------ */
/*                             Classes Concretas                            */
/* ------------------------------------------------------------------------ */

class SimplePendulum : public Pendulum {
 private:
  PendulumArm arm;

 public:
  SimplePendulum(Vector2 o, int l, float m, double t, Color c, float d);
  ~SimplePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};

/* ------------------------------------------------------------------------ */

class DoublePendulum : public Pendulum {
 private:
  PendulumArm arm1, arm2;

 public:
  DoublePendulum(Vector2 o,
                 int     l1,
                 float   m1,
                 double  t1,
                 Color   c1,
                 int     l2,
                 float   m2,
                 double  t2,
                 Color   c2,
                 float   d);
  ~DoublePendulum() = default;

  void update(float dt) override;
  void draw() const override;
};

/* ------------------------------------------------------------------------ */