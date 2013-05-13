#ifndef TGAMETIMER_HPP
#define TGAMETIMER_HPP

#include <functional>

class TGameTimer {

public:
  TGameTimer();
  ~TGameTimer();

public:
  void SetCurrentLevel(int level);
  int GetCurrentLevel();
  void SetCallback(std::function<void()> func);
  void OnLoop();

private:
  int level;
  int timer_rate;  // milliseconds
  long old_time;
  std::function<void()> callback_func;

public:
  bool enabled;

};

#endif
