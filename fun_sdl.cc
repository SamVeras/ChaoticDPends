#include "fun_sdl.hh"

int SM::set_renderer_color(SDL_Renderer* renderer, const SDL_Color& color) {
  return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SM::draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius) {
  bool even = (radius % 2 == 0);
  int  rad  = radius % 2 == 0 ? radius - 1 : radius;
  int  t1   = rad / 16;
  int  t2   = 0;
  int  x    = rad;
  int  y    = 0;
  int  cx   = center_x;
  int  cy   = center_y;

  while (x >= y) {
    SDL_RenderDrawPoint(renderer, cx + x, cy - y - even);         // 1st quadrant: (CCW)
    SDL_RenderDrawPoint(renderer, cx + y, cy - x - even);
    SDL_RenderDrawPoint(renderer, cx - y - even, cy - x - even);  // 2nd quadrant:
    SDL_RenderDrawPoint(renderer, cx - x - even, cy - y - even);
    SDL_RenderDrawPoint(renderer, cx - x - even, cy + y);         // 3rd quadrant:
    SDL_RenderDrawPoint(renderer, cx - y - even, cy + x);
    SDL_RenderDrawPoint(renderer, cx + y, cy + x);                // 4th quadrant:
    SDL_RenderDrawPoint(renderer, cx + x, cy + y);

    y++;
    t1 = t1 + y;
    t2 = t1 - x;
    if (t2 >= 0)
      t1 = t2, x--;
  }
}

int SM::draw_line(SDL_Renderer* renderer, SDL_Point point_1, SDL_Point point_2) {
  return SDL_RenderDrawLine(renderer, point_1.x, point_1.y, point_2.x, point_2.y);
}

SDL_Color SM::color_interpolate(SDL_Color color1, SDL_Color color2, float proportion) {
  SDL_Color new_color = color1;

  if (color1.r != color2.r)
    new_color.r = (Uint8)(color1.r + (color2.r - color1.r) * proportion);
  if (color1.g != color2.g)
    new_color.g = (Uint8)(color1.g + (color2.g - color1.g) * proportion);
  if (color1.b != color2.b)
    new_color.b = (Uint8)(color1.b + (color2.b - color1.b) * proportion);
  if (color1.a != color2.a)
    new_color.a = (Uint8)(color1.a + (color2.a - color1.a) * proportion);

  return new_color;
}