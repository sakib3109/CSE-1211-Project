
#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "chooseOptions.h"

using namespace std;

void loadFrame(SDL_Renderer *&, TTF_Font *&, SDL_Texture *&, SDL_Texture *[], SDL_Rect[], int, bool);

int searchTheWord(SDL_Renderer *&rend, TTF_Font *&font, bool &quit)
{
    // here the player will choose whether he will play wordFind or positionFind

    // This function will call all other functions related to this module. The game loop that runs the module “Search The Word” is defined here.

    SDL_Surface *surface = IMG_Load("Alphabet_image/bg1.jpg");

    SDL_RenderClear(rend);
    SDL_Texture *bg = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(rend, bg, NULL, NULL);

    SDL_Texture *text[N];
    SDL_Rect dest[N];

    int i, j, xPos = 200, yPos = 175;

    for (i = 0; i < 5; i++)
    {
        dest[i].w = 800;
        dest[i].h = 60;
        dest[i].x = xPos;
        dest[i].y = yPos;

        yPos += 80;
    }

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < 5; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    surface = TTF_RenderText_Solid(font, "WELCOME TO SEARCH THE WORD", {255, 0, 255});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "In this game you have two options", {255, 0, 255});
    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "1. Among multiple words find which word is present in puzzle", {255, 0, 255});
    text[2] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "2. Find the position of a particular word in puzzle", {255, 0, 255});
    text[3] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "Click mouse to choose any one of them", {255, 0, 255});
    text[4] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    for (i = 0; i < 5; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    SDL_RenderPresent(rend);

    bool close = false;
    int option;
    bool flag1 = false;
    bool flag2 = false;

    // taking input from the user in the event loop
    while (!close)
    {
        int x, y;
        SDL_Event e;
        SDL_PollEvent(&e);
        int button = SDL_GetMouseState(&x, &y);

        if (x >= dest[2].x && x <= (dest[2].x + dest[2].w) && y >= dest[2].y && y <= (dest[2].y + dest[2].h))
        {
            if (!flag1)
            {
                loadFrame(rend, font, bg, text, dest, 2, flag1);
                flag1 = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                option = 1;
                close = true;
            }
        }
        else
        {
            if (flag1)
            {
                loadFrame(rend, font, bg, text, dest, 2, flag1);
                flag1 = false;
            }
        }

        if (x >= dest[3].x && x <= (dest[3].x + dest[3].w) && y >= dest[3].y && y <= (dest[3].y + dest[3].h))
        {
            if (!flag2)
            {
                loadFrame(rend, font, bg, text, dest, 3, flag2);
                flag2 = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                option = 2;
                close = true;
            }
        }
        else
        {
            if (flag2)
            {
                loadFrame(rend, font, bg, text, dest, 3, flag2);
                flag2 = false;
            }
        }

        if (e.type == SDL_QUIT)
        {
            close = true;
            quit = true;
            return 10;
        }
    }

    SDL_RenderClear(rend);

    for (i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(text[i]);
    }

    int size = 10;
    return chooseOptions(size, option, rend, font, bg, quit);
    SDL_DestroyTexture(bg);
}

void loadFrame(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *text[], SDL_Rect dest[], int idx, bool flag)
{
    // in case of any change in the frame this function will load the window again

    int i;
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < idx; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }
    for (i = idx + 1; i < 5; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }
    if (!flag)
    {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
    }

    SDL_RenderFillRect(rend, &dest[idx]);

    for (i = 0; i < 5; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    SDL_RenderPresent(rend);
}
