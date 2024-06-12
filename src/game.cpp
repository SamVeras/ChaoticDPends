#include "game.hpp"
#include <array>
#include <iomanip>
#include <sstream>
#include "functions.hpp"
#include "global.hpp"

/* ---------------- Função inacessível por outros arquivos ---------------- */
// Adicionar pêndulos conforme as configurações
void create_pendulums(Game& game, const Config& settings) {
  for (size_t i = 0; i < settings.count; i++) {
    float   p, t1, t2, m1, m2, l1, l2, d;
    Color   c1, c2;
    Vector2 o;

    p  = float(i) / settings.count;
    o  = settings.origin;
    m1 = settings.mass_1, m2 = settings.mass_2;
    l1 = settings.length_1, l2 = settings.length_2;
    d  = settings.damping;
    t1 = angle_interpolation(settings.initial_theta_1, settings.final_theta_1, p);
    t2 = angle_interpolation(settings.initial_theta_2, settings.final_theta_2, p);
    c1 = color_interpolation(settings.initial_color_1, settings.final_color_1, p);
    c2 = color_interpolation(settings.initial_color_2, settings.final_color_2, p);

    auto P = std::make_unique<DoublePendulum>(o, l1, m1, t1, c1, l2, m2, t2, c2, d);

    game.add_drawable(std::move(P));
  }
}

/* ------------------------------------------------------------------------ */
/*                                Game class                                */
/* ------------------------------------------------------------------------ */
/* ------------------------------ Construtor ------------------------------ */

Game::Game() {
  create_pendulums(*this, settings);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(settings.win_width, settings.win_height, settings.title.c_str());
  settings.init_font();  // Não é possível inicializar a fonte antes da janela do jogo
  SetTargetFPS(settings.framerate);
}

/* ------------------------------- Destrutor ------------------------------ */

Game::~Game() {
  CloseWindow();
}

/* -------------------------------- Métodos ------------------------------- */

void Game::display_fps() {
  std::string str = "FPS: " + std::to_string(GetFPS());
  DrawTextEx(settings.font, str.c_str(), {0, 0}, settings.font_size, 1, WHITE);
}

/* ------------------------------------------------------------------------ */

std::string format_float(float n, float dec) {
  std::ostringstream s;
  s << std::fixed << std::setprecision(dec) << n;
  return s.str();
}

void Game::display_debug() {
  std::string RES = "RES:\t";
  RES += std::to_string(GetScreenWidth()) + "x" + std::to_string(GetScreenHeight());

  std::string CNT = "CNT:\t";
  CNT += std::to_string(settings.count);

  std::string DMP = "DMP:\t";
  DMP += format_float(settings.damping * 100, 5) + "%";

  std::string LEN = "LEN:\t";
  LEN += format_float(settings.length_1, 2) + ", " + format_float(settings.length_2, 2);

  std::string MSS = "MSS:\t";
  MSS += format_float(settings.mass_1, 2) + ", " + format_float(settings.mass_2, 2);

  float       tdif1 = angle_difference(settings.initial_theta_1, settings.final_theta_1);
  std::string ANG1  = "Δθ1:\t";
  ANG1 += format_float(tdif1 * 100, 10) + "%";

  float       tdif2 = angle_difference(settings.initial_theta_1, settings.final_theta_1);
  std::string ANG2  = "Δθ2:\t";
  ANG2 += format_float(tdif2 * 100, 10) + "%";

  std::string DT = " Δt:\t";
  DT += std::to_string(GetFrameTime()) + "s";

  std::string GRV = "  G:\t";
  GRV += format_float(Global::gravity, 4) + "m/s2";

  std::array<std::string, 9> debug = {DT, ANG2, ANG1, DMP, GRV, MSS, LEN, RES, CNT};

  float y = GetScreenHeight() - settings.font_size;
  for (size_t i = 0; i < debug.size(); i++) {
    std::string str = debug[i];
    DrawTextEx(settings.font, str.c_str(), {0, y - i * settings.font_size}, settings.font_size, 1,
               WHITE);
  }
}

/* ------------------------------------------------------------------------ */

void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}

/* ------------------------------------------------------------------------ */

void Game::run() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(settings.background_color);
    if (settings.show_fps)
      display_fps();
    if (settings.debug_mode)
      display_debug();
    for (auto& drawable : drawables)
      drawable->update(GetFrameTime()), drawable->draw();
    EndDrawing();
  }
}

/* ------------------------------------------------------------------------ */