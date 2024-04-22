#pragma once
#include <SDL2/SDL.h>

namespace SM {
static const SDL_Color WHITE = {255, 255, 255, 255};
static const SDL_Color GREY = {128, 128, 128, 255};
static const SDL_Color BLACK = {0, 0, 0, 255};
static const SDL_Color RED = {255, 0, 0, 255};
static const SDL_Color GREEN = {0, 255, 0, 255};
static const SDL_Color BLUE = {0, 0, 255, 255};
static const SDL_Color YELLOW = {255, 255, 0, 255};
static const SDL_Color MAGENTA = {255, 0, 255, 255};
static const SDL_Color CYAN = {0, 255, 255, 255};

int set_color(SDL_Renderer* ren, const SDL_Color& color);
void draw_circle(SDL_Renderer* ren, int cx, int cy, int r);

}  // namespace SM
