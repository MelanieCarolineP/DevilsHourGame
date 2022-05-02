#include "actor.h"

/**
 * @brief Construct a new Actor:: Actor object
 *
 */
Actor::Actor() {
  velocity = 3.5f;
  position.x = 100;
  position.y = 400;
  size.x = 120;  // width
  size.y = 150;  // height

  curDir = direction::RIGHT;
}

/**
 * @brief Moves character in a desired direction
 *
 * @param direction: direction the character is headed
 * @param deltaTime: time elapsed
 */
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
/**
 * @brief Checks whether player collides with another entity  returns true if
 * performed a successful collision
 *
 * @param size
 * @returns true if a collision was successful, false otherwise
 */
bool Actor::collision(const std::vector<Entity> entityList) {  // Entity
  // check if it hits against any inside the entity list
  int n = entityList.size();
  for (int i = 0; i < n; i++) {
    entity = entityList[i];
    // if not entity, skip
    if (!entity.isEntity) continue;

    // checking horizontally
    if ((entity.position.x <= (position.x + size.x)) &&
        (position.x <= (entity.position.x + entity.size.x)))
      // checking vertically
      if ((entity.position.y <= (position.y + size.y)) &&
          (position.y <= (entity.position.y + entity.size.y))) {
        // adjust position based on which side actor is facing and if object can
        // be walked on
        if (!canWalkOnCollision(entity) && entity.isEntity) {
          switch (curDir) {
            case direction::UP:
              position.y = entity.position.y + entity.size.y;
              break;
            case direction::DOWN:
              position.y = entity.position.y - size.y;
              break;
            case direction::LEFT:
              position.x = entity.position.x + entity.size.x;
              break;
            case direction::RIGHT:
              position.x = entity.position.x - size.x;
              break;
          }
        }
        return true;
      }
  }

  return false;
}
/**
 * @brief After collision, this makes sure the character can walk next to object
 * only if it's not facing the object
 *
 * @param size
 * @returns true if character can walk this direction, false otherwise
 */
bool Actor::canWalkOnCollision(const Entity entity) {
  switch (curDir) {
    case direction::UP:
    case direction::DOWN:
      // check if actor is on the left side and right side of the object
      if ((position.x + size.x == entity.position.x) ||
          (position.x == entity.position.x + entity.size.x))
        return true;
    case direction::LEFT:
    case direction::RIGHT:
      // check top then bottom
      if ((position.y + size.y == entity.position.y) ||
          (position.y == entity.position.y + entity.size.y))
        return true;
  }
  return false;
}

bool Actor::collideWith(Entity* e) {
  // return (this->position.x >= e->position.x &&
  //         this->position.x <= (e->position.x + e->size.x)) ||
  //        (this->position.y >= e->position.y &&
  //         this->position.y <= (e->position.y + e->size.y)) ||
  //        (this->position.x + this->size.x >= e->position.x &&
  //         this->position.x + this->size.x <= (e->position.x + e->size.x)) ||
  //        (this->position.y + this->size.y >= e->position.y &&
  //         this->position.y + this->size.y <= (e->position.y + e->size.y));
  auto x1min = this->position.x;
  auto x1max = this->position.x + this->size.x;
  auto y1min = this->position.y;
  auto y1max = this->position.y + this->size.y;
  auto x2min = e->position.x;
  auto x2max = e->position.x + e->size.x;
  auto y2min = e->position.y;
  auto y2max = e->position.y + e->size.y;
  return x1min <= x2max && x2min <= x1max && y1min <= y2max && y2min <= y1max;
}

bool Actor::collisionDetection(direction d, std::vector<Entity>& entityList) {
  Entity* e;
  for (int i = 0; i < entityList.size(); ++i) {
    e = &entityList[i];
    if (collideWith(e)) {
      if (e->isEntity) {
        switch (d) {
          case direction::UP:
            position.y = e->position.y + e->size.y;
            break;
          case direction::DOWN:
            position.y = e->position.y - this->size.y;
            break;
          case direction::LEFT:
            position.x = e->position.x + e->size.x;
            break;
          case direction::RIGHT:
            position.y = e->position.x - this->size.x;
            break;

          default:
            break;
        }
      }
      return true;
    }
  }
  return false;
}