#include "draw_utils.hh"
namespace SM {
int set_color(SDL_Renderer* ren, const SDL_Color& color) {
  return SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
}

void draw_circle_points(SDL_Renderer* ren,
                        int cx,
                        int cy,
                        int x,
                        int y,
                        bool even) {
  SDL_RenderDrawPoint(ren, cx + x, cy - y - even);  // 1st quadrant: (CCW)
  SDL_RenderDrawPoint(ren, cx + y, cy - x - even);
  SDL_RenderDrawPoint(ren, cx - y - even, cy - x - even);  // 2nd quadrant:
  SDL_RenderDrawPoint(ren, cx - x - even, cy - y - even);
  SDL_RenderDrawPoint(ren, cx - x - even, cy + y);         // 3rd quadrant:
  SDL_RenderDrawPoint(ren, cx - y - even, cy + x);
  SDL_RenderDrawPoint(ren, cx + y, cy + x);                // 4th quadrant:
  SDL_RenderDrawPoint(ren, cx + x, cy + y);
}

void draw_circle(SDL_Renderer* ren, int cx, int cy, int r) {
  bool even_circle = (r % 2 == 0);
  int rad = r % 2 == 0 ? r - 1 : r;

  int t1 = rad / 16;
  int t2 = 0;
  int x = rad, y = 0;

  while (x >= y) {
    draw_circle_points(ren, cx, cy, x, y, even_circle);

    y++;
    t1 = t1 + y;
    t2 = t1 - x;
    if (t2 >= 0)
      t1 = t2, x--;
  }
}

void draw_line(SDL_Renderer* ren, SDL_Point p1, SDL_Point p2) {
  SDL_RenderDrawLine(ren, p1.x, p1.y, p2.x, p2.y);
};

}  // namespace SM