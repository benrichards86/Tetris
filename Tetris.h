#ifndef TETRIS_H
#define TETRIS_H

#include <SDL/SDL.h>
#include "TSurface.h"
#include "TEvent.h"

class Tetris : public TEvent {
 private:
  bool running;
  SDL_Surface* surf_display;
  SDL_Surface* surf_tetris;

 public:
  Tetris();
  int OnExecute();

 public:
  bool OnInit();
  void OnEvent(SDL_Event* event);
  void OnExit();
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

#endif
