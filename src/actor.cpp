#include "actor.h"

Actor::Actor() {
  this->velocity = 3.5f;
  position.x = 100;
  position.y = 400;
  size.x = 120;  // width
  size.y = 150;  // height

  curDir = direction::RIGHT;
}

void Actor::move(direction direction, float deltaTime) {
  curDir = direction;
  switch (direction) {
    case direction::UP:
      position.y += deltaTime * -velocity;
      break;
    case direction::DOWN:
      position.y += deltaTime * velocity;
      break;
    case direction::RIGHT:
      position.x += deltaTime * velocity;
      break;
    case direction::LEFT:
      position.x += deltaTime * -velocity;
      break;
  }
  std::cout << "x: " << position.x << " y: " << position.y << "\n";
}
/* Checks whether player/demon collides with another entity
    returns true if performed a successful collision
 */
