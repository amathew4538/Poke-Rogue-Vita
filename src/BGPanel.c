#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "bgLocations.h"

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;

SDL_Rect bottomPanelSrcRect =
{
  0,
  0,
  340,
  48
};

SDL_Rect bottomPanelDstRect =
{
  0,
  SCREEN_HEIGHT - 112,
  SCREEN_WIDTH,
  112
};

SDL_Rect upperGameRect =
{
  0,
  0,
  SCREEN_WIDTH,
  SCREEN_HEIGHT - 112
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

  // Dialogue image
  SDL_Texture* dialogueBoxTexture = IMG_LoadTexture(gRenderer, DIALOGUE_BOX_PATH);
  SDL_Texture* plainsBGTexture = IMG_LoadTexture(gRenderer, PLAINS_BG_PATH);


  SDL_RenderCopy(gRenderer, plainsBGTexture, NULL, &upperGameRect);
  SDL_RenderCopy(gRenderer, dialogueBoxTexture, &bottomPanelSrcRect, &bottomPanelDstRect);

  SDL_RenderPresent(gRenderer);

  SDL_Delay(5000);

  if (dialogueBoxTexture) {
    SDL_DestroyTexture(dialogueBoxTexture);
  }
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gWindow = NULL;
  gRenderer = NULL;

  SDL_Quit();
  return 0;
}