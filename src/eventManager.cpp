#include "eventManager.h"

EventManager::EventManager(GameView* gameView, AudioView* audioView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  this->audioView = audioView;

  std::vector<std::string> Text = {"test", "dsd"};
  std::vector<std::string> name = {"name1", "name2"};

  this->dialogManager = DialogManager();

  this->testText.assign(Text.begin(), Text.end());

  this->nameText.assign(name.begin(), name.end());
}

EventManager::EventManager(GameView* gameView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  this->audioView = NULL;

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
    if (!isDialog && !isPaused) {
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
          case SDLK_p:
            roomChange(Rooms::hallway);
            break;
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
          case SDLK_1:
            clock.deductTime();
            break;

          case SDLK_ESCAPE:
            pauseGame(time);
            break;
        }

        if (!isPaused && !isDialog && gameStarted) {
          displayGame();
        }

      } else if (isPaused) {
        handlePausedEvent(event, deltaTime, time, running, renderer);
      } else if (isDialog) {
        handleDialogEvent(event, deltaTime, time, running, renderer);
      }
    } else if (isPaused == false && isDialog == false && gameStarted) {
      displayGame();
    }
    // } else if (isDialog) {
    //   std::vector<std::string> dialogList = dialogManager.getDialog();
    //   showDialog(dialogList[0].c_str(), dialogList[1].c_str());
    // }

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
    case SDLK_SPACE:
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
  mainActor.collisionDetection(direction, curRoom.entityList);
  curDir = direction;
}

void EventManager::playerInteraction() {
  // interact returns entity only if character is colliding with an object
  // if (mainActor.collision(curRoom.entityList)) mainActor.interact();
  // otherwise do nothing

  // Get current info
  std::string object = mainActor.interact(curRoom.entityList);
  std::cout << "object: " << object << std::endl;
  std::string item(inventory.getSelectedItem());
  std::cout << "item: " << item << std::endl;
  std::cout << "current state: " << stateMonitor.currentState << std::endl;

  // retrieve dialog
  int id = curDialog.triggerDialog(mainActor.position, object, item,
                                   stateMonitor.currentState);
  std::cout << "id: " << id << std::endl;

  if (id < 0) {
    if (object.size() > 0 && item.size() > 0) {
      isDialog = true;
      std::vector<std::string> temp_name = {"Me"};
      std::vector<std::string> temp_dialog = {"I can't use it here."};
      displayDialog(temp_name, temp_dialog);
    }
    return;
  }

  dialog* d = &(curDialog.dialogList[id]);

  // play sound
  audioView->playSound("interact");

  isDialog = true;

  // Inventory Update and trigger dialog
  if (item != "hands") inventory.removeItem();
  if (d->pickItem.size() > 0) {
    if (!(inventory.itemHasBeenUsed(d->pickItem) ||
          inventory.itemInInventory(
              d->pickItem))) {  // If you successfully pick up an
                                // item, play the normal dialog
      displayDialog(d->speakers, d->texts);
      inventory.addItem(d->pickItem);
    } else {  // If you already picked up the item, play default dialog
      std::vector<std::string> temp_name = {"Me"};
      std::vector<std::string> temp_dialog = {
          "I don't think I can find anything else here."};
      displayDialog(temp_name, temp_dialog);
    }
  } else {
    displayDialog(d->speakers, d->texts);
  }

  // State transision
  int switchToRoom = 0;
  if (d->transitToState.size() > 0) {
    switchToRoom = stateMonitor.update(d->transitToState);
  }

  // std::cout << "transit to state: " << d->transitToState << std::endl;

  // handle doors

  if (switchToRoom == 1) {
    roomChange(Rooms::bedroom);
  } else if (switchToRoom == 2) {
    audioView->playSound("door");
    roomChange(Rooms::kitchen);
  } else if (switchToRoom == 3) {
    audioView->playSound("door");
    roomChange(Rooms::bathroom);
  } else if (switchToRoom == 4) {
    audioView->playSound("door");
    roomChange(Rooms::foyer);
  } else if (switchToRoom == 5) {
    inventory
        .resetInventory();  // Resets the inventory when you enter the hallway
    audioView->playSound("door");
    roomChange(Rooms::hallway);
  } else if (switchToRoom == 6) {
    clock.deductTime();
  } else if (switchToRoom == 7) {
    gameStarted = false;
    this->winScreen();
  }
}

void EventManager::pauseGame(float time) {
  isPaused = true;
  gameView->drawPauseMenu();
  gameView->presentScreen();
}

void EventManager::startScreen(void) {
  audioView->playMusic("main");
  gameView->drawStartScreen();
  gameView->presentScreen();
}

void EventManager::loseScreen(void) {
  gameView->drawLosingScreen();
  gameView->presentScreen();
}

void EventManager::winScreen(void) {
  audioView->playMusic("win");
  gameView->drawWinningScreen();
  gameView->presentScreen();
}

void EventManager::startGame(void) {
  clock.start();
  audioView->playMusic("main");
  inventory.resetInventory();
  roomChange(Rooms::bedroom);
  // startScreen();
}

void EventManager::roomChange(Rooms r) {
  curRoom = Room(r);
  // std::cout << "Successfully switched room" << std::endl;
  currRoomName = r;
  curDialog = Dialog(r);
  // std::cout << "Successfully switched dialog" << std::endl;
  // gameView->drawRoom(&curRoom);
  mainActor.position.x = curRoom.bornX;
  mainActor.position.y = curRoom.bornY;
  mainActor.setBoundary(curRoom.boundX, curRoom.boundY, curRoom.boundW,
                        curRoom.boundH);
  // std::cout << "Successfully set boundary" << std::endl;

  // Since the hallway has multiple doors, we need to account for which door the
  // player just left
  if (stateMonitor.currentState == "h1") {  // Bedroom door
    mainActor.position.x = 154;
    mainActor.position.y = 616;
  } else if (stateMonitor.currentState == "h2") {  // Kitchen door
    mainActor.position.x = 439.5;
    mainActor.position.y = 296.5;
  } else if (stateMonitor.currentState == "h3") {  // Bathroom door
    mainActor.position.x = 812;
    mainActor.position.y = 175;
  }

  // DEBUG:
  std::string s;
  switch (r) {
    case Rooms::kitchen:
      s = "k1";
      break;
    case Rooms::bathroom:
      s = "b1";
      break;
    case Rooms::bedroom:
      s = "e1";
      break;

    default:
      break;
  }
  isDialog = true;
  displayDialog(curDialog.dialogList[0].speakers,
                curDialog.dialogList[0].texts);
  if (s.size() > 0) stateMonitor.update(s);
}
void EventManager::returnToGame(void) {
  isPaused = false;
  std::cout << "resume game" << std::endl;

  displayGame();
}

void EventManager::demonMovement(SDL_Event* event, float deltaTime) {
  // std::cout << "Not implemented";
}
void EventManager::inventoryChange() { inventory.changeSelectedItem(); }

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
