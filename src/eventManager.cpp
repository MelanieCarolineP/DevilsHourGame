#include "eventManager.h"

EventManager::EventManager(GameView* gameView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  this->bathroomDialog = Dialog(Rooms::bathroom);
  this->bedroomDialog = Dialog(Rooms::bedroom);
  this->kitchenDialog = Dialog(Rooms::kitchen);
  this->foyerDialog = Dialog(Rooms::foyer);
  this->hallwayDialog = Dialog(Rooms::hallway);
  inventory.addItem("crowbar");
  inventory.addItem("flashlight");
  inventory.addItem("hairpin");
  inventory.addItem("knife");
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
  Uint8 const* keystate = SDL_GetKeyboardState(NULL);
  keystate = SDL_GetKeyboardState(NULL);
  if (event->type == SDL_QUIT) {
    exitEvent(event, time, running);
  }

  if (event->key.keysym.sym == SDLK_x && !gameStarted) {
    startGame();
    gameStarted = true;
  } else if (gameStarted) {
    if (keystate[SDL_SCANCODE_W]) {
      playerMovement(deltaTime, direction::UP, renderer);
    }
    if (keystate[SDL_SCANCODE_A]) {
      playerMovement(deltaTime, direction::LEFT, renderer);
    }
    if (keystate[SDL_SCANCODE_S]) {
      playerMovement(deltaTime, direction::DOWN, renderer);
    }
    if (keystate[SDL_SCANCODE_D]) {
      playerMovement(deltaTime, direction::RIGHT, renderer);
    }
    if (event->type == SDL_KEYDOWN) {
      if (isPaused == false && isDialog == false) {
        switch (event->key.keysym.sym) {
          case SDLK_e:
            playerInteraction();
            break;

          case SDLK_SPACE:
            playerInteraction();
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
            roomChange(Rooms::bedroom);
            break;
          case SDLK_j:
            roomChange(Rooms::kitchen);
            break;
          case SDLK_k:
            roomChange(Rooms::bathroom);
            break;
          case SDLK_l:
            roomChange(Rooms::foyer);
            break;
          case SDLK_p:
            roomChange(Rooms::hallway);
          case SDLK_9:
            gameView->drawWinningScreen();
            gameView->presentScreen();
            gameStarted = false;
            break;
          case SDLK_0:
            gameView->drawLosingScreen();
            gameView->presentScreen();
            gameStarted = false;
            break;
          case SDLK_t:
            showEntity = !showEntity;
            break;

          case SDLK_ESCAPE:
            pauseGame(time);
            break;
        }

        if (!isPaused && !isDialog && gameStarted) {
          // std::cout << "display_game" << std::endl;
          displayGame();
          // clock.update(deltaTime);
        }

      } else if (isPaused) {
        handlePausedEvent(event, deltaTime, time, running, renderer);
      } else if (isDialog) {
        handleDialogEvent(event, deltaTime, time, running, renderer);
      }
    } else if (isPaused == false && isDialog == false && gameStarted) {
      displayGame();
    } else if (isDialog) {
      displayDialog();
    }

    // Checking if the timer has run out
    if (clock.isTimeOut()) {
      gameStarted = false;
      loseScreen();
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
  mainActor.move(direction, deltaTime, curRoom.entityList);
  // mainActor.collision(curRoom.entityList);
  mainActor.collisionDetection(direction, curRoom.entityList);
  // gameView.drawActor(mainActor.position, mainActor.size, direction);
  curDir = direction;

  // std::cout << mainActor.position.x << std::endl;
  // std::cout << mainActor.position.y << std::endl;

  // std::cout << "gamedis \n";
  // gameView->displayGame(&mainActor);
  // std::cout << "display game done \n";

  // gameView->presentScreen();
}

void EventManager::playerInteraction() {
  // interact returns entity only if character is colliding with an object
  // if (mainActor.collision(curRoom.entityList)) mainActor.interact();
  // otherwise do nothing
  // std::cout << mainActor.interact(curRoom.entityList) << std::endl;

  std::string object = mainActor.interact(curRoom.entityList);
  // std::cout << "object: " << object << std::endl;
  std::string item(inventory.getSelectedItem());
  // std::cout << "item: " << item << std::endl;
  // std::cout << "current state: " << stateMonitor.currentState << std::endl;
  int id = curDialog.triggerDialog(mainActor.position, object, item,
                                   stateMonitor.currentState);
  // std::cout << "id: " << id << std::endl;
  if (id < 0) return;

  dialog* d = &(curDialog.dialogList[id]);
  int switchToRoom = stateMonitor.update(d->transitToState);
  // std::cout << "transit to state: " << d->transitToState << std::endl;

  // handle doors
  if (!stateMonitor.isRoomLocked()) {
    if (switchToRoom == 1) {
      roomChange(Rooms::bedroom);
    } else if (switchToRoom == 2) {
      roomChange(Rooms::kitchen);
    } else if (switchToRoom == 3) {
      roomChange(Rooms::bathroom);
    } else if (switchToRoom == 4) {
      roomChange(Rooms::foyer);
    } else if (switchToRoom == 5) {
      roomChange(Rooms::hallway);
    }
  }
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

void EventManager::loseScreen(void) {
  gameView->drawLosingScreen();
  gameView->presentScreen();
}

void EventManager::winScreen(void) {
  gameView->drawWinningScreen();
  gameView->presentScreen();
}

void EventManager::startGame(void) {
  // Room foyer = Room();
  // this->curRoom = Room(Rooms::bedroom);
  roomChange(Rooms::bedroom);
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

void EventManager::roomChange(Rooms r) {
  curRoom = Room(r);
  currRoomName = r;
  curDialog = Dialog(r);
  // gameView->drawRoom(&curRoom);
  mainActor.position.x = curRoom.bornX;
  mainActor.position.y = curRoom.bornY;
  mainActor.setBoundary(curRoom.boundX, curRoom.boundY, curRoom.boundW,
                        curRoom.boundH);
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
  // curItem += 1;
  // curItem %= 8;
  inventory.changeSelectedItem();
}

void EventManager::exitEvent(SDL_Event* event, float time, bool* running) {
  *running = false;
}

void EventManager::displayGame() {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(inventory.currentPosition + 1);
  gameView->drawItems(&inventory);
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
  gameView->drawItems(&inventory);
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
      "vitae sollicitudin sem mi vitae sem. Suspendisse potenti.",
      "Bob");
  gameView->presentScreen();
}
