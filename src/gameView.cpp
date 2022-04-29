#include "gameView.h"

GameView::GameView(SDL_Renderer* renderer) {
  this->renderer = renderer;
  pauseMenu = PauseMenu(this->renderer);
}

/* Method will animate the movements of the two actor types */
void GameView::drawActor(Vec2d position, Vec2d size,
                         direction direction) {  // vec2D position
  sprite.storeImage("../resource/mainActorSprite.png", 4, 4);
  rect.x = position.x;
  rect.y = position.y;  // get x, y from position
  rect.w = size.x;
  rect.h = size.y;

  // use actor to find cur direction facing and coordinates
  switch (direction) {
    case direction::UP:
      sprite.selectSprite(0, 3);
      break;
    case direction::DOWN:
      sprite.selectSprite(0, 0);
      break;
    case direction::LEFT:
      sprite.selectSprite(0, 1);
      break;
    case direction::RIGHT:
      sprite.selectSprite(0, 2);
      break;
  }
  sprite.drawSprite(renderer, &rect);
}
// Given a sprite sheet reference, it will draw for us, we delegate which one
// to use We will animate in this class
// given delta time divide this by 2 to animate the movement (two frame
// changes within the delta time)

void GameView::drawRoom(Room* r, Rooms roomName) {
  this->currentR = r;
  // std::cout << this->currentRoom << "/n";

  SDL_Surface* roomImage;

  std::cout << " equal \n";
  switch (roomName) {
    case Rooms::bedroom:
      this->currentRoom = Rooms::bedroom;
      roomImage = IMG_Load("../resource/rooms/bedroom-pixel.png");
      break;

    case Rooms::bathroom:
      this->currentRoom = Rooms::bathroom;
      roomImage = IMG_Load("../resource/rooms/bathroom_pixel.png");
      break;
    case Rooms::kitchen:
      this->currentRoom = Rooms::kitchen;
      roomImage = IMG_Load("../resource/rooms/kitchen-pixel.png");
      break;
    case Rooms::foyer:
      std::cout << "foyer \n";
      this->currentRoom = Rooms::foyer;
      roomImage = IMG_Load("../resource/rooms/FFoyerRoom.png");
      break;
    default:
      break;
  }

  roomTexture = SDL_CreateTextureFromSurface(renderer, roomImage);

  SDL_RenderCopy(renderer, roomTexture, NULL, NULL);
  SDL_FreeSurface(roomImage);

  this->currentRoom = roomName;
}
void GameView::displayGame(Actor* actor) {
  clearScreen();
  std::cout << "to draw room\n";
  drawRoom(currentR, currentRoom);
  std::cout << "after draw room\n";
  drawActor(actor->position, actor->size, actor->getDirection());
}

void GameView::drawPauseMenu(void) {
  clearScreen();
  SDL_RenderCopy(renderer, pauseMenu.returnTexture(), NULL, NULL);
}
void GameView::clearScreen(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void GameView::presentScreen(void) { SDL_RenderPresent(renderer); }
