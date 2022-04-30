#include "eventManager.h"

EventManager::EventManager(GameView* gameView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
}

/**
 * @brief Takes in the events from the SDL event queue and processes it within
 * the game
 *
 * @param event - the SDL event
 * @param deltaTime - the time change between events last event
 */

void EventManager::handle_event(SDL_Event* event, float deltaTime, float time,
                                bool* running, SDL_Renderer* renderer) {
  if (event->type == SDL_QUIT) {
    exitEvent(event, time, running);
  } else if (event->type == SDL_KEYDOWN) {
    if (isPaused == false) {
      switch (event->key.keysym.sym) {
        case SDLK_w:
          playerMovement(deltaTime, direction::UP, renderer);
          break;
        case SDLK_a:
          playerMovement(deltaTime, direction::LEFT, renderer);
          break;
        case SDLK_s:
          playerMovement(deltaTime, direction::DOWN, renderer);
          break;
        case SDLK_d:
          playerMovement(deltaTime, direction::RIGHT, renderer);
          break;
        case SDLK_e:
          playerInteraction(event, deltaTime);
          break;
        case SDLK_i:
          inventoryChange();
          break;
        case SDLK_ESCAPE:
          pauseGame(time);
          break;
      }
    } else {
      switch (event->key.keysym.sym) {
        case SDLK_q:
          exitEvent(event, time, running);
          break;
        case SDLK_r:
          isPaused = false;
          returnToGame();
          break;
      }
    }
  }
}
/* Moves and draws the main character on the screen */
void EventManager::playerMovement(float deltaTime, direction direction,
                                  SDL_Renderer* renderer) {
  mainActor.move(direction, deltaTime);
  mainActor.collision(curRoom.entityList);
  // gameView.drawActor(mainActor.position, mainActor.size, direction);
  curDir = direction;

  // std::cout << "gamedis \n";
  // gameView->displayGame(&mainActor);
  // std::cout << "display game done \n";

  // gameView->presentScreen();
}

void EventManager::playerInteraction(SDL_Event* event, float deltaTime) {
  // interact returns entity only if character is colliding with an object
  if (mainActor.collision(curRoom.entityList)) mainActor.interact();
  // otherwise do nothing
}

void EventManager::pauseGame(float time) {
  isPaused = true;
  gameView->drawPauseMenu();
  gameView->presentScreen();
}
void EventManager::startGame(void) {
  Room foyer = Room();
  this->curRoom = foyer;
  this->currRoomName = Rooms::foyer;
  gameView->drawRoom(curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, direction::RIGHT);
  gameView->presentScreen();
}

void EventManager::roomChange(SDL_Event* event, float time) {
  // std::cout << "Not implemented";
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_h:
        curRoom = Room(Rooms::bedroom);
        currRoomName = Rooms::bedroom;
        gameView->drawRoom(curRoom);
        break;
      case SDLK_j:
        curRoom = Room(Rooms::kitchen);
        currRoomName = Rooms::kitchen;
        gameView->drawRoom(curRoom);
        break;
      case SDLK_k:
        curRoom = Room(Rooms::bathroom);
        currRoomName = Rooms::bathroom;
        gameView->drawRoom(curRoom);
        break;
      case SDLK_l:
        curRoom = Room(Rooms::foyer);
        currRoomName = Rooms::foyer;
        gameView->drawRoom(curRoom);
        break;
    }
  }
}
void EventManager::returnToGame(void) {
  gameView->clearScreen();
  gameView->drawRoom(this->curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, direction::RIGHT);
  gameView->presentScreen();
}

void EventManager::demonMovement(SDL_Event* event, float deltaTime) {
  // std::cout << "Not implemented";
}
void EventManager::inventoryChange() {
  // std::cout << "Not implemented";
  curItem += 1;
  curItem %= 8;
  // gameView.drawInventory(curItem + 1);
}

void EventManager::exitEvent(SDL_Event* event, float time, bool* running) {
  *running = false;
}
