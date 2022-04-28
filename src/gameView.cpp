#include "gameView.h"

GameView::GameView() {}

/* Method will animate the movements of the two actor types */
void GameView::drawActor(SDL_Renderer* renderer, Vec2d position, Vec2d size,
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

void GameView::drawUI(SDL_Renderer* renderer) {
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
}

void GameView::drawInventory(SDL_Renderer* renderer, int k) {
  SDL_Surface* loadingSurf = IMG_Load("../resource/ui/inventory/inventory_" +
                                      std::to_string(k).c_str() + ".png");
  SDL_Texture* ivTx = SDL_CreateTextureFromSurface(renderer, loadingSurf);
  SDL_FreeSurface(loadingSurf);

  // specify size & loc
  SDL_Rect dstR;
  dstR.x = 0;
  dstR.y = 0;
  dstR.w = 400;
  dstR.h = 800;

  // draw UI
  SDL_RenderCopy(renderer, ivTx, NULL, &dstR);
}