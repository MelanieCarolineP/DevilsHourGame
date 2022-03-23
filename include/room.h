#ifndef _ROOM_H_
#define _ROOM_H_

#include <vector>

#include "entity.h"

class Room : public Entity {
 public:
  /* constructor */
  Room();

  /* Members */
  Vec2d size;
  std::vector<Entity*> entityList;

  /* Get entity list from xml file */
  void getEntities();
}

#endif /* _ROOM_H_ */