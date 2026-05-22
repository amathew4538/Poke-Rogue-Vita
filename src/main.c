#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "bgPanel.h"
#include "constants.h"

SDL_Window    * window   = NULL;
SDL_Renderer  * renderer = NULL;

int main(int argc, char *argv[])
{
  // Initialize SDL
  if(SDL_Init( SDL_INIT_VIDEO ) < 0)
  {
    return -1;
  }

  // Initialize IMGs
  int flags = IMG_INIT_PNG;
  if ((IMG_Init(flags) & flags) != flags)
  {
    SDL_Quit();
    return -1;
  }

  // Initialize Window
  if ((window = SDL_CreateWindow("pokerogue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
    SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
  {
    IMG_Quit();
    SDL_Quit();
    return -1;
  }

  // Initialize Renderer
  if ((renderer = SDL_CreateRenderer( window, -1, 0)) == NULL)
  {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return -1;
  }

  drawTownBackground();

  SDL_Delay(5000);

  if(renderer) SDL_DestroyRenderer(renderer);
  if(window) SDL_DestroyWindow(window);

  window = NULL;
  renderer = NULL;

  SDL_Quit();
  return 0;
}