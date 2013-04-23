#ifndef TSURFACE_H
#define TSURFACE_H

#include <SDL/SDL.h>

class TSurface {
 public:
  TSurface();

 public:
  static bool OnDraw(SDL_Surface* dest, SDL_Surface* src, int x, int y);

};

#endif
