#include "json_setup.hh"
#include <iostream>
#include "fun.hh"
#include "fun_sdl.hh"

PendulumSetup::PendulumSetup(nlohmann::json setup) : pvector() {
  using json = nlohmann::json;
  // Casting dos valores? Acho que deve ser necessário...

  json P      = setup["pendulums"];
  json trails = setup["trails"];
  json f_arm  = P["first arm"];
  json s_arm  = P["second arm"];

  SDL_Point    origin    = {P["origin"][0], P["origin"][1]};
  unsigned int num       = setup["pendulums"]["pendulum count"];
  float        mass_1    = f_arm["mass"];
  float        mass_2    = s_arm["mass"];
  float        len_1     = f_arm["length"];
  float        len_2     = s_arm["length"];
  float        f_angle1  = f_arm["angle range"][0];
  float        f_angle2  = f_arm["angle range"][1];
  float        s_angle1  = s_arm["angle range"][0];
  float        s_angle2  = s_arm["angle range"][1];
  unsigned int trail_len = trails["length"];

  SDL_Color C1, C2, TC1, TC2;
  Uint8     r, g, b;

  r  = f_arm["color range"][0][0];
  g  = f_arm["color range"][0][1];
  b  = f_arm["color range"][0][2];
  C1 = {r, g, b, 255};

  r  = f_arm["color range"][1][0];
  g  = f_arm["color range"][1][1];
  b  = f_arm["color range"][1][2];
  C2 = {r, g, b, 255};

  r   = trails["color range"][0][0];
  g   = trails["color range"][0][1];
  b   = trails["color range"][0][2];
  TC1 = {r, g, b, 255};

  r   = trails["color range"][1][0];
  g   = trails["color range"][1][1];
  b   = trails["color range"][1][2];
  TC2 = {r, g, b, 255};

  for (float i = 0; i < num; i++) {
    float     prop = i / num;  // Proporção
    float     t1   = SM::degrees_to_radians(SM::angle_interpolate(f_angle1, f_angle2, prop));
    float     t2   = SM::degrees_to_radians(SM::angle_interpolate(s_angle1, s_angle2, prop));
    SDL_Color fc   = SM::color_interpolate(C1, C2, prop);
    SDL_Color tc   = SM::color_interpolate(TC1, TC2, prop);

    auto pen = std::make_unique<SM::Pendulum>(origin.x, origin.y, len_1, len_2, t1, t2, mass_1,
                                              mass_2, fc, trail_len, tc);
    pvector.push_back(std::move(pen));
  }
}

void PendulumSetup::update() {
  for (const auto& ptr : pvector)
    ptr->update();
}
void PendulumSetup::draw(SDL_Renderer* ren) const {
  for (const auto& ptr : pvector)
    ptr->draw(ren);
}
