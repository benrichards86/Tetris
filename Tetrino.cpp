#include <iostream>
#include "Tetrino.h"

Tetrino::Tetrino() {
  surf_entity = NULL;
  x = y = 0;
}

Tetrino::~Tetrino() {
}

void Tetrino::SetLocation(int x_loc, int y_loc) {
  x = x_loc;
  y = y_loc;
}

bool Tetrino::OnLoad(int type) {
  if ((surf_entity = SDL_CreateRGBSurface(0, 100, 100, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff)) == false)
    return false;

  switch(type) {
  case 0:
    SDL_Rect shape;
    shape.x = 0;
    shape.y = 0;
    shape.w = 100;
    shape.h = 100;
    SDL_FillRect(surf_entity, &shape, SDL_MapRGB(surf_entity->format, 255, 100, 100));
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  default:
    std::cout << "Wrong type!" << std::endl;
    break;
  }

  return true;
}

void Tetrino::OnLoop() {
}

void Tetrino::OnRender(SDL_Surface* surf_display) {
  if (surf_entity == NULL || surf_display == NULL) return;

  TSurface::OnDraw(surf_display, surf_entity, x, y);
}

void Tetrino::OnCleanup() {
  if (surf_entity) {
    SDL_FreeSurface(surf_entity);
  }
  surf_entity = NULL;
}
