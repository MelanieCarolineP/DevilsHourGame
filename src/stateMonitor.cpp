#include "stateMonitor.h"

StateMonitor::StateMonitor() { this->currentState = ""; }

void StateMonitor::update(std::string& s) { this->currentState = s; }

bool StateMonitor::isRoomLocked() {
  return currentState == "b2" || currentState == "b3" || currentState == "b4";
}