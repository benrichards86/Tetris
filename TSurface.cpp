#include "TSurface.h"

TSurface::TSurface() {
}

bool TSurface::OnDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y) {
  if (dest == NULL || src == NULL)
    return false;

  SDL_Rect dest_r;

  dest_r.x = x;
  dest_r.y = y;

  SDL_BlitSurface(src, NULL, dest, &dest_r);

  return true;
}
