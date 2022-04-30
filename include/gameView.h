#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <iostream>
#include <string>

#include "actor.h"
#include "constants.h"
#include "enum.h"
#include "pauseMenu.h"
#include "room.h"
#include "spriteSheet.h"
#include "stdio.h"
#include "vec2d.h"

class GameView {
 public:
  /* constructor */
  GameView(){};

  GameView(SDL_Renderer *renderer);

  /* methods to draw element */
  void drawStartScreen(SDL_Renderer *renderer);
  void displayGame(Actor *actor);
  void drawUI();
  void drawRoom(Room r);
  void drawActor(Vec2d position, Vec2d size, direction direction);
  void drawDoor();
  void drawPauseMenu(void);

  void drawInventory(int k);
  void roomToPosition(void);
  void presentScreen(void);
  void clearScreen(void);

 private:
  /* helper function for drawInventory() */
  void drawItem();
  SDL_Renderer *renderer;
  SpriteSheet sprite;
  SDL_Rect rect;
  PauseMenu pauseMenu;
  Room *currentR;
  Rooms currentRoom;
  SDL_Texture *roomTexture;
  SDL_Rect roomDest;
};

#endif /* _GAMEVIEW_H_ */