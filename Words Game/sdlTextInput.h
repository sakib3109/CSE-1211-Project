#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "gameEvents.h"
#include "dualPlayer.h"

void loadWindow(SDL_Renderer *&, TTF_Font *&, SDL_Texture *&, SDL_Texture *[], SDL_Texture *[], SDL_Texture *[], SDL_Texture *&, SDL_Rect[], SDL_Rect[], SDL_Rect[], int, int, int);

bool sdlTextInput(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *&time, SDL_Texture *inputText[], SDL_Texture *text[], SDL_Texture *tex[], SDL_Rect dest[], SDL_Rect inputRect[], SDL_Rect puzzleRect[], int &num, char str[], int size, struct choices choice, int &curTime, SDL_Texture *duals[], bool &quit)
{
    // this function will run an event loop to take which word is present in the puzzle as input from the user using the keyboard.

    int length = 0;
    bool close = false;
    SDL_Event e;
    int lastTime = SDL_GetTicks();
    int prevTime = choice.totalTime;
    int i;
    SDL_Surface *surface;
    SDL_Rect tdest = {1050, 150, 170, 50};

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    loadWindow(rend, font, bg, text, tex, inputText, time, dest, inputRect, puzzleRect, 0, 0, size);
    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
    SDL_RenderPresent(rend);

    int enterFlag = 0;
    int backspaceFlag = 0;
    int flag = 0;
    while (!close)
    {
        curTime = (lastTime + choice.totalTime * 1000 - SDL_GetTicks()) / 1000;
        SDL_PollEvent(&e);

        if (e.type == SDL_KEYUP)
        {
            backspaceFlag = 0;
            flag = 0;
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                if (length < size)
                {
                    str[length] = 'a';
                    flag = 1;
                }
                break;
            case SDLK_b:
                if (length < size)
                {
                    str[length] = 'b';
                    flag = 1;
                }
                break;
            case SDLK_c:
                if (length < size)
                {
                    str[length] = 'c';
                    flag = 1;
                }
                break;
            case SDLK_d:
                if (length < size)
                {
                    str[length] = 'd';
                    flag = 1;
                }
                break;
            case SDLK_e:
                if (length < size)
                {
                    str[length] = 'e';
                    flag = 1;
                }
                break;
            case SDLK_f:
                if (length < size)
                {
                    str[length] = 'f';
                    flag = 1;
                }
                break;
            case SDLK_g:
                if (length < size)
                {
                    str[length] = 'g';
                    flag = 1;
                }
                break;
            case SDLK_h:
                if (length < size)
                {
                    str[length] = 'h';
                    flag = 1;
                }
                break;
            case SDLK_i:
                if (length < size)
                {
                    str[length] = 'i';
                    flag = 1;
                }
                break;
            case SDLK_j:
                if (length < size)
                {
                    str[length] = 'j';
                    flag = 1;
                }
                break;
            case SDLK_k:
                if (length < size)
                {
                    str[length] = 'k';
                    flag = 1;
                }
                break;
            case SDLK_l:
                if (length < size)
                {
                    str[length] = 'l';
                    flag = 1;
                }
                break;
            case SDLK_m:
                if (length < size)
                {
                    str[length] = 'm';
                    flag = 1;
                }
                break;
            case SDLK_n:
                if (length < size)
                {
                    str[length] = 'n';
                    flag = 1;
                }
                break;
            case SDLK_o:
                if (length < size)
                {
                    str[length] = 'o';
                    flag = 1;
                }
                break;
            case SDLK_p:
                if (length < size)
                {
                    str[length] = 'p';
                    flag = 1;
                }
                break;
            case SDLK_q:
                if (length < size)
                {
                    str[length] = 'q';
                    flag = 1;
                }
                break;
            case SDLK_r:
                if (length < size)
                {
                    str[length] = 'r';
                    flag = 1;
                }
                break;
            case SDLK_s:
                if (length < size)
                {
                    str[length] = 's';
                    flag = 1;
                }
                break;
            case SDLK_t:
                if (length < size)
                {
                    str[length] = 't';
                    flag = 1;
                }
                break;
            case SDLK_u:
                if (length < size)
                {
                    str[length] = 'u';
                    flag = 1;
                }
                break;
            case SDLK_v:
                if (length < size)
                {
                    str[length] = 'v';
                    flag = 1;
                }
                break;
            case SDLK_w:
                if (length < size)
                {
                    str[length] = 'w';
                    flag = 1;
                }
                break;
            case SDLK_x:
                if (length < size)
                {
                    str[length] = 'x';
                    flag = 1;
                }
                break;
            case SDLK_y:
                if (length < size)
                {
                    str[length] = 'y';
                    flag = 1;
                }
                break;
            case SDLK_z:
                if (length < size)
                {
                    str[length] = 'z';
                    flag = 1;
                }
                break;
            case SDLK_BACKSPACE:
                if (length > 0)
                {
                    flag = 1;
                    length--;
                    backspaceFlag = 1;

                    surface = IMG_Load("Alphabet_image/underscore.png");
                    inputText[length] = SDL_CreateTextureFromSurface(rend, surface);
                    SDL_FreeSurface(surface);

                    SDL_RenderClear(rend);
                    SDL_RenderCopy(rend, bg, NULL, NULL);

                    loadWindow(rend, font, bg, text, tex, inputText, time, dest, inputRect, puzzleRect, curTime, 0, size);
                    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
                    SDL_RenderPresent(rend);
                }
                break;
            case SDLK_RETURN: // player has finished his input giving
                str[length] = '\0';
                enterFlag = 1;
                close = true;
                break;
            }

            if (flag && !enterFlag && !backspaceFlag)
            {
                // flag for adding new character
                // backspaceFlag to erase the previous character
                // enterFlag to terminate the loop
                surface = IMG_Load("Alphabet_image/background.png");
                inputText[length] = SDL_CreateTextureFromSurface(rend, surface);
                SDL_FreeSurface(surface);

                SDL_RenderCopy(rend, inputText[length], NULL, &dest[length]);

                char ch = str[length];
                char buffer[5];
                sprintf(buffer, " %c ", ch);

                surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
                inputText[length] = SDL_CreateTextureFromSurface(rend, surface);
                SDL_FreeSurface(surface);

                SDL_RenderCopy(rend, inputText[length], NULL, &dest[length]);

                length++;

                // load the frame when user gives any input
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, bg, NULL, NULL);
                loadWindow(rend, font, bg, text, tex, inputText, time, dest, inputRect, puzzleRect, curTime, 0, size);
                doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
                SDL_RenderPresent(rend);
            }
        }
        if (e.type == SDL_QUIT)
        {
            close = true;
            quit = true;
            return false;
        }

        if (curTime != prevTime)
        {
            // load the frame after every second
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, bg, NULL, NULL);
            loadWindow(rend, font, bg, text, tex, inputText, time, dest, inputRect, puzzleRect, curTime, 0, size);
            doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
            SDL_RenderPresent(rend);

            prevTime = curTime;
        }
        if (curTime == 0) // terminate  the loop when the time is finished
            close = true;
    }
    return true;
}

void loadWindow(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *text[], SDL_Texture *tex[], SDL_Texture *inputText[], SDL_Texture *&time, SDL_Rect dest[], SDL_Rect inputRect[], SDL_Rect puzzleRect[], int curTime, int option, int size)
{
    // When sdlTextInput() function runs an event loop to take input from the user, the timer updates its value every second. The loadWindow() function will display the updated time as well as the input given by the user.

    int i;

    char buffer[Size];
    SDL_Rect tdest = {990, 120, 160, 50};

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < 2; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }
    for (i = 0; i < size * size; i++)
    {
        SDL_RenderFillRect(rend, &puzzleRect[i]);
    }
    SDL_RenderFillRect(rend, &tdest);

    for (i = 0; i < 2; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }
    for (i = 0; i < size; i++)
    {
        SDL_RenderCopy(rend, inputText[i], NULL, &inputRect[i]);
    }

    sprintf(buffer, "timer : %d", curTime);
    SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
    time = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(rend, time, NULL, &tdest);

    for (i = 0; i < size * size; i++)
    {
        SDL_RenderCopy(rend, tex[i], NULL, &puzzleRect[i]);
    }
}