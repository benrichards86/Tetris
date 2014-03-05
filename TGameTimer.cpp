#include <SDL.h>

#include <functional>
#ifdef DEBUG
#include <iostream>
#endif
#include "TGameTimer.hpp"

TGameTimer::TGameTimer() {
  old_time = 0;
  enabled = true;
  callback_func = NULL;
  loop_mode = FOREVER;
  repeat_count = max_repeat_count = 0;
}

TGameTimer::~TGameTimer() {
}

void TGameTimer::SetCallback(std::function<void()> func) {
  callback_func = func;
}

void TGameTimer::ResetTimer() {
  repeat_count = 0;
  old_time = SDL_GetTicks();
}

void TGameTimer::OnLoop() {
  if (enabled) {
    if (SDL_GetTicks() < old_time + timer_rate)
      return;

#ifdef DEBUG
    std::cout << "Tick!" << std::endl;
    std::cout << "loop mode = " << loop_mode << std::endl;
#endif
    
    old_time = SDL_GetTicks();
    
    if (callback_func)
      callback_func();

    switch(loop_mode) {
    case ONCE:
      enabled = false;
      break;
    case REPEATCOUNT:
      repeat_count += 1;
      if (repeat_count > max_repeat_count)
        enabled = false;
      break;
    case FOREVER:
    default:
      break;
    }
  }
}
