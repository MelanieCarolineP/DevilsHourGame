#include "gameview.h"

GameView::GameView() {
  // man.storeImage("../resource/sprite_sheet_man.png", 4, 4);
}

/* Method will animate the movements of the two actor types */
void GameView::drawActor(SDL_Renderer *renderer, float x, float y,
                         direction dir) {  // vec2D position
  man.storeImage("../resource/sprite_sheet_man.png", 4, 4);
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;  // get x, y from position
  dstrect.w = 150;
  dstrect.h = 150;

  // use actor to find cur direction facing and coordinates
  switch (dir) {
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
  man.drawSprite(renderer, &dstrect);
  // man.clearSprite();
}