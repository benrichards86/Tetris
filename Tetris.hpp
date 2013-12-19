#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "RGBColor.hpp"
#include "TEvent.hpp"
#include "Tetrino.hpp"
#include "TField.hpp"
#include "TGameTimer.hpp"

namespace tetris {

class Tetris : public TEvent {
 private:
  bool running;
  SDL_Window* window;
  SDL_GLContext context;
  TField play_field;

  int resolution_x;
  int resolution_y;
  bool fullscreen;   // true = fullscreen mode, false = windowed mode

  int level;
  int score;

  bool game_over;

  TGameTimer game_timer;

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
  void OnKeyUp(SDL_Keycode sym, Uint16 mod);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
  bool SetDisplayMode(int res_x, int res_y, int bpp, bool fullscreen_mode);

 public:
  void GameOver();
};

}

#endif
