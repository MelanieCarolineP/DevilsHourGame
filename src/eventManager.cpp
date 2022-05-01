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
  }
  if (event->key.keysym.sym == SDLK_x && !gameStarted) {
    startGame();
    gameStarted = true;
  } else if (gameStarted) {
    if (event->type == SDL_KEYDOWN) {
      if (isPaused == false && isDialog == false) {
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

          case SDLK_z:
            std::cout << "dialog";
            isDialog = true;
            displayDialog();
            break;

          // DEBUG
          case SDLK_h:
            curRoom = Room(Rooms::bedroom);
            currRoomName = Rooms::bedroom;
            gameView->drawRoom(&curRoom);
            break;
          case SDLK_j:
            curRoom = Room(Rooms::kitchen);
            currRoomName = Rooms::kitchen;
            gameView->drawRoom(&curRoom);
            break;
          case SDLK_k:
            curRoom = Room(Rooms::bathroom);
            currRoomName = Rooms::bathroom;
            gameView->drawRoom(&curRoom);
            break;
          case SDLK_l:
            curRoom = Room(Rooms::foyer);
            currRoomName = Rooms::foyer;
            gameView->drawRoom(&curRoom);
            break;
          case SDLK_t:
            showEntity = !showEntity;
            break;

          case SDLK_ESCAPE:
            pauseGame(time);
            break;
        }

        if (!isPaused && !isDialog) {
          // std::cout << "display_game" << std::endl;
          displayGame();
          // clock.update(deltaTime);
        }

      } else if (isPaused) {
        handlePausedEvent(event, deltaTime, time, running, renderer);
      } else {
        handleDialogEvent(event, deltaTime, time, running, renderer);
      }
    } else if (isPaused == false && isDialog == false) {
      displayGame();
    } else if (isDialog) {
      displayDialog();
    }
  }
}

void EventManager::handlePausedEvent(SDL_Event* event, float deltaTime,
                                     float time, bool* running,
                                     SDL_Renderer* renderer) {
  switch (event->key.keysym.sym) {
    case SDLK_q:
      exitEvent(event, time, running);
      break;
    case SDLK_r:
      returnToGame();
      break;
    case SDLK_ESCAPE:
      returnToGame();
      break;
  }
}

void EventManager::handleDialogEvent(SDL_Event* event, float deltaTime,
                                     float time, bool* running,
                                     SDL_Renderer* renderer) {
  switch (event->key.keysym.sym) {
    case SDLK_e:
      isDialog = false;
      displayGame();
      break;
  }
  if (isDialog) {
    displayDialog();
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

void EventManager::startScreen(void) {
  gameView->drawStartScreen();
  gameView->presentScreen();
}

void EventManager::startGame(void) {
  // Room foyer = Room();
  this->curRoom = Room(Rooms::bedroom);
  clock.start();
  // gameView->clearScreen();
  // gameView->drawUI();
  // gameView->drawInventory(curItem + 1);
  // gameView->drawRoom(curRoom);
  // gameView->drawActor(mainActor.position, mainActor.size,
  // direction::RIGHT); gameView->roomToPosition(); gameView->presentScreen();

  // displayGame();
  startScreen();
}

void EventManager::roomChange(SDL_Event* event, float time) {
  // std::cout << "Not implemented";
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_h:
        curRoom = Room(Rooms::bedroom);
        currRoomName = Rooms::bedroom;
        gameView->drawRoom(&curRoom);
        break;
      case SDLK_j:
        curRoom = Room(Rooms::kitchen);
        currRoomName = Rooms::kitchen;
        gameView->drawRoom(&curRoom);
        break;
      case SDLK_k:
        curRoom = Room(Rooms::bathroom);
        currRoomName = Rooms::bathroom;
        gameView->drawRoom(&curRoom);
        break;
      case SDLK_l:
        curRoom = Room(Rooms::foyer);
        currRoomName = Rooms::foyer;
        gameView->drawRoom(&curRoom);
        break;
    }
  }
}
void EventManager::returnToGame(void) {
  isPaused = false;
  std::cout << "resume game" << std::endl;
  // gameView->clearScreen();
  // gameView->drawUI();
  // gameView->drawInventory(curItem + 1);
  // gameView->drawRoom(this->curRoom);
  // gameView->drawActor(mainActor.position, mainActor.size, curDir);
  // gameView->roomToPosition();
  // gameView->presentScreen();
  displayGame();
}

void EventManager::demonMovement(SDL_Event* event, float deltaTime) {
  // std::cout << "Not implemented";
}
void EventManager::inventoryChange() {
  // std::cout << "Not implemented";
  curItem += 1;
  curItem %= 8;
}

void EventManager::exitEvent(SDL_Event* event, float time, bool* running) {
  *running = false;
}

void EventManager::displayGame() {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(curItem + 1);
  gameView->drawRoom(&curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, curDir);
  gameView->roomToPosition();
  // debug
  if (showEntity) gameView->drawEntities(&curRoom);
  gameView->presentScreen();
}

void EventManager::displayDialog(void) {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(curItem + 1);
  gameView->drawRoom(&this->curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, curDir);
  gameView->roomToPosition();

  gameView->drawDialog(
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin "
      "fringilla libero id lobortis malesuada. In auctor eu ante at "
      "efficitur."

      "Etiam facilisis nec odio nec commodo. Aliquam at metus ac orci "
      "fringilla mollis ac a leo. Sed justo ex, lacinia facilisis ante id, "
      "posuere elementum mauris. Suspendisse potenti. Curabitur sit amet "
      "rutrum nibh. Praesent lobortis elit lorem, sit amet egestas dui "
      "pulvinar ut. Curabitur lorem metus, facilisis sed dolor non, pretium "
      "bibendum purus. Pellentesque mollis vel magna sit amet consectetur. "
      "Curabitur elit lectus, imperdiet eu aliquet a, elementum in tellus. "
      "Fusce faucibus, nibh at sodales facilisis, nulla urna malesuada "
      "massa, "
      "vitae sollicitudin sem mi vitae sem. Suspendisse potenti.");
  gameView->presentScreen();
}
