#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>


class EventMangager {


public:
    EventMangager();
    void handle_event (SDL_Event * event, float deltaTime, float time, bool *running);
    void playerMovement (SDL_Event * event, float deltaTime, int direction);
    void playerInteraction( SDL_Event * event, float delaTime);
    void pauseGame (SDL_Event * event , float time);
    void roomChange (SDL_Event * event, float time);
    void demonMovement (SDL_Event * event , float deltaTime);
    void inventoryChange ( SDL_Event* event , float deltaTime);
    

    void exitEvent(SDL_Event* event, float time, bool *running);
};

#endif




