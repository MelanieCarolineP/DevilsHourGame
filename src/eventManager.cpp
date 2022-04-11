#include "eventManager.h"


/**
 * @brief Takes in the events from the SDL event queue and processes it within the game
 * 
 * @param event - the SDL event
 * @param deltaTime - the time change between events last event
 */

void EventManager::handle_event (SDL_Event * event, float deltaTime, float time, bool *running ){

    if (e.type == SDL_QUIT) {
        exitEvent(event, time, running);
    }
    else if (e.type == SDL_KEYDOWN){

        switch(event.key.keysym.sym){
            case SDLK_q:
                exitEvent(event,time, running);
                break;
            case SDLK_w:
                playerMovement(event,deltaTime, 0);
                break;
            case SDLK_a:
                playerMovement(event,deltaTime, 2);
                break;
           case SDLK_s:
                playerMovement(event,deltaTime, 1);
                break;
            case SDLK_d:
                playerMovement(event,deltaTime, 3);
                break;
            case SDLK_e:
                playerInteractoin(event,deltaTime);
                break;
            case SDLK_i:
                inventoryChange(event,time);
                break;
        }
    }
}

void EventManager::playerMovement (SDL_Event * event, float deltaTime, int direction){
  std::cout << "Not implemented";
}

void EventManager::playerInteraction( SDL_Event * event, float deltaTime){
    std::cout << "Not implemented";
}

void EventManager::pauseGame (SDL_Event * event , float time){
    std::cout << "Not implemented";
}

void EventManager::roomChange (SDL_Event * event, float time){
    std::cout << "Not implemented";
}

void EventManager::demonMovement (SDL_Event * event , float deltaTime){
    std::cout << "Not implemented";
}
void EventManager::inventoryChange ( SDL_Event* event , float deltaTime){
    std::cout << "Not implemented";
}


void EventManager:: exitEvent(SDL_Event* event, float time, bool *running){
    *running  = false; 
}



