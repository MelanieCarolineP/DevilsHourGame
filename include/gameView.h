#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <iostream>

#include "constants.h"
#include "enum.h"
#include "pauseMenu.h"
#include "room.h"
#include "spriteSheet.h"
#include "vec2d.h"

class GameView {
 public:
  /* constructor */
  GameView(SDL_Renderer *renderer);

  /* methods to draw element */
  void drawStartScreen(SDL_Renderer *renderer);
  void drawUI();
  void drawRoom(Room r, Rooms room_name);
  void drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
                 direction direction);
  void drawDoor();
  void drawPauseMenu(void);
  void drawInventory();

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SpriteSheet sprite;
  SDL_Rect rect;
  PauseMenu pauseMenu;
  SDL_Renderer *renderer;
  Rooms currentRoom;
  SDL_Texture *roomTexture;
};

#endif /* _GAMEVIEW_H_ */