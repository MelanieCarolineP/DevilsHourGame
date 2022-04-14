#include "eventManager.h"

EventManager::EventManager() {}

/**
 * @brief Takes in the events from the SDL event queue and processes it within
 * the game
 *
 * @param event - the SDL event
 * @param deltaTime - the time change between events last event
 */

void EventManager::handle_event(SDL_Event event, float deltaTime, float time,
                                bool* running, SDL_Renderer* renderer) {
  if (event.type == SDL_QUIT) {
    exitEvent(event, time, running);
  } else if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_q:
        exitEvent(event, time, running);
        break;
      case SDLK_w:
        playerMovement(deltaTime, direction::UP, renderer);
        break;
      case SDLK_a:
        playerMovement(deltaTime, direction::LEFT, renderer);
        break;
      case SDLK_s:
        playerMovement(deltaTime, direction::DOWN, renderer);
        break;
      case SDLK_d:
        playerMovement(deltaTime, direction::RIGHT, renderer);
        break;
      case SDLK_e:
        playerInteraction(event, deltaTime);
        break;
      case SDLK_i:
        inventoryChange(event, time);
        break;
    }
  }
}
/* Moves and draws the main character on the screen */
void EventManager::playerMovement(float deltaTime, direction direction,
                                  SDL_Renderer* renderer) {
  mainActor.move(direction, deltaTime);
  gameView.drawActor(renderer, mainActor.position, mainActor.size, direction);
}

void EventManager::playerInteraction(SDL_Event event, float deltaTime) {
  // std::cout << "Not implemented";
}

void EventManager::pauseGame(SDL_Event event, float time) {
  // std::cout << "Not implemented";
}

void EventManager::roomChange(SDL_Event event, float time) {
  // std::cout << "Not implemented";
}

void EventManager::demonMovement(SDL_Event event, float deltaTime) {
  // std::cout << "Not implemented";
}
void EventManager::inventoryChange(SDL_Event event, float deltaTime) {
  // std::cout << "Not implemented";
}

void EventManager::exitEvent(SDL_Event event, float time, bool* running) {
  *running = false;
}
