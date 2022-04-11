#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SDL.h>

class SpriteSheet {
 public:
  /* constructor is given an image and how many rows and columns it has */
  SpriteSheet(char const *image_path, int row, int col);
  ~SpriteSheet();

  void selectSprite();
  void drawSprite(SDL_Surface *gameSurface, SDL_Rect *position);

 private:
  /* will the partitions within the sprite image */
  SDL_Rect frame_rect;
  /* this surface holds raw pixel data of the entire sprite sheet used */
  SDL_Surface *spriteSheetImage;
}

#endif