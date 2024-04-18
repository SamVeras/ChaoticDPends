#include "draw_utils.hh"
namespace SM {
int set_color(SDL_Renderer *ren, const SDL_Color &color) {
  return SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
}
}  // namespace SM