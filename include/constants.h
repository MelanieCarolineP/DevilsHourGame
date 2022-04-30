#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <SDL.h>

enum class Rooms { bedroom, bathroom, kitchen, foyer };
enum class PauseSelection { none, resume, exit };
static SDL_Color WHITE = {255, 255, 255, 255};
static SDL_Color SILVER = {192, 192, 192};
static SDL_Color BLACK = {0, 0, 0};

#endif /* _CONSTANTS_H_ */