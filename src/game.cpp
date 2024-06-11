#include "game.hpp"
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