#include "gameview.h"

GameView::GameView() {}

/* Method will animate the movements of the two actor types */
void GameView::drawActor(SDL_Renderer *renderer, Vec2d position, Vec2d size,
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