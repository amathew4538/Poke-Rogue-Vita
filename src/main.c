#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Screen dimension constants for the Vita
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

// Global declarations
SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;
SDL_Texture   * gBgTexture = NULL;

int main(int argc, char *argv[])
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      return -1;
  }

  if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
      SDL_Quit();
      return -1;
  }

  gWindow = SDL_CreateWindow("PokéRogue Vita",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      0);
  if( gWindow == NULL ) {
      IMG_Quit();
      SDL_Quit();
      return -1;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if( gRenderer == NULL ) {
      SDL_DestroyWindow(gWindow);
      IMG_Quit();
      SDL_Quit();
      return -1;
  }

  gBgTexture = IMG_LoadTexture(gRenderer, "ux0:data/pokerogue/images/ui/bg.png");
  if( gBgTexture == NULL ) {
    // If the image fails to load
  }

  // GAME / RENDERING LOOP

  SDL_Delay(4000);

  if (gBgTexture) {
      SDL_DestroyTexture(gBgTexture);
  }
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  
  IMG_Quit();
  SDL_Quit();
  
  return 0;
}