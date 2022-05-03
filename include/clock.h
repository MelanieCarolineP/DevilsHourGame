#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <iostream>
#include <string>

#include "SDL.h"

class Clock {
 public:
  Clock(){};
  void start();
  void update(float deltaTime);
  void pause();
  bool isTimeOut();
  std::string getCurTime();

 private:
  Uint32 startTime;
  bool isPaused = true;
  float timeElapsed = 0.0f;
  float totalTime = 600000.0f;
};

#endif /* _CLOCK_H_ */