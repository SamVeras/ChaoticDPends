#include "pendulum.hh"
#include "fun_sdl.hh"
#include "globals.hh"

SM::Pendulum::Pendulum(int       x,
                       int       y,
                       int       l1,
                       int       l2,
                       float     t1,
                       float     t2,
                       float     m1,
                       float     m2,
                       SDL_Color c)
    : origin({x, y}),
      arm_length_1(l1),
      arm_length_2(l2),
      mass_1(m1),
      angle_1(t1),
      angle_1_velocity(0),
      angle_1_acceleration(0),
      mass_2(m2),
      angle_2(t2),
      angle_2_velocity(0),
      angle_2_acceleration(0),
      bob_1({0, 0}),
      bob_2({0, 0}),
      color(c){};

void SM::Pendulum::update() {
  float t1 = angle_1;
  float t2 = angle_2;

  float L1  = arm_length_1;
  float L2  = arm_length_2;
  float m_1 = mass_1;
  float m_2 = mass_2;
  float g   = SM::GRAVITY;

  // Tudo que não é proibido é permitido.
  float t1_v² = angle_1_velocity * angle_1_velocity, t_2_v² = angle_2_velocity * angle_2_velocity;

  float num1_p1, num1_p2;
  float num2_p1, num2_p2, num2_p3;
  float den_1, den_2, den_p;

  num1_p1 = (-g * (2 * m_1 + m_2) * sin(t1)) - (m_2 * g * sin(t1 - 2 * t2));
  num1_p2 = 2 * sin(t1 - t2) * m_2 * (t1_v² * L2 + t1_v² * L1 * cos(t1 - t2));

  num2_p1 = 2 * sin(t1 - t2);
  num2_p2 = t1_v² * L1 * (m_1 + m_2) + g * (m_1 + m_2) * cos(t1);
  num2_p3 = t_2_v² * L2 * m_2 * cos(t1 - t2);

  den_p = (2 * m_1 + m_2 - m_2 * cos(2 * t1 - 2 * t2));
  den_1 = L1 * den_p;
  den_2 = L2 * den_p;

  angle_1_acceleration = (num1_p1 - num1_p2) / den_1;
  angle_2_acceleration = (num2_p1 * (num2_p2 + num2_p3)) / den_2;

  angle_1_velocity += angle_1_acceleration;
  angle_2_velocity += angle_2_acceleration;

  angle_1_velocity *= SM::DAMPING;
  angle_2_velocity *= SM::DAMPING;

  angle_1 += angle_1_velocity;
  angle_2 += angle_2_velocity;

  float x_1 = origin.x + sin(angle_1) * arm_length_1;
  float y_1 = origin.y + cos(angle_1) * arm_length_1;
  float x_2 = x_1 + sin(angle_2) * arm_length_2;
  float y_2 = y_1 + cos(angle_2) * arm_length_2;
  bob_1     = {static_cast<int>(x_1), static_cast<int>(y_1)};
  bob_2     = {static_cast<int>(x_2), static_cast<int>(y_2)};
}

void SM::Pendulum::draw(SDL_Renderer* ren) const {
  SM::set_renderer_color(ren, color);
  SM::draw_line(ren, origin, bob_1);
  SM::draw_line(ren, bob_1, bob_2);
  // SM::draw_circle(ren, bob_2.x, bob_2.y, 5);
}