#include "pendulum.hh"
#include "fun.hh"
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
                       SDL_Color c,
                       int       tl,
                       SDL_Color tc)
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
      color(c),
      trail(tc, tl){};

void SM::Pendulum::update(float delta_t) {
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

  angle_1_velocity += angle_1_acceleration * delta_t;
  angle_2_velocity += angle_2_acceleration * delta_t;

  angle_1_velocity *= SM::DAMPING;
  angle_2_velocity *= SM::DAMPING;

  angle_1 += angle_1_velocity * delta_t;
  angle_2 += angle_2_velocity * delta_t;

  float x_1 = origin.x + sin(angle_1) * arm_length_1;
  float y_1 = origin.y + cos(angle_1) * arm_length_1;
  float x_2 = x_1 + sin(angle_2) * arm_length_2;
  float y_2 = y_1 + cos(angle_2) * arm_length_2;
  bob_1     = {static_cast<int>(x_1), static_cast<int>(y_1)};
  bob_2     = {static_cast<int>(x_2), static_cast<int>(y_2)};

  trail.add_point(bob_2);
  trail.update(delta_t);
}

void SM::Pendulum::draw(SDL_Renderer* ren) const {
  trail.draw(ren);
  SM::set_renderer_color(ren, color);
  SDL_Point points[3] = {origin, bob_1, bob_2};
  SDL_RenderDrawLines(ren, points, 3);
}

SM::PendulumSystem::PendulumSystem(SDL_Point    O,
                                   unsigned int N,
                                   float        A1,
                                   float        A2,
                                   float        T1,
                                   float        T2,
                                   float        M1,
                                   float        M2,
                                   int          L1,
                                   int          L2,
                                   SDL_Color    C1,
                                   SDL_Color    C2,
                                   int          TL,
                                   SDL_Color    TC1,
                                   SDL_Color    TC2) {
  for (float i = 0; i < N; i++) {
    // Declarations
    float     P  = i / N;  // Proportion
    int       X  = O.x;
    int       Y  = O.y;
    float     R1 = degrees_to_radians(angle_interpolate(A1, A2, P));
    float     R2 = degrees_to_radians(angle_interpolate(T1, T2, P));
    SDL_Color C  = color_interpolate(C1, C2, P);
    SDL_Color TC = color_interpolate(TC1, TC2, P);  //  C;  // ?

    auto Q = std::make_unique<SM::Pendulum>(X, Y, L1, L2, R1, R2, M1, M2, C, TL, TC);
    pendulums.push_back(move(Q));
  }
}
void SM::PendulumSystem::update(float delta_t) {
  for (const auto& p : pendulums)
    p->update(delta_t);
}
void SM::PendulumSystem::draw(SDL_Renderer* ren) const {
  for (const auto& p : pendulums)
    p->draw(ren);
}