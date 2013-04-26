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

// Tetrinos in a 80x80 pixel square, grid lines every 20px

bool Tetrino::OnLoad(int type) {
  if ((surf_entity = SDL_CreateRGBSurface(0, 100, 100, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff)) == false)
    return false;

  switch(type) {
  case 0: {
    SDL_Rect shapes[2];
    shapes[0].x = 0;
    shapes[0].y = 20;
    shapes[0].w = 20;
    shapes[0].h = 40;
    shapes[1].x = 0;
    shapes[1].y = 60;
    shapes[1].w = 40;
    shapes[1].h = 20;
    SDL_FillRect(surf_entity, &shapes[0], SDL_MapRGB(surf_entity->format, 255, 100, 100));
    SDL_FillRect(surf_entity, &shapes[1], SDL_MapRGB(surf_entity->format, 255, 100, 100));
    break;
  }
  case 1: {
    SDL_Rect shape;
    shape.x = 20;
    shape.y = 0;
    shape.w = 20;
    shape.h = 80;
    SDL_FillRect(surf_entity, &shape, SDL_MapRGB(surf_entity->format, 255, 255, 100));
    break;
  }
  case 2: {
    SDL_Rect shapes[2];
    shapes[0].x = 40;
    shapes[0].y = 20;
    shapes[0].w = 20;
    shapes[0].h = 40;
    shapes[1].x = 20;
    shapes[1].y = 60;
    shapes[1].w = 40;
    shapes[1].h = 20;
    SDL_FillRect(surf_entity, &shapes[0], SDL_MapRGB(surf_entity->format, 100, 100, 255));
    SDL_FillRect(surf_entity, &shapes[1], SDL_MapRGB(surf_entity->format, 100, 100, 255));
    break;
  }
  case 3: {
    SDL_Rect shapes[2];
    shapes[0].x = 0;
    shapes[0].y = 60;
    shapes[0].w = 60;
    shapes[0].h = 20;
    shapes[1].x = 20;
    shapes[1].y = 40;
    shapes[1].w = 20;
    shapes[1].h = 20;
    SDL_FillRect(surf_entity, &shapes[0], SDL_MapRGB(surf_entity->format, 100, 255, 100));
    SDL_FillRect(surf_entity, &shapes[1], SDL_MapRGB(surf_entity->format, 100, 255, 100));
    break;
  }
  case 4: {
    SDL_Rect shapes[2];
    shapes[0].x = 0;
    shapes[0].y = 40;
    shapes[0].w = 40;
    shapes[0].h = 20;
    shapes[1].x = 20;
    shapes[1].y = 60;
    shapes[1].w = 40;
    shapes[1].h = 20;
    SDL_FillRect(surf_entity, &shapes[0], SDL_MapRGB(surf_entity->format, 255, 100, 255));
    SDL_FillRect(surf_entity, &shapes[1], SDL_MapRGB(surf_entity->format, 255, 100, 255));
    break;
  }
  case 5: {
    SDL_Rect shapes[2];
    shapes[0].x = 20;
    shapes[0].y = 40;
    shapes[0].w = 40;
    shapes[0].h = 20;
    shapes[1].x = 0;
    shapes[1].y = 60;
    shapes[1].w = 40;
    shapes[1].h = 20;
    SDL_FillRect(surf_entity, &shapes[0], SDL_MapRGB(surf_entity->format, 100, 255, 255));
    SDL_FillRect(surf_entity, &shapes[1], SDL_MapRGB(surf_entity->format, 100, 255, 255));
    break;
  }
  default: {
    std::cout << "Wrong type!" << std::endl;
    break;
  }
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
