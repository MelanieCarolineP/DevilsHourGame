#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "stateMonitor.h"

class Puzzle : public StateMonitor {
 public:
  /* constructor */
  Puzzle();

  int getProgress();
  bool isSolved();

 private:
  int step;
};

#endif /* _PUZZLE_H_ */