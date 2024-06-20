#pragma once
#include <memory>
#include <vector>
#include "classes.hpp"
#include "config.hpp"

/* ------------------------------------------------------------------------ */
/*                                Game class                                */
/* ------------------------------------------------------------------------ */

class Game {
 private:
  std::string                            config_path;
  Config                                 settings;
  std::vector<std::unique_ptr<Drawable>> drawables;    // Vetor de objetos desenháveis
  Camera2D                               camera;
  double                                 timer;        // Tempo de simulação
  const float                            delta_t;      // Taxa de atualização fixa
  float                                  accumulator;  // Acumulador de tempo restante
  float                                  sim_speed;    // Velocidade de simulação

  void display_fps();
  void display_debug();
  void display_timer();
  void light_reset();
  void reset();
  void full_reset();

 public:
  void add_drawable(std::unique_ptr<Drawable> ptr);
  void input();
  void run();

  Game();
  ~Game();
};

/* ------------------------------------------------------------------------ */