#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include "enum.h"
#include "spritesheet.h"
#include "vec2d.h"

class GameView {
 public:
  /* constructor */
  GameView();

  /* methods to draw element */
  void drawUI();
  void drawRoom();
  void drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
                 direction direction);
  void drawDoor();
  void drawInventory();

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SpriteSheet man;
  SDL_Rect rect;
};

#endif /* _GAMEVIEW_H_ */