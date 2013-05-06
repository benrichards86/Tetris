#ifndef TETRIS_HPP
#define TETRIS_HPP

#ifdef _WIN32
#include <windows.h>
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

#include <vector>

#include <gl/gl.h>
#include <gl/glu.h>

#include "RGBColor.hpp"
#include "TEvent.hpp"
#include "Tetrino.hpp"

namespace tetris {

class Tetris : public TEvent {
 private:
  bool running;
  SDL_Surface* surf_display;
  std::vector<Tetrino*> tetrinos; // Tetrinos in play on the screen

  int resolution_x;
  int resolution_y;

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

 public:
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

}

#endif
