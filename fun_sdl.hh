#pragma once
#include <SDL2/SDL.h>

namespace SM {
static const SDL_Color WHITE   = {255, 255, 255, 255};
static const SDL_Color GREY    = {128, 128, 128, 255};
static const SDL_Color BLACK   = {0, 0, 0, 255};
static const SDL_Color RED     = {255, 0, 0, 255};
static const SDL_Color GREEN   = {0, 255, 0, 255};
static const SDL_Color BLUE    = {0, 0, 255, 255};
static const SDL_Color YELLOW  = {255, 255, 0, 255};
static const SDL_Color MAGENTA = {255, 0, 255, 255};
static const SDL_Color CYAN    = {0, 255, 255, 255};

// Muda a cor usada para operações de desenho
int set_renderer_color(SDL_Renderer* renderer, const SDL_Color& color);
// Desenha um círculo com centro em (x, y) e raio
void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius);
// Desenha uma linha entre dois pontos
int draw_line(SDL_Renderer* renderer, SDL_Point point_1, SDL_Point point_2);

}  // namespace SM
