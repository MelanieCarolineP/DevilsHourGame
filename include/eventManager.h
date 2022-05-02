#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>

#include <iostream>

#include "actor.h"
#include "clock.h"
#include "enum.h"
#include "gameView.h"
#include "room.h"
#include "stateMonitor.h"
#include "stdio.h"
#include "vec2d.h"

class EventManager {
 public:
  /* constructor */
  EventManager() { this->curRoom.getEntities(Rooms::bedroom); }
  EventManager(GameView* gameView);
  void startScreen(void);
  void startGame(void);
  void handle_event(SDL_Event* event, float deltaTime, float time,
                    bool* running, SDL_Renderer* renderer);
  void playerMovement(float deltaTime, direction direction,
                      SDL_Renderer* renderer);
  void playerInteraction();
  void pauseGame(float time);
  void roomChange(Rooms r);
  void demonMovement(SDL_Event* event, float deltaTime);
  void inventoryChange();
  void returnToGame(void);
  void displayGame(void);
  void displayDialog(void);

  void handlePausedEvent(SDL_Event* event, float deltaTime, float time,
                         bool* running, SDL_Renderer* renderer);

  void handleDialogEvent(SDL_Event* event, float deltaTime, float time,
                         bool* running, SDL_Renderer* renderer);

  void exitEvent(SDL_Event* event, float time, bool* running);

  int curItem = 0;
  bool gameStarted = false;
  bool isPaused = false;
  bool isDialog = false;
  bool showEntity = false;

  GameView* gameView;
  Actor mainActor;
  direction curDir;
  Room curRoom;
  StateMonitor stateMonitor;
  Rooms currRoomName;
  Clock clock;
  Inventory inventory;
};

#endif
