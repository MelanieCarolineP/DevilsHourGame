#include "gameView.h"

GameView::GameView() {}

/* Method will animate the movements of the two actor types */
void GameView::drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
                         direction direction) {  // vec2D position
  SpriteSheet man;
  man.storeImage("../resource/sprite_sheet_man.png", 4, 4);
  SDL_Rect dstrect;
  rect.x = position.x;
  rect.y = position.y;  // get x, y from position
  rect.w = 230;
  rect.h = 240;

  // use actor to find cur direction facing and coordinates
  switch (direction) {
    case direction::UP:
      man.selectSprite(0, 3);
      break;
    case direction::DOWN:
      man.selectSprite(0, 0);
      break;
    case direction::LEFT:
      man.selectSprite(0, 1);
      break;
    case direction::RIGHT:
      man.selectSprite(0, 2);
      break;
  }
  man.drawSprite(renderer, &rect);
}
// Given a sprite sheet reference, it will draw for us, we delegate which one
// to use We will animate in this class
// given delta time divide this by 2 to animate the movement (two frame
// changes within the delta time)