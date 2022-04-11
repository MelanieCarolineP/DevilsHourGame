#ifndef _ROOM_H_
#define _ROOM_H_

#include <tinyxml2.h>

#include <string>
#include <vector>

#include "constants.h"
#include "entity.h"

class Room : public Entity {
 public:
  /* constructor */
  Room();
  Room(Vec2d vec);
  Room(Vec2d vec, std::vector<Entity*>& entityList);

  /* Members */
  Vec2d size;
  std::vector<Entity*> entityList;

  /* Get entity list from xml file */
  void getEntities(Rooms r);

 private:
  int generateEntityList(std::string& s);
};

#endif /* _ROOM_H_ */