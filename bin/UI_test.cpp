// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <iostream>

#include "eventManager.h"
#include "room.h"

// Screen dimension constants
// static const int SCREEN_WIDTH = 1024;
// static const int SCREEN_HEIGHT = 768;

// Room enummerations
enum rooms { Front_Foyer, Bedroom, Bathroom, Kitchen, Hallway };

void csci437_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void csci437_img_error(const std::string& msg) {
  std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
  exit(0);
}
SDL_Surface* load_bitmap(SDL_Surface* input) {
  // Load bitmap
  if (input == NULL) csci437_img_error("Could not image!");
  return input;
}

SDL_Texture* convert_image_to_texture(SDL_Renderer* renderer,
                                      SDL_Surface* image) {
  // convert to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) csci437_error("Could not create texture from surface!");

  // delete image
  SDL_FreeSurface(image);
  image = NULL;

  return texture;
}
int main(int argc, char** argv) {
  /*** Initialization ***/

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) csci437_error("SDL could not initialize!");

  // Create window
  SDL_Window* window =
      SDL_CreateWindow("Devil's Hour", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1500, 800, SDL_WINDOW_SHOWN);
  if (window == NULL) csci437_error("Window could not be created!");

  // Init Bitmap loading
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    csci437_img_error("SDL could not initialize bitmap loaders!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) csci437_error("Unable to create renderer!");

  // SDL_Surface* image =
  //     load_bitmap(IMG_Load("../resource/rooms/bedroom-pixel.png"));

  // // convert to texture
  // SDL_Texture* roomTx = SDL_CreateTextureFromSurface(renderer, image);
  // if (roomTx == NULL) csci437_error("Could not create texture from
  // surface!");

  // // delete image
  // SDL_FreeSurface(image);
  // image = NULL;

  // bool red = true, green = true, blue = true;
  // float angle = 0;

  // SDL_Rect dst = {410, 10, 1024, 768};

  /*** Main Loop ***/
  bool running = true;
  bool start = false;

  EventManager eventManager;
  SDL_Event e;
  rooms current_room;
  current_room = Front_Foyer;
  float deltaTime = 0.0f;
  uint32_t startTime, endTime;

  GameView gameView;

  Room room(Rooms::bathroom);

  // While application is running
  while (running) {
    // loop start time
    startTime = SDL_GetTicks();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      gameView.drawUI(renderer);
      gameView.drawInventory(renderer, eventManager.curItem + 1);
      gameView.drawRoom(renderer, room);
      // gameView.drawRoom(renderer, room);

      eventManager.handle_event(e, deltaTime, startTime, &running, renderer);

      // switch (current_room) {
      //   case Front_Foyer:
      //     image =
      //     load_bitmap(IMG_Load("../resource/rooms/bedroom-pixel.png"));
      //     roomTx = convert_image_to_texture(renderer, image);
      //     break;
      //   case Bedroom:
      //     image = load_bitmap(IMG_Load("../resource/bathroom.png"));
      //     roomTx = convert_image_to_texture(renderer, image);
      //     break;
      // }

      //// render
      // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      // SDL_RenderClear(renderer);
      //// SDL_SetTextureColorMod(texture, red * 255, green * 255, blue *
      // 255);
      // SDL_RenderCopy(renderer, roomTx, NULL, &dst);
      SDL_RenderPresent(renderer);

      endTime = SDL_GetTicks();
      deltaTime = (endTime - startTime) / 1.0f;
    }
  }
  // Gets end time of the loop
  Uint32 end_time = SDL_GetTicks();

  /*** Clean Up ***/

  // Destroy texture
  // SDL_DestroyTexture(roomTx);

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();

  // Done.
  return 0;
}
