#ifndef _STATEMONITOR_H_
#define _STATEMONITOR_H_

#include <string>

class StateMonitor {
 public:
  /* constructor */
  StateMonitor();

  /* returns current game state */
  std::string& getState();
  /* update current game state */
  void update(std::string& s);

 private:
  std::string currentState;
};

#endif /* _STATEMONITOR_H_ */