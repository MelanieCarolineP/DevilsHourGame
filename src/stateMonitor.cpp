#include "stateMonitor.h"

StateMonitor::StateMonitor() { this->currentState = ""; }

std::string& StateMonitor::getState() { return this->currentState; }

void StateMonitor::update(std::string& s) { this->currentState = s; }