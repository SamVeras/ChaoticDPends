#include "trail.hh"
#include <iostream>
#include "fun_sdl.hh"

SM::Trail::Trail(SDL_Color trail_color, int trail_size)
    : points(), color(trail_color), trail_size(trail_size){};

void SM::Trail::add_point(SDL_Point& point) {
  points.push_back(point);
};

void SM::Trail::update() {
  if (points.size() > trail_size)
    points.pop_front();
}
void SM::Trail::draw(SDL_Renderer* ren) const {
  bool      first = true;
  SDL_Point prev{0, 0};
  int       c = 0;

  for (const auto p : points) {
    if (first) {
      first = false, prev = p;
      continue;
    }

    Uint8     a  = color.a * ((float)c++ / trail_size);
    SDL_Color nc = {color.r, color.g, color.b, a};

    set_renderer_color(ren, nc);
    draw_line(ren, prev, p);
    prev = p;
  }
}
