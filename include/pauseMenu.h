#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "constants.h"
#include "eventManager.h"
#include "vec2d.h"

class PauseMenu {
 public:
  PauseMenu(SDL_Renderer* renderer);
  // PauseSelection onButtonPress(float x, float y);
  SDL_Texture* returnTexture(void) { return this->menuTexture; }

 private:
  EventManager* manager;
  SDL_Texture* menuTexture;
  SDL_Rect resumeButton;
  SDL_Rect exitButton;
  SDL_Renderer* renderer;

  void createTexture(void);
};

#endif