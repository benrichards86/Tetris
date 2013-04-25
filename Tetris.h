#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include <SDL/SDL.h>
#include "TSurface.h"
#include "TEvent.h"
#include "Tetrino.h"

class Tetris : public TEvent {
 private:
  bool running;
  SDL_Surface* surf_display;
  SDL_Surface* surf_tetris;
  std::vector<Tetrino*> tetrinos; // Tetrinos in play on the screen


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
