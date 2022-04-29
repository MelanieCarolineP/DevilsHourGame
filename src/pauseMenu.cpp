#include "pauseMenu.h"

PauseMenu::PauseMenu(SDL_Renderer* renderer) {
  this->renderer = renderer;

  exitButton.x = 50;
  exitButton.y = 150;
  exitButton.w = 150;
  exitButton.h = 50;

  resumeButton.x = 50;
  resumeButton.y = 50;
  resumeButton.w = 150;
  resumeButton.h = 50;

  createTexture();
}
// PauseSelection PauseMenu::onButtonPress() {
//   if (x > 50 && x < 200) {
//     if (this->resumeButton.y <= y &&
//         y >= this->resumeButton.y + this->resumeButton.h) {
//       return PauseSelection::resume;
//     }
//     if (this->exitButton.y <= y &&
//         y >= this->exitButton.y + this->resumeButton.h) {
//       return PauseSelection::exit;
//     }
//   }
//   return PauseSelection::none;
// }
void PauseMenu::createTexture(void) {
  menuTexture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetRenderDrawColor(this->renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_SetRenderTarget(renderer, menuTexture);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderDrawColor(this->renderer, SILVER.r, SILVER.g, SILVER.b, 255);
  SDL_RenderFillRect(renderer, &this->resumeButton);
  SDL_RenderFillRect(renderer, &this->exitButton);
  SDL_SetRenderTarget(renderer, NULL);
}