
#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "logic.h"
#include "mode.h"

void guessTheWord(TTF_Font *&font, SDL_Renderer *&renderer, bool &quit)
{
  // This function will call all other functions related to this module. The game loop that runs the module “Guess The Word” is defined here.

  SDL_RenderClear(renderer);
  texture_intialization(font, renderer);
  surface = IMG_Load("Alphabet_image/bg1.jpg");
  SDL_Texture *bg = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, bg, NULL, NULL);
  SDL_RenderPresent(renderer);

  while (game) // running game loop for guess the word
  {
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT)
    {
      quit = true;
      game = 0;
      return;
    }

    if (game == 0 || quit == true)
      return;

  hell: // if the player wants to go to the menu option then the program will come here
    if (game == 0 || quit == true)
      return;

    main_render(renderer);               // load background
    if (mode(renderer, font, quit) == 1) // Normal mode
    {
      SDL_RenderClear(renderer);
      main_render(renderer);
      logic_for_adult(renderer, font, quit);
      if (next_step(quit) == 2) // clicks menu
      {
        goto hell;
      }

      while (next_step(quit) == 1) // chooses next round
      {
        main_render(renderer);                 // load background
        logic_for_adult(renderer, font, quit); // normal mode
        SDL_RenderClear(renderer);
      }
    }

    else if (mode(renderer, font, quit) == 0) // kids mode
    {
      SDL_RenderClear(renderer);
      main_render(renderer);
      logic_for_kids(renderer, font, quit);
      if (next_step(quit) == 2) // clicks menu
      {
        goto hell;
      }
      while (next_step(quit) == 1) // chooses next round
      {
        main_render(renderer);
        logic_for_kids(renderer, font, quit);
        SDL_RenderClear(renderer);
      }
    }

    else if (mode(renderer, font, quit) == -1) // quit the game
    {
      SDL_RenderClear(renderer);
      return;
    }
  }
}