#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

#include <functional>
#include "TGameTimer.hpp"

TGameTimer::TGameTimer() {
  old_time = 0;
  enabled = true;
  callback_func = NULL;
}

TGameTimer::~TGameTimer() {
}

void TGameTimer::SetCallback(std::function<void()> func) {
  callback_func = func;
}

void TGameTimer::ResetTimer() {
  old_time = SDL_GetTicks();
}

void TGameTimer::OnLoop() {
  if (enabled) {
    if (SDL_GetTicks() < old_time + timer_rate)
      return;
    
    old_time = SDL_GetTicks();
    
    if (callback_func)
      callback_func();
  }
}
