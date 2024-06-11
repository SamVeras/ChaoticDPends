#include "game.hpp"
#include <cmath>
#include "classes.hpp"
#include "raylib.h"
#include "setup.hpp"

Game::Game() {
  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);
  InitWindow(Setup::win_width, Setup::win_height, Setup::title);
  SetTargetFPS(Setup::framerate);
}

Game::~Game() {
  CloseWindow();
}

void Game::run() {
  auto dp = std::make_unique<DoublePendulum>(Vector2{200, 200}, 50, 1.f, M_PI / 3, RED, 30, 1.f,
                                             M_PI / 5, GREEN);
  this->add_drawable(std::move(dp));
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Setup::background);
    for (auto& drawable : drawables) {
      drawable->update(GetFrameTime());
      drawable->draw();
    }
    EndDrawing();
  }
}

void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}