#include "game.hpp"
#include <vector>
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

Game::Game()
    : settings("config.toml"),
      timer(0),
      delta_t(1.f / settings.framerate),
      accumulator(0.f),
      sim_speed(1) {
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
  float       pad = 10;
  DrawTextEx(settings.font, str.c_str(), {pad, pad}, settings.font_size, 1, c);
}

/* ------------------------------------------------------------------------ */

// Mostrar as configurações
void Game::display_debug() {
  using str = std::string;
  using std::to_string;

  std::vector<str> title, debug;

  title.push_back("Contagem");
  title.push_back("Resolução");
  title.push_back("Delta-tempo");
  title.push_back("Acumulador");
  title.push_back("Tamanhos");
  title.push_back("Massas");
  title.push_back("Gravidade");
  title.push_back("Damping");

  debug.push_back(to_string(drawables.size()) + " objetos");
  debug.push_back(to_string(GetScreenWidth()) + ":" + to_string(GetScreenHeight()));
  debug.push_back(format_float(delta_t * 1000, 2) + "ms");
  debug.push_back(format_float(accumulator * 1000, 2) + "ms");
  debug.push_back(format_float(settings.length_1, 2) + ", " + format_float(settings.length_2, 2));
  debug.push_back(format_float(settings.mass_1, 2) + ", " + format_float(settings.mass_2, 2));
  debug.push_back(format_float(Global::gravity, 4) + "m/s/s");
  debug.push_back(format_float(settings.damping * 100, 5) + "%");

  float max_title_width = 0;
  for (const auto& t : title) {
    float width = MeasureTextEx(settings.font, t.c_str(), settings.font_size, 1).x;
    if (width > max_title_width) {
      max_title_width = width;
    }
  }

  float y   = GetScreenHeight() - settings.font_size;
  Color c   = invert_color(settings.background_color);
  float pad = 10;

  y -= pad;

  for (size_t i = debug.size() - 1; i < debug.size(); i--) {
    size_t  n   = debug.size() - i - 1;
    str     S   = title[n] + " " + debug[n];
    Vector2 pos = {pad, y - i * settings.font_size};

    DrawTextEx(settings.font, title[n].c_str(), pos, settings.font_size, 1, c);

    pos.x += max_title_width + 10;
    DrawTextEx(settings.font, debug[n].c_str(), pos, settings.font_size, 1, c);
  }
}

/* ------------------------------------------------------------------------ */

// Mostrar o timer
void Game::display_timer() {
  std::string str;
  if (settings.paused)
    str += "PAUSADO ";
  if (sim_speed != 1)
    str += "x" + format_float(sim_speed, 1) + " ";
  str += "t = " + format_float(timer, 2) + "s";
  Color c   = invert_color(settings.background_color);
  float pad = 10;

  float x = GetScreenWidth() - MeasureTextEx(settings.font, str.c_str(), settings.font_size, 1).x;
  float y = GetScreenHeight() - settings.font_size;

  x -= pad;
  y -= pad;

  DrawTextEx(settings.font, str.c_str(), {x, y}, settings.font_size, 1, c);
}

/* ------------------------------------------------------------------------ */

// Reiniciar o jogo
void Game::reset() {
  drawables.clear();
  create_pendulums(*this, settings);
  settings.init_font();
  SetWindowSize(settings.win_width, settings.win_height);
  SetWindowTitle(settings.title.c_str());
  SetTargetFPS(settings.framerate);
  timer = 0;
}

/* ------------------------------------------------------------------------ */

// Adicionar um objeto desenhável
void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}

/* ------------------------------------------------------------------------ */

// Interpretar entrada do usuário
void Game::input() {
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
  int key = GetKeyPressed();
  while (key) {
    switch (key) {
      case KEY_ESCAPE:
      case KEY_Q:
        CloseWindow();
        break;
      case KEY_ONE:
      case KEY_MINUS:
        if (sim_speed > 0.1f)
          sim_speed -= 0.1f;
        break;
      case KEY_TWO:
        sim_speed = 1.0f;
        break;
      case KEY_THREE:
      case KEY_EQUAL:
        if (sim_speed < 2.0f)
          sim_speed += 0.1f;
        break;
      case KEY_P:
      case KEY_SPACE:
        settings.paused = !settings.paused;
        break;
      case KEY_F1:
      case KEY_F:
        if (IsKeyDown(KEY_LEFT_CONTROL)) {  // CTRL F
          if (IsWindowMaximized())
            RestoreWindow();
          else
            MaximizeWindow();
          break;
        }
        settings.show_fps = !settings.show_fps;
        break;
      case KEY_F2:
      case KEY_D:
        settings.debug_mode = !settings.debug_mode;
        break;
      case KEY_F3:
      case KEY_T:
        settings.show_timer = !settings.show_timer;
        break;
      case KEY_R:
        reset();
        break;
      default:
        break;
    }

    key = GetKeyPressed();
  }
}

/* ------------------------------------------------------------------------ */

// Executar o jogo
void Game::run() {
  while (!WindowShouldClose()) {
    accumulator += GetFrameTime() * sim_speed;

    BeginDrawing();
    ClearBackground(settings.background_color);

    if (settings.show_fps)
      display_fps();

    this->input();

    while (accumulator >= delta_t) {
      if (!settings.paused) {
        for (auto& drawable : drawables)
          drawable->update(delta_t);  // Atualizar usando a taxa de atualização fixa
        timer += delta_t;             // Atualizar o timer
      }
      accumulator -= delta_t;
    }

    if (settings.debug_mode)
      display_debug();

    if (settings.show_timer)
      display_timer();

    for (auto& drawable : drawables) {
      drawable->draw();
    }

    EndDrawing();
  }
}

/* ------------------------------------------------------------------------ */