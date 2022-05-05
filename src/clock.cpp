#include "clock.h"

void Clock::start() {
  isPaused = false;
  startTime = SDL_GetTicks();
  // std::cout << "start time:" << startTime << std::endl;
}

void Clock::update(float deltaTime) {
  timeElapsed += deltaTime;
  std::cout << deltaTime << std::endl;
  std::cout << getCurTime() << std::endl;
}

bool Clock::isTimeOut() {
  return (SDL_GetTicks() + punishment - startTime) > totalTime;
}

std::string Clock::getCurTime() {
  Uint32 curTime = SDL_GetTicks() + punishment;
  // std::cout << "cur time:" << curTime << std::endl;
  std::string s = "02:";
  int minute = (curTime - startTime) / totalTime * 60;
  if (minute < 10) s += "0";
  s += std::to_string(minute);
  if (minute == 60) s = "03:00";
  // std::cout << s << std::endl;
  return s;
}

void Clock::deductTime() { punishment += 150000; }