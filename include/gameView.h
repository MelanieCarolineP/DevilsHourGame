#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <iostream>
#include <string>

#include "enum.h"
#include "room.h"
#include "spriteSheet.h"
#include "vec2d.h"

class GameView {
 public:
  /* constructor */
  GameView(SDL_Renderer* renderer);

  /* methods to draw element */
  void drawStartScreen();
  void drawRoom(Room r);
  void drawUI();
  void drawActor(Vec2d position, Vec2d size, direction direction);
  void drawDoor();
  void drawInventory(int k);

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SDL_Renderer* renderer;
  SpriteSheet sprite;
  SDL_Rect rect;
};

#endif /* _GAMEVIEW_H_ */