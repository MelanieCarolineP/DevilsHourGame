#ifndef _ACTOR_H_
#define _ACTOR_H_
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

  float velocity; /**< how fast they move */

  int getX() { return position.x; }
  int getY() { return position.y; }

  void move(direction, float deltaTime); /**< handles movement */

  void checkWithinWalls();

  void collision(); /**< handles when the actor in in contact with something */

  direction getDirection() { return curDir; }

 private:
  direction curDir;
};

#endif /* _ACTOR_H_ */
