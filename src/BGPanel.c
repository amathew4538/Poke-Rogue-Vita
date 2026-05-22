#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "bgPanel.h"
#include "constants.h"

SDL_Rect bottomPanelSrcRect = { 0, 0, 340, 48 };
SDL_Rect bottomPanelDstRect = { 0, SCREEN_HEIGHT - 112, SCREEN_WIDTH, 112 };
SDL_Rect upperGameRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 112 };

void drawTownBackground()
{
  SDL_RenderClear(renderer);

  SDL_Texture* dialogueBoxTexture = IMG_LoadTexture(renderer, DIALOGUE_BOX_PATH);
  SDL_Texture* townBGTexture = IMG_LoadTexture(renderer, TOWN_BG_PATH);
  SDL_Texture* townATexture = IMG_LoadTexture(renderer, TOWN_A_PATH);
  SDL_Texture* townBTexture = IMG_LoadTexture(renderer, TOWN_B_PATH);

  SDL_RenderCopy(renderer, townBGTexture, NULL, &upperGameRect);
  SDL_RenderCopy(renderer, townATexture, NULL, &upperGameRect);
  SDL_RenderCopy(renderer, townBTexture, NULL, &upperGameRect);
  SDL_RenderCopy(renderer, dialogueBoxTexture, &bottomPanelSrcRect, &bottomPanelDstRect);

  SDL_RenderPresent(renderer);

  if (dialogueBoxTexture) SDL_DestroyTexture(dialogueBoxTexture);
  if (townBGTexture)      SDL_DestroyTexture(townBGTexture);
  if (townATexture)       SDL_DestroyTexture(townATexture);
  if (townBTexture)       SDL_DestroyTexture(townBTexture);
}