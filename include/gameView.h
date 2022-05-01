#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include <iostream>
#include <string>

#include "actor.h"
#include "constants.h"
#include "enum.h"
#include "pauseMenu.h"
#include "room.h"
#include "speechBox.h"
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
  void drawRoom(Room *r);

  void drawEntities(Room *r);

  void drawActor(Vec2d position, Vec2d size, direction direction);
  void drawDoor();
  void drawPauseMenu(void);
  void drawDialog(const char *text);
  void drawInventory(int k);
  void displayTime(std::string s);
  void roomToPosition(void);
  void presentScreen(void);
  void clearScreen(void);

 private:
  SDL_Renderer *renderer;
  SpriteSheet sprite;

  SpeechBox speechbox;
  PauseMenu pauseMenu;

  TTF_Font *clockFont;

  SDL_Rect rect;
  SDL_Rect roomDest;

  SDL_Texture *roomTexture;

  Room *currentR;
  Rooms currentRoom;

  /* helper function for drawInventory() */
  void drawItem();
};

#endif /* _GAMEVIEW_H_ */
