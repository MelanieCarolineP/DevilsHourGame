#ifndef _ACTOR_H_
#define _ACTOR_H_
#include <iostream>

#include "entity.h"
#include "enum.h"
/**
 * @brief Actor handles all the enities in the game that move independently
 *
 */
class Actor : public Entity {
 public:
  /**
   * @brief contructor
   */
  Actor();
  /* members */
  void move(direction, float deltaTime); /**< handles movement */

 private:
  float velocity; /**< how fast they move */
  direction curDir;
};

#endif /* _ACTOR_H_ */
