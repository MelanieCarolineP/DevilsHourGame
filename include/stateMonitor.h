#ifndef _STATEMONITOR_H_
#define _STATEMONITOR_H_

class StateMonitor {
 public:
  /* constructor */
  StateMonitor();

  /* returns current game state */
  int getState();
  /* update current game state */
  void update();

 private:
  int currentState;
};

#endif /* _STATEMONITOR_H_ */