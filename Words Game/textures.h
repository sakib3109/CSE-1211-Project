#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "constants.h"
using namespace std;

bool texture_intialization(TTF_Font *&font, SDL_Renderer *&renderer)
{
    // this function will create the textures that are declared globally
    if (!IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG | IMG_INIT_WEBP))
    {
        printf("ERROR INITIALIZING IMAGE\n");
        SDL_Quit();
        IMG_Quit();
        return 0;
    }

    surface = IMG_Load("Alphabet_image/background.png");

    surface = TTF_RenderText_Solid(font, "NEXT ROUND", {0, 0, 0});

    Next_round = SDL_CreateTextureFromSurface(renderer, surface);

    next_round.w = 300;
    next_round.h = 100;
    next_round.x = 850;
    next_round.y = 550;

    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, "MENU", {0, 0, 0});
    menuee = SDL_CreateTextureFromSurface(renderer, surface);

    menu.x = 80;
    menu.y = 550;
    menu.h = 100;
    menu.w = 200;

    SDL_FreeSurface(surface);

    ans.x = 920;
    ans.y = 200;
    ans.h = 50;
    ans.w = 200;

    surface = TTF_RenderText_Solid(font, "CORRECT", {0, 255, 0});
    correct = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "INCORRECT", {255, 0, 0});
    incorrect = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    hint.x = 50;
    hint.y = 200;
    hint.w = 500;
    hint.h = 50;

    return 1;
}

void main_render(SDL_Renderer *&renderer)
{
    // this function will load the background
    SDL_RenderClear(renderer);
    surface = IMG_Load("Alphabet_image/background.png");
    back = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, back, NULL, NULL);
    SDL_RenderPresent(renderer);
}