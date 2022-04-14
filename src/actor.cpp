#include "actor.h"

Actor::Actor() {
  velocity = 2.5f;
  position.x = 100;
  position.y = 400;
  size.x = 220;  // width
  size.y = 240;  // height

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
  // checkWithinWalls();
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
/* checks whether user is within walls
void Actor::checkWithinWalls() {
  if (position.x >= SCREEN_WIDTH - size.x)
    position.x = (SCREEN_WIDTH - size.x);
  else if (position.x <= 0)
    position.x = 0;
  else if (position.y >= SCREEN_HEIGHT - size.y)
    position.y = (SCREEN_HEIGHT - size.y);
  else if (position.y <= 0)
    position.y = 0;
} */