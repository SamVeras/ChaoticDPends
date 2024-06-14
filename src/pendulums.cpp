#include <cmath>
#include "classes.hpp"
#include "global.hpp"

/* ------------------------------------------------------------------------ */
/*                             Abstract Pendulum                            */
/* ------------------------------------------------------------------------ */

Pendulum::Pendulum(Vector2 o, float d) : origin(o), damping(d) {}

/* ------------------------------------------------------------------------ */
/*                              SimplePendulum                              */
/* ------------------------------------------------------------------------ */
/* ------------------------------ Construtor ------------------------------ */

SimplePendulum::SimplePendulum(Vector2 o, int l, float m, float t, Color c, float d)
    : Pendulum(o, d), arm{l, m, t, 0.f, 0.f, c} {}

/* ----------------------------- Update method ---------------------------- */

void SimplePendulum::update(float dt) {
  float force = arm.mass * Global::gravity * sinf(arm.theta);

  arm.theta_a = -force / arm.length * dt;
  arm.theta_v += arm.theta_a * dt;
  arm.theta_v *= (1 - damping * dt);

  arm.theta += arm.theta_v;
}

/* ------------------------------ Draw method ----------------------------- */

void SimplePendulum::draw() const {
  float x = origin.x + arm.length * sinf(arm.theta);
  float y = origin.y + arm.length * cosf(arm.theta);
  DrawLineV(origin, {x, y}, arm.color);
  DrawCircleV({x, y}, 5.f, arm.color);
}

/* ------------------------------------------------------------------------ */
/*                              DoublePendulum                              */
/* ------------------------------------------------------------------------ */
/* ------------------------------ Construtor ------------------------------ */

DoublePendulum::DoublePendulum(Vector2 o,
                               int     l1,
                               float   m1,
                               float   t1,
                               Color   c1,
                               int     l2,
                               float   m2,
                               float   t2,
                               Color   c2,
                               float   d)
    : Pendulum(o, d), arm1{l1, m1, t1, 0.f, 0.f, c1}, arm2{l2, m2, t2, 0.f, 0.f, c2} {}

/* ----------------------------- Update method ---------------------------- */

void DoublePendulum::update(float dt) {
  float t1 = arm1.theta, t2 = arm2.theta, l1 = arm1.length, l2 = arm2.length;
  float m1 = arm1.mass, m2 = arm2.mass, g = Global::gravity;
  float v1 = arm1.theta_v, v2 = arm2.theta_v;

  float a, b, c;

  a = -g * (2 * m1 + m2) * sinf(t1) - m2 * g * sinf(t1 - 2 * t2);
  b = 2 * sinf(t1 - t2) * m2 * (v2 * v2 * l2 + v1 * v1 * l1 * cosf(t1 - t2));
  c = l1 * (2 * m1 + m2 - m2 * cosf(2 * t1 - 2 * t2));

  arm1.theta_a = (a - b) / c;

  float x, y, z;

  x = 2 * sinf(t1 - t2);
  y = v1 * v1 * l1 * (m1 + m2) + g * (m1 + m2) * cosf(t1) + v2 * v2 * l2 * m2 * cosf(t1 - t2);
  z = l2 * (2 * m1 + m2 - m2 * cosf(2 * t1 - 2 * t2));

  arm2.theta_a = (y * x) / z;

  arm1.theta_v += arm1.theta_a * dt;
  arm2.theta_v += arm2.theta_a * dt;

  arm1.theta_v *= (1 - damping * dt);
  arm2.theta_v *= (1 - damping * dt);

  arm1.theta += arm1.theta_v * dt;
  arm2.theta += arm2.theta_v * dt;
}

/* ------------------------------ Draw method ----------------------------- */

void DoublePendulum::draw() const {
  float x1 = origin.x + sinf(arm1.theta) * arm1.length;
  float y1 = origin.y + cosf(arm1.theta) * arm1.length;

  float x2 = x1 + sinf(arm2.theta) * arm2.length;
  float y2 = y1 + cosf(arm2.theta) * arm2.length;

  DrawLineV(origin, {x1, y1}, arm1.color);
  DrawLineV({x1, y1}, {x2, y2}, arm2.color);
  // DrawCircleV({x2, y2}, arm2.mass, arm2.color);
}
