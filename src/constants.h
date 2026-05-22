#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

extern SDL_Window    * window;
extern SDL_Renderer  * renderer;

#endif