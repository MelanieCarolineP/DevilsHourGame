#include "room.h"

Room::Room() {
  Vec2d vec(400, 300);
  this->size = vec;
}

Room::Room(Vec2d size) { this->size = size; }

Room::Room(Vec2d size, std::vector<Entity*>& entityList) {
  this->size = size;
  this->entityList = entityList;
}

void Room::getEntities(Rooms r) {
  switch (r) {
    case Rooms::bathroom:
      generateEntityList("../data/rooms/bathroom.xml");
      break;

    default:
      break;
  }
}

void Room::generateEntityList(const char* s) { return; }