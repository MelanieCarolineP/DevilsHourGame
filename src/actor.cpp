#include "actor.h"

Actor::Actor() {
  velocity = 3.5f;
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
/* Checks whether player/demon collides with another entity */
bool Actor::collision(Entity entity) {
  // checking horizontally
  if ((entity.position.x <= this->size.x) &&
      (this->position.x <= entity.size.x))

    if ((entity.position.y <= this->size.y) &&
        (this->position.y <= entity.size.y))
      return true;

  return false;
}
