#ifndef TGAMETIMER_HPP
#define TGAMETIMER_HPP

#include <functional>

class TGameTimer {

public:
  TGameTimer();
  ~TGameTimer();

public:
  void SetCallback(std::function<void()> func);
  void ResetTimer();
  void OnLoop();

private:
  long old_time;
  std::function<void()> callback_func;

public:
  int timer_rate;  // milliseconds
  bool enabled;

};

#endif
