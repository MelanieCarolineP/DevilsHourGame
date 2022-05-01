#include "gameView.h"

GameView::GameView(SDL_Renderer* renderer) {
  this->renderer = renderer;
  this->pauseMenu = PauseMenu(renderer);

  this->speechbox = SpeechBox(renderer);
  this->speechbox.initFonts("../resource/fonts/jmh_cthulhumbus.ttf");
  this->speechbox.initGlyph();

  this->roomTexture =
      SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
  this->roomDest.x = 335;
  this->roomDest.y = 15;
  this->roomDest.w = 1024;
  this->roomDest.h = 768;

  this->clockFont = TTF_OpenFont("../resource/fonts/digital-7.ttf", 24);
  if (!clockFont) std::cout << "Font not loaded" << std::endl;
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
  SDL_SetRenderTarget(renderer, roomTexture);
  sprite.drawSprite(renderer, &rect);
  SDL_SetRenderTarget(renderer, NULL);
}
// Given a sprite sheet reference, it will draw for us, we delegate which one
// to use We will animate in this class
// given delta time divide this by 2 to animate the movement (two frame
// changes within the delta time)

/**
 * @brief Draw the UI of the game
 *
 * @param renderer
 */
void GameView::drawUI() {
  // load image
  SDL_Surface* loadingSurf = IMG_Load("../resource/ui/ui_background.png");
  SDL_Texture* uiTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  SDL_FreeSurface(loadingSurf);

  // specify size & loc
  SDL_Rect dstR;
  dstR.x = 300;
  dstR.y = 0;
  dstR.w = 1100;
  dstR.h = 800;

  // draw UI
  SDL_RenderCopy(renderer, uiTx, NULL, &dstR);
  // SDL_RenderPresent(renderer);
}

/**
 * @brief Draw the inventory
 *
 * @param renderer
 * @param k
 */
void GameView::drawInventory(int k) {
  std::string s =
      "../resource/ui/inventory/inventory_" + std::to_string(k) + ".png";
  SDL_Surface* loadingSurf = IMG_Load(s.c_str());
  SDL_Texture* ivTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  SDL_FreeSurface(loadingSurf);

  // specify size & loc
  SDL_Rect dstR;
  dstR.x = 0;
  dstR.y = 200;
  dstR.w = 300;
  dstR.h = 600;

  SDL_RenderCopy(renderer, ivTx, NULL, &dstR);
  // SDL_RenderPresent(renderer);
}

/**
 * @brief Draw the room screen
 *
 * @param renderer
 * @param r : current room
 */
void GameView::drawRoom(Room* r) {
  SDL_Surface* loadingSurf;
  switch (r->type) {
    case Rooms::bedroom:
      loadingSurf = IMG_Load("../resource/rooms/bedroom-pixel.png");
      // std::cout << "Loaded bedroom image" << std::endl;
      break;
    case Rooms::kitchen:
      loadingSurf = IMG_Load("../resource/rooms/kitchen-pixel.png");
      // std::cout << "Loaded kitchen image" << std::endl;
      break;
    case Rooms::bathroom:
      loadingSurf = IMG_Load("../resource/rooms/bathroom-pixel.png");
      // std::cout << "Loaded bathroom image" << std::endl;
      break;
    case Rooms::foyer:
      loadingSurf = IMG_Load("../resource/rooms/foyer-pixel.png");
      // std::cout << "Loaded bathroom image" << std::endl;
      break;

    default:
      loadingSurf = IMG_Load("../resource/rooms/bedroom-pixel.png");
      break;
  }
  if (!loadingSurf) std::cout << "Fail to load room pic!" << std::endl;

  SDL_SetRenderTarget(renderer, this->roomTexture);
  SDL_Texture* roomTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  SDL_FreeSurface(loadingSurf);

  // specify size & loc
  // SDL_Rect dstR;
  // dstR.x = 335;
  // dstR.y = 15;
  // dstR.w = 1024;
  // dstR.h = 768;

  // draw UI
  SDL_RenderCopy(renderer, roomTx, NULL, NULL);
  SDL_SetRenderTarget(renderer, NULL);
  // SDL_RenderPresent(renderer);
}

void GameView::roomToPosition(void) {
  SDL_RenderCopy(renderer, this->roomTexture, NULL, &this->roomDest);
}
void GameView::displayGame(Actor* actor) {
  clearScreen();

  drawActor(actor->position, actor->size, actor->getDirection());
}

void GameView::drawPauseMenu(void) {
  clearScreen();
  SDL_RenderCopy(renderer, pauseMenu.returnTexture(), NULL, NULL);
}

void GameView::drawDialog(const char* text) {
  SDL_Texture* dialogView = SDL_CreateTexture(
      this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      dialogBoxSize.x + 5, dialogBoxSize.y + 5);

  // draw the box and text in a seperate texture;
  SDL_SetRenderTarget(renderer, dialogView);
  SDL_SetTextureBlendMode(dialogView, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
  this->speechbox.drawDialogBox();
  this->speechbox.drawText(text, 15, 15, dialogBoxSize.x - 15);
  SDL_SetRenderTarget(renderer, NULL);

  SDL_RenderCopy(renderer, dialogView, NULL, &speechbox.dialogBoxRect);
}

void GameView::clearScreen(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void GameView::presentScreen(void) { SDL_RenderPresent(renderer); }

void GameView::displayTime(std::string time) {
  // std::cout << time << std::endl;
  SDL_Color red = {255, 0, 0};
  SDL_Surface* loadingSurf = TTF_RenderText_Solid(clockFont, time.c_str(), red);
  if (!loadingSurf) std::cout << "Font surface not initialized" << std::endl;
  SDL_Texture* timeTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  if (!timeTx) std::cout << "Time texture not initialized" << std::endl;
  SDL_FreeSurface(loadingSurf);
  SDL_Rect dstRect = {30, 40, 240, 120};
  SDL_RenderCopy(renderer, timeTx, NULL, &dstRect);
  // presentScreen();
}

/**
 * @brief Helper function. Draw entities on the screen.
 *
 * @param r
 */
void GameView::drawEntities(Room* r) {
  // for each entity in the entity list
  for (int i = 0; i < r->entityList.size(); ++i) {
    Entity* e = &(r->entityList[i]);
    SDL_Rect rect;
    rect.x = 335 + int(e->position.x / r->size.x * 1024);
    rect.y = 15 + int(e->position.y / r->size.y * 768);
    rect.w = int(e->size.x / r->size.x * 1024);
    rect.h = int(e->size.y / r->size.y * 768);
    if (e->isEntity)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 130);
    else
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 130);
    SDL_RenderFillRect(renderer, &rect);
  }
}
