#ifndef TETRIS_HPP
#define TETRIS_HPP

#ifdef _WIN32
#include <windows.h>
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "RGBColor.hpp"
#include "TEvent.hpp"
#include "Tetrino.hpp"
#include "TField.hpp"

namespace tetris {

class Tetris : public TEvent {
 private:
  bool running;
  SDL_Surface* surf_display;
  TField play_field;

  int resolution_x;
  int resolution_y;
  bool fullscreen;   // true = fullscreen mode, false = windowed mode

  int scale;

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

private:
  bool SetDisplayMode(int res_x, int res_y, int bpp, bool fullscreen_mode);

 public:
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

}

#endif
