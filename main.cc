#include <cstdlib>
#include <iostream>
#include "fun.hh"
#include "fun_sdl.hh"
#include "game.hh"
#include "globals.hh"
#include "pendulum.hh"

void SM::Game::run() {
  unsigned int before = SDL_GetTicks();
  while (!input()) {
    unsigned int now  = SDL_GetTicks();
    unsigned int diff = now - before;
    before            = now;

    float calculated_delta_t = (float)diff / 1000;
    calculated_delta_t *= 100;
    paused ? SM::set_renderer_color(ren, SM::GREY) : SM::set_renderer_color(ren, SM::BLACK);
    SDL_RenderClear(ren);

    for (const auto& d : drawables) {
      if (!paused)
        d->update(calculated_delta_t);
      d->draw(ren);
    }

    SDL_RenderPresent(ren);
    // SDL_Delay(SM::DELAY_MS);
  }
}

int main(int argc, char** argv) {
  using std::make_unique, std::move, std::atof, std::atoi, SM::PendulumSystem;

  if (argc < 21) {
    std::cout
        << "Received:" << argc
        << " args.\nUsage:\nNum of pendulums, first angle start, first angle end, second angle "
           "start, second angle end, first arm length, second arm length, (first color "
           "start) R, G, B, (first color end) R, G, B, trail length, (trail color start) R, "
           "G, B, (trail color end) R, G, B\n";
    return 1;
  }

  SM::Game game;

  SDL_Point    origin_point    = {SM::SCR_W / 2, SM::SCR_H / 2};
  unsigned int pendulum_amount = strtoul(argv[1], nullptr, 10);
  float        first_angle1    = strtof(argv[2], nullptr);
  float        first_angle2    = strtof(argv[3], nullptr);
  float        secnd_angle1    = strtof(argv[4], nullptr);
  float        secnd_angle2    = strtof(argv[5], nullptr);
  unsigned int arm_length1     = strtol(argv[6], nullptr, 10);
  unsigned int arm_length2     = strtol(argv[7], nullptr, 10);
  SDL_Color    color1 = {(Uint8)strtol(argv[8], nullptr, 10), (Uint8)strtol(argv[9], nullptr, 10),
                         (Uint8)strtol(argv[10], nullptr, 10), 255};

  SDL_Color    color2 = {(Uint8)strtol(argv[11], nullptr, 10), (Uint8)strtol(argv[12], nullptr, 10),
                         (Uint8)strtol(argv[13], nullptr, 10), 255};
  unsigned int trail_length = strtoul(argv[14], nullptr, 10);
  SDL_Color    trail_color1 = {(Uint8)strtol(argv[15], nullptr, 10),
                               (Uint8)strtol(argv[16], nullptr, 10),
                               (Uint8)strtol(argv[17], nullptr, 10), 255};
  SDL_Color    trail_color2 = {(Uint8)strtol(argv[18], nullptr, 10),
                               (Uint8)strtol(argv[19], nullptr, 10),
                               (Uint8)strtol(argv[20], nullptr, 10), 255};
  // unsigned int pendulum_amount = 500;
  // float        first_angle1    = 90;
  // float        first_angle2    = 90.001;
  // float        secnd_angle1    = 240;
  // float        secnd_angle2    = 240.001;
  // unsigned int arm_length1     = 125;
  // unsigned int arm_length2     = 185;
  // SDL_Color    color1          = {255, 255, 0, 255};
  // SDL_Color    color2          = {0, 255, 255, 255};
  // unsigned int trail_length    = 45;
  // SDL_Color    trail_color1    = {255, 255, 255, 255};
  // SDL_Color    trail_color2    = {0, 0, 255, 255};

  auto PS = make_unique<PendulumSystem>(origin_point, pendulum_amount, first_angle1, first_angle2,
                                        secnd_angle1, secnd_angle2, 1, 1, arm_length1, arm_length2,
                                        color1, color2, trail_length, trail_color1, trail_color2);
  game.add_drawable(move(PS));

  game.run();
};