#include "game.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
#include "functions.hpp"
#include "global.hpp"

/* ---------------- Função inacessível por outros arquivos ---------------- */

// Adicionar pêndulos conforme as configurações
void create_pendulums(Game& game, const Config& settings) {
  double  peso, t1, t2;
  float   m1, m2, l1, l2, d;
  Color   c1, c2;
  Vector2 o;

  // Cria pêndulos, inicializando-os com as configurações e movendo-os para o vetor
  for (size_t i = 0; i < settings.count; i++) {
    peso = static_cast<double>(i) / settings.count;  // Peso entre 0.0 e 1.0

    o  = settings.origin;
    m1 = settings.mass_1, m2 = settings.mass_2;
    l1 = settings.length_1, l2 = settings.length_2;
    d  = settings.damping;
    t1 = angle_interpolation(settings.initial_theta_1, settings.final_theta_1, peso);
    t2 = angle_interpolation(settings.initial_theta_2, settings.final_theta_2, peso);
    c1 = color_interpolation(settings.initial_color_1, settings.final_color_1, peso);
    c2 = color_interpolation(settings.initial_color_2, settings.final_color_2, peso);

    auto P = std::make_unique<DoublePendulum>(o, l1, m1, t1, c1, l2, m2, t2, c2, d);

    game.add_drawable(std::move(P));
  }
}

/* ------------------------------------------------------------------------ */
/*                                Game class                                */
/* ------------------------------------------------------------------------ */

/* ------------------------------ Construtor ------------------------------ */

Game::Game()
    : config_path("config.toml"),
      settings(config_path),
      timer(0),
      delta_t(1.f / settings.framerate),
      accumulator(0.f),
      sim_speed(1.f) {
  create_pendulums(*this, settings);

  camera.target   = settings.origin;
  camera.offset   = {static_cast<float>(settings.win_width / 2),
                     static_cast<float>(settings.win_height / 2)};
  camera.rotation = 0.f;
  camera.zoom     = 1.f;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(settings.win_width, settings.win_height, settings.title.c_str());

  settings.init_font();  // Não é possível inicializar a fonte antes da janela do jogo

  SetTargetFPS(settings.framerate);
  SetExitKey(KEY_NULL);  // Desabilitar a tecla padrão de saída
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
  DrawTextEx(settings.font, str.c_str(), {Global::pad, Global::pad}, settings.font_size, 1, c);
}

/* ------------------------------------------------------------------------ */

// Mostrar as configurações
void Game::display_debug() {
  using std::to_string;
  std::vector<std::string> title, debug;

  title.push_back("Angulo 1:");
  title.push_back("Angulo 2:");
  title.push_back("Contagem:");
  title.push_back("Resolucao:");
  title.push_back("Delta-tempo:");
  title.push_back("Acumulador:");
  title.push_back("Tamanhos:");
  title.push_back("Massas:");
  title.push_back("Damping:");
  title.push_back("Gravidade:");
  title.push_back("Tempo:");

  debug.push_back(format_float(radians_to_degrees(settings.initial_theta_1), 3) + " -> " +
                  format_float(radians_to_degrees(settings.final_theta_1), 3));
  debug.push_back(format_float(radians_to_degrees(settings.initial_theta_2), 3) + " -> " +
                  format_float(radians_to_degrees(settings.final_theta_2), 3));
  debug.push_back(to_string(drawables.size()) + " objetos");
  debug.push_back(to_string(GetScreenWidth()) + ":" + to_string(GetScreenHeight()));
  debug.push_back(format_float(delta_t * 1000, 2) + "ms");
  debug.push_back(format_float(accumulator * 1000, 2) + "ms");
  debug.push_back(format_float(settings.length_1, 2) + ", " + format_float(settings.length_2, 2));
  debug.push_back(format_float(settings.mass_1, 2) + ", " + format_float(settings.mass_2, 2));
  debug.push_back(format_float(settings.damping * 100, 5) + "%");
  debug.push_back(format_float(Global::gravity, 4));
  debug.push_back(format_float(GetTime(), 2) + "s");

  assert(debug.size() == title.size());

  float max_title_width = measure_strings_width(title, settings.font, settings.font_size);

  float y = GetScreenHeight() - settings.font_size;  // Ponto inicial da linha
  Color c = invert_color(settings.background_color);

  y -= Global::pad;

  for (size_t i = debug.size() - 1; i < debug.size(); i--) {
    size_t  n   = debug.size() - i - 1;                       // Ordem reversa
    Vector2 pos = {Global::pad, y - i * settings.font_size};  // Posição da string atual

    DrawTextEx(settings.font, title[n].c_str(), pos, settings.font_size, 1, c);

    pos.x += max_title_width + 10;  // Espacamento entre as strings
    DrawTextEx(settings.font, debug[n].c_str(), pos, settings.font_size, 1, c);
  }

  if (!settings.camera_debug)
    return;

  // Camera debug

  debug.clear(), title.clear();
  title.push_back("Offset:");
  title.push_back("Target:");
  title.push_back("Zoom:");
  title.push_back("Rotacao:");
  debug.push_back(format_float(camera.offset.x, 1) + ", " + format_float(camera.offset.y, 1));
  debug.push_back(format_float(camera.target.x, 1) + ", " + format_float(camera.target.y, 1));
  debug.push_back(format_float(camera.zoom, 1));
  debug.push_back(format_float(camera.rotation, 1));

  max_title_width       = measure_strings_width(title, settings.font, settings.font_size);
  float max_debug_width = measure_strings_width(debug, settings.font, settings.font_size);
  y                     = 0 + Global::pad;
  float x               = GetScreenWidth() - max_title_width - max_debug_width - 2 * Global::pad;

  for (size_t i = debug.size() - 1; i < debug.size(); i--) {
    Vector2 pos = {x, y + i * settings.font_size};  // Posição da string atual

    DrawTextEx(settings.font, title[i].c_str(), pos, settings.font_size, 1, c);

    pos.x += max_title_width + 10;  // Espacamento entre as strings
    DrawTextEx(settings.font, debug[i].c_str(), pos, settings.font_size, 1, c);
  }
}

/* ------------------------------------------------------------------------ */

// Mostrar o timer
void Game::display_timer() {
  std::string str;

  if (settings.paused)
    str += "PAUSADO ";

  if (sim_speed != 1)  // Só mostrar a velocidade se fora diferente do normal
    str += "x" + format_float(sim_speed, 1) + " ";
  str += "t = " + format_float(timer, 2) + "s";

  Color c = invert_color(settings.background_color);

  float x = GetScreenWidth() - MeasureTextEx(settings.font, str.c_str(), settings.font_size, 1).x;
  float y = GetScreenHeight() - settings.font_size;  // Ponto inicial da linha

  x -= Global::pad, y -= Global::pad;

  DrawTextEx(settings.font, str.c_str(), {x, y}, settings.font_size, 1, c);
}

/* ------------------------------------------------------------------------ */

// Reiniciar o jogo
void Game::light_reset() {
  drawables.clear();                  // Limpar o vetor de objetos desenháveis
  create_pendulums(*this, settings);  // Recriar os pêndulos
}

void Game::reset() {
  light_reset();

  SetWindowSize(settings.win_width, settings.win_height);

  // Resetar a camera
  camera.target   = settings.origin;
  camera.offset   = {static_cast<float>(settings.win_width / 2),
                     static_cast<float>(settings.win_height / 2)};
  camera.rotation = 0.f;
  camera.zoom     = 1.f;
  timer           = 0;
}

/* ------------------------------------------------------------------------ */
// Reiniciar completamente o jogo
void Game::full_reset() {
  settings = Config(config_path);  // Recarregar as configurações
  settings.init_font();
  SetWindowTitle(settings.title.c_str());
  SetTargetFPS(settings.framerate);
  sim_speed = 1.f;
  reset();
}

/* ------------------------------------------------------------------------ */

// Adicionar um objeto desenhável
void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}

/* ------------------------------------------------------------------------ */

// Interpretar entrada do usuário
void Game::input() {
  if (IsWindowResized()) {  // Atualizar tamanho da janela
    settings.win_width  = GetScreenWidth();
    settings.win_height = GetScreenHeight();
  }

  // Carregar arquivo de configuração solto na janela
  if (IsFileDropped()) {
    FilePathList d = LoadDroppedFiles();
    if (IsFileExtension(d.paths[0], ".toml")) {
      config_path = d.paths[0];
      full_reset();
    }
    UnloadDroppedFiles(d);
  }

  /* --------------------------------- Mouse -------------------------------- */

  // Se o mouse estiver sendo arrastado, atualizar a posição da camera
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    camera.offset.x += GetMouseDelta().x, camera.offset.y += GetMouseDelta().y;

  // Mudar o zoom com o mouse wheel
  camera.zoom += GetMouseWheelMove() / 10.f;
  camera.zoom = std::clamp(camera.zoom, 0.5f, 2.0f);

  /* -------------------------------- Teclado ------------------------------- */

  if (IsKeyPressed(KEY_ESCAPE) | IsKeyPressed(KEY_Q))
    CloseWindow();

  if (IsKeyPressed(KEY_ONE) | IsKeyPressed(KEY_MINUS))
    if (sim_speed > 0.1f)
      sim_speed -= 0.1f;

  if (IsKeyPressed(KEY_TWO))
    sim_speed = 1.0f;

  if (IsKeyPressed(KEY_THREE) | IsKeyPressed(KEY_EQUAL))
    if (sim_speed < 2.0f)
      sim_speed += 0.1f;

  if (IsKeyPressed(KEY_P) | IsKeyPressed(KEY_SPACE))
    settings.paused = !settings.paused;

  if (IsKeyPressed(KEY_F1) | IsKeyPressed(KEY_F)) {
    if (IsKeyDown(KEY_LEFT_CONTROL))  // CTRL F
      toggle_maximized();
    else
      settings.show_fps = !settings.show_fps;
  }
  if (IsKeyPressed(KEY_F2) | IsKeyPressed(KEY_D))
    settings.debug_mode = !settings.debug_mode;

  if (IsKeyPressed(KEY_F3) | IsKeyPressed(KEY_T))
    settings.show_timer = !settings.show_timer;

  if (IsKeyPressed(KEY_F4) | IsKeyPressed(KEY_C))
    settings.camera_debug = !settings.camera_debug;

  if (IsKeyPressed(KEY_R)) {
    if (IsKeyDown(KEY_LEFT_CONTROL))  // CTRL R
      full_reset();
    reset();
  }
}

/* ------------------------------------------------------------------------ */

// Executar o jogo
void Game::run() {
  while (!WindowShouldClose()) {
    accumulator += GetFrameTime() * sim_speed;
    // O sistema de time-step fixo com acumulador faz com que a lógica de
    // simulação tenha uma taxa independente da taxa de atualização de quadros
    // https://gafferongames.com/post/fix_your_timestep/#free-the-physics

    BeginDrawing();
    ClearBackground(settings.background_color);

    if (settings.show_fps)
      display_fps();

    this->input();  // Interpretar entrada do usuário

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

    BeginMode2D(camera);  // Apenas os objetos desenháveis sao renderizados pela câmera
    for (auto& drawable : drawables)
      drawable->draw();
    EndMode2D();

    EndDrawing();
  }
}

/* ------------------------------------------------------------------------ */
