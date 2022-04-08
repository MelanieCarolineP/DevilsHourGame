#include "spritesheet.h"

/* May be used for a single image 1x1 sprite sheets or for animation 4x4
   row 0: facing towards
   row 1: facing left
   row 2: facing right
   row 3: facing away

*/

/* constructor */
SpriteSheet::SpriteSheet(char const *image_path, int row, int col) {
  // surface holding image
  this->spriteSheetImage = load_bitmap(
      IMG_Load("../resource/sprite_sheet_man.png"));  // Hardcoded for debugging
                                                      // // should be image_path
  /* surface-> sets size dimensions of a frame */
  frame_rect.h = spriteSheetImage->h / row;
  frame_rect.w = spriteSheetImage->w / col;
}

/* Destructor to avoid memory leak*/
SpriteSheet::~SpriteSheet() { SDL_FreeSurface(spriteSheetImage); }

/* given the frame's position (4x4) on the sprite sheet, select the sprite*/
void SpriteSheet::selectSprite(int row, int col) {
  // calculate the coordinate of the top left of selected frame
  frame_rect.x = row * spriteSheetImage.w;
  frame_rect.h = col * spriteSheetImage.h;
}
/* draws a sprite on the window given a position */
void SpriteSheet::drawSprite(SDL_Surface *gameSurface, SDL_Rect *position) {
  // fast surface copy to a dest surface
  SDL_BlitSurface(spriteSheetImage, &frame_rect, gameSurface, position);
}
