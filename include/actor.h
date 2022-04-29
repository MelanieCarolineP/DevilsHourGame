#ifndef _ACTOR_H_
#define _ACTOR_H_
#include <iostream>
#include <vector>

#include "entity.h"
#include "enum.h"
#include "room.h"
/**
 * @brief Actor handles all the enities in the game that move independently
 *
 */
class Actor : public Entity {
 public:
  /* constructor */
  Actor();
  /* methods */

  void move(direction, float deltaTime); /**< handles movement */
  bool collision(const std::vector<Entity> entityList);

  /**
   * @brief returns entity most recently in contact with
   * @returns object in room
   */
  Entity interact() { return entity; }

  direction getDirection(void) { return curDir; }

 private:
  /* members */
  float velocity; /**< how fast they move */
  direction curDir;
  Entity entity;  // entity collided into last
  bool canWalkOnCollision(const Entity entity);
};

#endif /* _ACTOR_H_ */
