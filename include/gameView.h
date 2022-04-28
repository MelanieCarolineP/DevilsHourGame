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
  GameView();

  /* methods to draw element */
  void drawStartScreen(SDL_Renderer *renderer);
  void drawRoom(SDL_Renderer *renderer, Room r);
  void drawUI(SDL_Renderer *renderer);
  void drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
                 direction direction);
  void drawDoor();
  void drawInventory(SDL_Renderer *renderer, int k);

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SpriteSheet sprite;
  SDL_Rect rect;
};

#endif /* _GAMEVIEW_H_ */