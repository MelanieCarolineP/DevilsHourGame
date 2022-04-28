#ifndef _STATEMONITOR_H_
#define _STATEMONITOR_H_

#include <string>

#include "constants.h"

class StateMonitor {
 public:
  /* constructor */
  StateMonitor();

  /* update current game state */
  void update(std::string& s);

  bool isRoomLocked();

  std::string currentState;
  bool isPaused;
};

#endif /* _STATEMONITOR_H_ */