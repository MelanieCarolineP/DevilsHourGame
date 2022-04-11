#include "actor.h"

Actor::Actor() {
  velocity = 70.0;
  position.x = 100;
  position.y = 100;
  size.x = 150;  // width
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
}
// Given a sprite sheet reference, it will draw for us, we delegate which one
// to use We will animate in this class
// given delta time divide this by 2 to animate the movement (two frame
// changes within the delta time)