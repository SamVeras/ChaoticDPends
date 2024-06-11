#include "classes.hpp"

/* ------------------------------ PendulumArm ----------------------------- */
PendulumArm::PendulumArm(int l, float m, float t, Color c)
    : length(l), mass(m), theta(t), theta_v(0), theta_a(0), color(c) {}

void PendulumArm::update(float dt) {}

void PendulumArm::draw() const {}

/* ---------------------------- SimplePendulum ---------------------------- */

SimplePendulum::SimplePendulum(Vector2 o, int l, float m, float t, Color c)
    : origin(o), arm(l, m, t, c) {}

void SimplePendulum::update(float dt) {}

void SimplePendulum::draw() const {}

/* ---------------------------- DoublePendulum ---------------------------- */