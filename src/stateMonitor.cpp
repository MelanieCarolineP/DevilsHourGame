#include "stateMonitor.h"

StateMonitor::StateMonitor() { this->currentState = ""; }

int StateMonitor::update(std::string& s) {
  this->currentState = s;
  if (currentState == "bedroom_door") return 1;
  if (currentState == "kitchen_door") return 2;
  if (currentState == "bathroom_door") return 3;
  if (currentState == "foyer_door") return 4;
  if (currentState == "hallway_door") return 5;
  return 0;
}

bool StateMonitor::isRoomLocked() {
  // return currentState == "b2" || currentState == "b3" || currentState ==
  // "b4";
  return false;
}