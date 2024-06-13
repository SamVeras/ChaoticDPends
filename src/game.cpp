#include "game.hpp"
#include <array>
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

Game::Game() : settings("config.toml") {
  create_pendulums(*this, settings);

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(settings.win_width, settings.win_height, settings.title.c_str());

  settings.init_font();  // Não é possível inicializar a fonte antes da janela do jogo

  SetTargetFPS(settings.framerate);
  SetExitKey(KEY_NULL);
}

/* ------------------------------- Destrutor ------------------------------ */

Game::~Game() {
  CloseWindow();
}

/* -------------------------------- Métodos ------------------------------- */

// Mostrar o FPS
void Game::display_fps() {
  std::string str = "FPS: " + std::to_string(GetFPS());
  Color       c   = invert_color(settings.background_color);
  DrawTextEx(settings.font, str.c_str(), {0, 0}, settings.font_size, 1, c);
}

/* ------------------------------------------------------------------------ */

// Mostrar as configurações
void Game::display_debug() {
  using str = std::string;
  using std::to_string;

  const str CNT_t = "Contagem:";
  const str RES_t = "Resolucao:";
  const str DT_t  = "Delta-tempo:";
  const str LEN_t = "Tamanhos:";
  const str MSS_t = "Massas:";
  const str GRV_t = "Gravidade:";
  const str DMP_t = "Damping:";
  // const str ANG1_t = "Dif. inicial 1:";
  // const str ANG2_t = "Dif. inicial 2:";

  // float tdif1 = angle_difference(settings.initial_theta_1, settings.final_theta_1);
  // float tdif2 = angle_difference(settings.initial_theta_1, settings.final_theta_1);

  const str CNT = to_string(settings.count);
  const str RES = to_string(GetScreenWidth()) + "x" + to_string(GetScreenHeight());
  const str DT  = format_float(GetFrameTime() * 1000, 2) + "ms";
  const str LEN = format_float(settings.length_1, 2) + ", " + format_float(settings.length_2, 2);
  const str MSS = format_float(settings.mass_1, 2) + ", " + format_float(settings.mass_2, 2);
  const str GRV = format_float(Global::gravity, 4) + "m/s^2";
  const str DMP = format_float(settings.damping * 100, 5) + "%";
  // const str ANG1 = format_float(tdif1 * 100, 10) + "%";
  // const str ANG2 = format_float(tdif2 * 100, 10) + "%";

  // std::array<str, 9> title = {CNT_t, RES_t, DT_t, LEN_t, MSS_t, GRV_t, DMP_t, ANG1_t, ANG2_t};
  // std::array<str, 9> debug = {CNT, RES, DT, LEN, MSS, GRV, DMP, ANG1, ANG2};
  std::array<str, 7> title = {CNT_t, RES_t, DT_t, LEN_t, MSS_t, GRV_t, DMP_t};
  std::array<str, 7> debug = {CNT, RES, DT, LEN, MSS, GRV, DMP};

  float max_title_width = 0;
  for (const auto& t : title) {
    float width = MeasureTextEx(settings.font, t.c_str(), settings.font_size, 1).x;
    if (width > max_title_width) {
      max_title_width = width;
    }
  }

  float y = GetScreenHeight() - settings.font_size;
  Color c = invert_color(settings.background_color);

  for (size_t i = debug.size() - 1; i < debug.size(); i--) {
    size_t  n   = debug.size() - i - 1;
    str     S   = title[n] + " " + debug[n];
    Vector2 pos = {0, y - i * settings.font_size};
    DrawTextEx(settings.font, title[n].c_str(), pos, settings.font_size, 1, c);
    pos.x += max_title_width + 10;
    DrawTextEx(settings.font, debug[n].c_str(), pos, settings.font_size, 1, c);
  }
}

// Reiniciar o jogo
void Game::reset() {
  drawables.clear();
  create_pendulums(*this, settings);
  settings.init_font();
  SetWindowSize(settings.win_width, settings.win_height);
  SetWindowTitle(settings.title.c_str());
  SetTargetFPS(settings.framerate);
}

/* ------------------------------------------------------------------------ */

// Adicionar um objeto desenhável
void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}

/* ------------------------------------------------------------------------ */

// Interpretar entrada do usuário
void Game::input() {
  if (IsKeyPressed(KEY_ESCAPE) | IsKeyPressed(KEY_Q))
    CloseWindow();

  // Talvez eu remova isso, caso seja
  // necessário manter a resolução original guardada
  if (IsWindowResized()) {
    settings.win_width  = GetScreenWidth();
    settings.win_height = GetScreenHeight();
  }

  if (IsFileDropped()) {
    FilePathList d = LoadDroppedFiles();

    if (IsFileExtension(d.paths[0], ".toml")) {
      settings = Config(d.paths[0]);
      reset();
    }

    UnloadDroppedFiles(d);
  }

  if (IsKeyPressed(KEY_P))
    settings.paused = !settings.paused;

  if (IsKeyPressed(KEY_F1) | IsKeyPressed(KEY_D))
    settings.debug_mode = !settings.debug_mode;

  if (IsKeyPressed(KEY_F2) | IsKeyPressed(KEY_F))
    settings.show_fps = !settings.show_fps;

  if (IsKeyPressed(KEY_R))
    reset();
}

/* ------------------------------------------------------------------------ */

// Executar o jogo
void Game::run() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(settings.background_color);

    if (settings.show_fps)
      display_fps();

    if (settings.debug_mode)
      display_debug();

    this->input();

    for (auto& drawable : drawables) {
      if (!settings.paused)
        drawable->update(GetFrameTime());
      drawable->draw();
    }

    EndDrawing();
  }
}

/* ------------------------------------------------------------------------ */