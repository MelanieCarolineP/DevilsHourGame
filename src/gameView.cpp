#include "gameView.h"

GameView::GameView(SDL_Renderer* renderer) { this->renderer = renderer; }

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

  // draw UI
  SDL_RenderCopy(renderer, ivTx, NULL, &dstR);
  // SDL_RenderPresent(renderer);
}

/**
 * @brief Draw the room screen
 *
 * @param renderer
 * @param r : current room
 */
void GameView::drawRoom(Room r) {
  SDL_Surface* loadingSurf;
  switch (r.type) {
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
      // case Rooms::foyer:
      //   dir = "../resources/rooms/foyer-pixel.png";
      //   break;

    default:
      loadingSurf = IMG_Load("../resource/rooms/bedroom-pixel.png");
      break;
  }
  // SDL_Surface* loadingSurf = IMG_Load("../resource/rooms/bedroom-pixel.png");
  if (!loadingSurf) std::cout << "Fail to load room pic!" << std::endl;

  SDL_Texture* roomTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  SDL_FreeSurface(loadingSurf);

  // specify size & loc
  SDL_Rect dstR;
  dstR.x = 335;
  dstR.y = 15;
  dstR.w = 1024;
  dstR.h = 768;

  // draw UI
  SDL_RenderCopy(renderer, roomTx, NULL, &dstR);
  // SDL_RenderPresent(renderer);
}