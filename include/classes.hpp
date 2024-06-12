#pragma once
#include "raylib.h"

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

class Config {
 public:
  std::string title;
  size_t      win_width, win_height, framerate;
  Color       background_color;

  Vector2 origin;
  size_t  count;
  float   damping;

  int   length_1, length_2;
  float mass_1, mass_2;
  float initial_theta_1, initial_theta_2;
  float final_theta_1, final_theta_2;
  Color initial_color_1, initial_color_2;
  Color final_color_1, final_color_2;

  bool        show_fps, debug_mode;
  std::string font_path;
  float       font_size;
  Font        font;

  void init_font();
  Config();
  ~Config() = default;
};

/* ------------------------------------------------------------------------ */