#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;

SDL_Rect srcrect =
{
  0,
  0,
  340,
  48
};

SDL_Rect dstrect =
{
  0,
  SCREEN_HEIGHT - 112,
  SCREEN_WIDTH,
  112
};

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
  if ((gWindow = SDL_CreateWindow("pokerogue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
    SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
  {
    IMG_Quit();
    SDL_Quit();
    return -1;
  }

  // Initialize Renderer
  if ((gRenderer = SDL_CreateRenderer( gWindow, -1, 0)) == NULL)
  {
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    return -1;
  }

  // Blue BKG
  SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
  SDL_RenderClear(gRenderer);

  // BG image
  SDL_Texture* bgTexture = IMG_LoadTexture(gRenderer, "app0:/assets/images/ui/bg.png");
  if (bgTexture != NULL) {
    SDL_RenderCopy(gRenderer, bgTexture, &srcrect, &dstrect);
  } else {
    // If the image fails to load, the screen will just stay blue.
  }

  SDL_RenderPresent(gRenderer);

  SDL_Delay(5000);

  if (bgTexture) {
    SDL_DestroyTexture(bgTexture);
  }
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gWindow = NULL;
  gRenderer = NULL;

  SDL_Quit();
  return 0;
}