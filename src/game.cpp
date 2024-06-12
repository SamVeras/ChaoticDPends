#include "game.hpp"
#include <cmath>
#include "classes.hpp"
#include "raylib.h"

Game::Game() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(settings.win_width, settings.win_height, settings.title.c_str());
  SetTargetFPS(settings.framerate);
}

Game::~Game() {
  CloseWindow();
}

void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
}

void Game::run() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(settings.background_color);
    for (auto& drawable : drawables)
      drawable->update(GetFrameTime()), drawable->draw();
    EndDrawing();
  }
}
