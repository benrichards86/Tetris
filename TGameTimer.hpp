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

  const unsigned int RepeatCount() {
    return repeat_count;
  }

private:
  long old_time;
  std::function<void()> callback_func;
  unsigned int repeat_count;

public:
  int timer_rate;  // milliseconds
  bool enabled;
  int loop_mode;
  unsigned int max_repeat_count;

  static const int ONE_SECOND = 1000;
  static const int ONE_MILLISECOND = 1;
  static const int FOREVER = 0;
  static const int ONCE = 1;
  static const int REPEATCOUNT = 2;
};

#endif
