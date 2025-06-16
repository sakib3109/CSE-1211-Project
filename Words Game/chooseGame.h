#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "closeGame.h"
#include "searchWord.h"
#include "guessTheWord.h"
void newFrame(SDL_Renderer *&, TTF_Font *&, SDL_Texture *&, SDL_Texture *[], SDL_Rect[], int);

void chooseGame(SDL_Window *&window, SDL_Renderer *&rend, TTF_Font *&font)
{
    // This function will bring the page from where the player will choose whether he wants to play “Guess the word” or “Search the word”. According to the player’s choice the related functions will be called.

    SDL_Surface *surface = IMG_Load("Alphabet_image/bg1.jpg");
    SDL_Texture *bg = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_Texture *text[4];
    SDL_Rect dest[4];

    int i, j, xPos = 375, yPos = 205;

    for (i = 0; i < 4; i++)
    {
        dest[i].w = 450;
        dest[i].h = 60;
        dest[i].x = xPos;
        dest[i].y = yPos;

        yPos += 80;
    }

    surface = TTF_RenderText_Solid(font, "WELCOME TO WORD GAME", {255, 0, 0});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "Choose one game", {255, 0,0});
    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "1. Guess the word", {255, 0,0 });
    text[2] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "2. Search the word", {255, 0, 0});
    text[3] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    newFrame(rend, font, bg, text, dest, -1);

    int option;

    bool close = false;
    bool flag[2] = {false, false};
    SDL_Event e;
    int x, y;

    while (!close)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            int button = SDL_GetMouseState(&x, &y);

            for (int i = 0; i < 2; i++)
            {
                if (x >= dest[2 + i].x && x <= (dest[2 + i].x + dest[2 + i].w) && y >= dest[2 + i].y && y <= (dest[2 + i].y + dest[2 + i].h))
                {
                    if (!flag[i])
                    {
                        newFrame(rend, font, bg, text, dest, 2 + i);
                        flag[i] = true;  // flags are used to trace mouse position and display button accordingly
                    }
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        option = i + 1;
                        close = true;
                    }
                }
                else
                {
                    if (flag[i])
                    {
                        newFrame(rend, font, bg, text, dest, -1); // if there is any change in the frame load the fram again
                        flag[i] = false;
                    }
                }
            }

            if (e.type == SDL_QUIT)
            {
                close = true;
                return;
            }
        }
    }

    SDL_RenderClear(rend);

    SDL_DestroyTexture(bg);
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(text[i]);
    }

    SDL_RenderClear(rend);

    int player;
    bool quit = false;

    if (option == 2)
    {
        player = searchTheWord(rend, font, quit); // calling search the word game
    }
    else
    {
        guessTheWord(font, rend, quit); // calling guess the word
        SDL_RenderClear(rend);
        player = 1;
    }

    if (quit)
        return;

    bool choice = closeGame(rend, font, player);

    if (!choice)
        chooseGame(window, rend, font); // running the game loop again if the player chooses new game
}

void newFrame(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *text[], SDL_Rect dest[], int idx)
{
    // in case of frame change load the frame
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);
    int i;

    if (idx == -1)
    {
        for (i = 0; i < 4; i++)
        {
            SDL_RenderFillRect(rend, &dest[i]);
        }
    }
    else
    {
        for (i = 0; i < idx; i++)
        {
            SDL_RenderFillRect(rend, &dest[i]);
        }
        for (i = idx + 1; i < 4; i++)
        {
            SDL_RenderFillRect(rend, &dest[i]);
        }

        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
        SDL_RenderFillRect(rend, &dest[idx]);
        SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);
    }

    for (i = 0; i < 4; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    SDL_RenderPresent(rend);
}
