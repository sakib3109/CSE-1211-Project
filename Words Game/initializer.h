#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "startGame.h"

void initializeSDL()
{
    // this function will initialize sdl window, renderer, ttf font and background music

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP);
    TTF_Init();
    Mix_OpenAudio(1500, MIX_DEFAULT_FORMAT, 2, 512);

    SDL_Window *window = SDL_CreateWindow("WORDS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0); // initializing window

    if (!window)
    {
        printf("Window\n");
        SDL_Quit();
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        return;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, render_flags); // initialing rendered

    if (!rend)
    {
        printf("Renderer\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        return;
    }

    TTF_Font *font = TTF_OpenFont("static/Catamaran-ExtraBold.ttf", 16); // loading ttf font

    if (font == NULL)
    {
        printf("Font\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        SDL_Quit();
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        return;
    }

    Mix_Music *music = Mix_LoadMUS("music.mp3"); // loading background music

    if (music == NULL)
    {
        printf("music\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        return;
    }

    Mix_PlayMusic(music, -1);

    gameInit(window, rend, font); // initializing game loop

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    TTF_CloseFont(font);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
