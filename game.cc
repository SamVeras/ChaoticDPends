#include "game.hh"
#include "globals.hh"
#include <iostream>

namespace SM {

Game::Game() : paused(false) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    handle_error(ERROR_SDL_INIT_FAIL, "Failed to init SDL. ");

  win = SDL_CreateWindow(SM::TITLE, SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, SM::SCR_TW, SM::SCR_TH,
                         SDL_WINDOW_OPENGL);

  if (win == nullptr)
    handle_error(ERROR_SDL_INIT_FAIL, "failed to init Window. ");

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  if (ren == nullptr)
    handle_error(ERROR_SDL_INIT_FAIL, "Failed to init Renderer. ");

  SDL_RenderSetLogicalSize(ren, SM::SCR_W, SM::SCR_H);
  SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
}

Game::~Game() {
  if (ren)
    SDL_DestroyRenderer(ren);

  if (win)
    SDL_DestroyWindow(win);

  SDL_Quit();
}

void handle_error(int error_code, const char *message) {
  std::cerr << message << std::endl;
  std::cerr << "SDL Error: " << SDL_GetError() << std::endl;

  if (error_code == ERROR_SDL_INIT_FAIL)
    SDL_Quit();
};

bool Game::input() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return true;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_q:
        return true;
      case SDLK_p:
        toggle_pause();
        break;
      default:
        break;
      }
    default:
      break;
    }
  }
  return false;
}

// bool Game::is_running() { return this->running; }
// bool Game::is_paused() { return this->paused; }
void Game::toggle_pause() { this->paused = !this->paused; }

void Game::add_drawable(std::unique_ptr<Drawable> ptr) {
  drawables.push_back(std::move(ptr));
};

}  // namespace SM
