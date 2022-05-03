#include "eventManager.h"

EventManager::EventManager(GameView* gameView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  inventory.addItem("crowbar");
  inventory.addItem("flashlight");
  inventory.addItem("hairpin");
  inventory.addItem("knife");

  std::vector<std::string> Text = {"test", "dsd"};
  std::vector<std::string> name = {"name1", "name2"};

  this->dialogManager = DialogManager();

  this->testText.assign(Text.begin(), Text.end());

  this->nameText.assign(name.begin(), name.end());
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
            isDialog = true;
            displayDialog(this->nameText, this->testText);

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
    }
    // } else if (isDialog) {
    //   std::vector<std::string> dialogList = dialogManager.getDialog();
    //   showDialog(dialogList[0].c_str(), dialogList[1].c_str());
    // }
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
      dialogManager.clearDialog();

      break;
  }

  if (!dialogManager.check()) {
    isDialog = false;
    displayGame();
  } else {
    std::vector<std::string> dialogList = dialogManager.getDialog();
    showDialog(dialogList[0].c_str(), dialogList[1].c_str());
  }
  // if (isDialog) {
  //   std::vector<std::string> dialogList = dialogManager.getDialog();
  //   showDialog(dialogList[0].c_str(), dialogList[1].c_str());
  // }
}
void EventManager::displayDialog(std::vector<std::string> names,
                                 std::vector<std::string> texts) {
  dialogManager.handleDialog(names, texts);
  std::vector<std::string> dialog_list = dialogManager.getDialog();

  showDialog(dialog_list[0].c_str(), dialog_list[1].c_str());
}

void EventManager::displayDialog(std::string name, std::string text) {
  dialogManager.handleDialog(name, text);
  std::vector<std::string> dialog_list = dialogManager.getDialog();

  showDialog(dialog_list[0].c_str(), dialog_list[1].c_str());
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
  std::cout << mainActor.interact(curRoom.entityList) << std::endl;
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

void EventManager::roomChange(Rooms r) {
  curRoom = Room(r);
  currRoomName = r;
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

void EventManager::showDialog(const char* name, const char* text) {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(curItem + 1);
  gameView->drawItems(&inventory);
  gameView->drawRoom(&this->curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, curDir);
  gameView->roomToPosition();

  gameView->drawDialog(text, name);
  gameView->presentScreen();
}
