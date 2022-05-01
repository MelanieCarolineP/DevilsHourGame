#include "entity.h"

/**
 * @brief Entity constructor
 *
 * @param x x- cordinate
 * @param y y-cordinate
 * @param w width dimension
 * @param h height dimension
 * @return Entity object
 */
Entity::Entity() {
  Vec2d location = Vec2d(0, 0);
  Vec2d size = Vec2d(0, 0);
  this->position = location;
  this->size = size;
  this->name = name;
  this->isEntity = isEntity;
}
Entity::Entity(float x, float y, float w, float h, std::string name,
               bool isEntity) {
  Vec2d location = Vec2d(x, y);
  Vec2d size = Vec2d(w, h);
  this->position = location;
  this->size = size;
  this->name = name;
  this->isEntity = isEntity;
}
