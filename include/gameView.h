#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <iostream>

#include "enum.h"
#include "room.h"
#include "spriteSheet.h"
#include "vec2d.h"

class GameView {
 public:
  /* constructor */
  GameView();

  /* methods to draw element */
  void drawStartScreen(SDL_Renderer *renderer);
  void drawUI();
  void drawRoom(SDL_Renderer *renderer, Room r);
  void drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
                 direction direction);
  void drawDoor();
  void drawInventory();

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SpriteSheet sprite;
  SDL_Rect rect;
};

#endif /* _GAMEVIEW_H_ */