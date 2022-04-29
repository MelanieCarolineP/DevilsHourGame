#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>

#include "actor.h"
#include "enum.h"
#include "gameView.h"
#include "room.h"
#include "vec2d.h"

class EventManager {
 public:
  /* constructor */
  EventManager();
  void handle_event(SDL_Event event, float deltaTime, float time, bool* running,
                    SDL_Renderer* renderer);
  void playerMovement(float deltaTime, direction direction,
                      SDL_Renderer* renderer);
  void playerInteraction(SDL_Event event, float delaTime);
  void pauseGame(SDL_Event event, float time);
  void roomChange(SDL_Event event, float time);
  void demonMovement(SDL_Event event, float deltaTime);
  void inventoryChange(SDL_Event event, float deltaTime,
                       SDL_Renderer* renderer);

  void exitEvent(SDL_Event event, float time, bool* running);
  int curItem = 0;

 private:
  Actor mainActor;
  Room curRoom;
};

#endif
