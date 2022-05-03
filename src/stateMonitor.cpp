#include "stateMonitor.h"

StateMonitor::StateMonitor() { this->currentState = ""; }

int StateMonitor::update(std::string& s) {
  this->currentState = s;
  if (currentState == "k1") return 2;
  if (currentState == "b1") return 3;
  if (currentState == "f1") return 4;
  if (currentState == "h1" || currentState == "h2" || currentState == "h3")
    return 5;
  return 0;
}

bool StateMonitor::isRoomLocked() {
  // return currentState == "b2" || currentState == "b3" || currentState ==
  // "b4";
  return false;
}