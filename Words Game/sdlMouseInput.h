
#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "wordFind.h"

int curIdx;
struct point
{
    int x;
    int y;
};

void windowLoad(int, SDL_Renderer *&, TTF_Font *&, SDL_Texture *&, SDL_Texture *[], SDL_Texture *[], SDL_Texture *&, SDL_Texture *[], SDL_Rect[], SDL_Rect[], SDL_Rect[], int &);

struct point *getMouseInput(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *&time, SDL_Texture *text[], SDL_Texture *tex[], SDL_Texture *img[], SDL_Rect Mousedest[], SDL_Rect puzzleRect[], SDL_Rect dest[], int &curTime, int size, struct choices choice, struct puzzleLocation location, SDL_Texture *duals[], bool &quit)
{
    // this function will run an event loop to take the position of the word in the puzzle as input from the user using the mouse.

    int startX = location.x, startY = location.y;
    int endX = startX + size * 43 - 4;
    int endY = startY + size * 36 - 3;
    struct point coordinates[2];
    bool close = false;
    SDL_Rect tdest = {1050, 120, 170, 50};
    int totalTime = choice.totalTime;
    SDL_Surface *surface;
    char buffer[Size];

    int x, y, ct = 0, i;
    curIdx = -1;

    char buffer1[Size], buffer2[Size];

    SDL_Event e;
    int lastTime = SDL_GetTicks();
    int prevTime = totalTime;

    windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
    SDL_RenderPresent(rend);
    int prevX = -1, prevY = -1, curX = 20, curY = 20;
    int prevIdx;

    bool flag[size * size];
    memset(flag, false, sizeof(flag));
    struct point *ptr;

    while (!close)
    {
        SDL_PollEvent(&e);
        int button = SDL_GetMouseState(&x, &y);

        curTime = (lastTime + totalTime * 1000 - SDL_GetTicks()) / 1000;

        if (curTime != prevTime)
        {
            // load the window after every second to display updated time
            windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
            doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
            SDL_RenderPresent(rend);
            prevTime = curTime;
        }

        if (x >= startX && x <= endX && y >= startY && y <= endY)
        {
            // the whole puzzle board has been treated as buttons
            // this loop will display buttons whenever necessary
            for (int i = 0; i < size * size; i++)
            {
                if (x >= puzzleRect[i].x && x <= (puzzleRect[i].x + puzzleRect[i].w) && y >= puzzleRect[i].y && y <= (puzzleRect[i].y + puzzleRect[i].h))
                {
                    curIdx = i;
                    if (!flag[i])
                    {
                        windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
                        doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
                        SDL_RenderPresent(rend);
                        flag[i] = true;
                    }
                }
                else
                {
                    if (flag[i])
                    {
                        windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
                        doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
                        SDL_RenderPresent(rend);
                        flag[i] = false;
                    }
                }
            }
            coordinates[ct].y = (x - startX) / 43;
            coordinates[ct].x = (y - startY) / 36;

            // selecting the position of the word by clicking mouse
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                if (ct == 0)
                {
                    sprintf(buffer1, "startIdx : (%d,%d)", coordinates[ct].x + 1, coordinates[ct].y + 1);
                    surface = TTF_RenderText_Solid(font, buffer1, {255, 0, 255});

                    SDL_RenderFillRect(rend, &Mousedest[0]);

                    img[0] = SDL_CreateTextureFromSurface(rend, surface);
                }
                if (ct == 1)
                {
                    sprintf(buffer2, "endIdx : (%d,%d)", coordinates[ct].x + 1, coordinates[ct].y + 1);
                    surface = TTF_RenderText_Solid(font, buffer2, {255, 0, 255});
                    SDL_RenderFillRect(rend, &Mousedest[1]);

                    img[1] = SDL_CreateTextureFromSurface(rend, surface);
                }

                SDL_FreeSurface(surface);

                windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
                doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
                SDL_RenderPresent(rend);

                ct++;
            }
        }
        else
        {
            curIdx = -1;
            windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
            doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
            SDL_RenderPresent(rend);
        }

        if (ct == 2)
            close = true;

        if (curTime == 0)
            close = true;

        if (e.type == SDL_QUIT)
        {
            quit = true;
            close = true;
        }
    }

    ptr = coordinates;

    curIdx = -1; // this means the cursor is out of puzzle board
    windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, false, false, duals, quit);
    SDL_RenderPresent(rend);

    return ptr;
}

void windowLoad(int size, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *text[], SDL_Texture *tex[], SDL_Texture *&time, SDL_Texture *img[], SDL_Rect dest[], SDL_Rect puzzleRect[], SDL_Rect Mousedest[], int &curTime)
{
    // When sdlMouseInput() function runs an event loop to take input from the user, the timer updates its value every second. The loadWindow() function will display the updated time as well as the input given by the user.

    int i;
    char buffer[Size];
    SDL_Surface *surface;
    SDL_Rect tdest = {990, 120, 160, 50};
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);

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
        SDL_RenderFillRect(rend, &Mousedest[i]);
    }

    if (curIdx >= 0 && curIdx < size * size) // if the cursor is on puzzle board then display button else ignore
    {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
        SDL_RenderFillRect(rend, &puzzleRect[curIdx]);
    }

    for (i = 0; i < 2; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    for (i = 0; i < 2; i++)
    {
        SDL_RenderCopy(rend, img[i], NULL, &Mousedest[i]);
    }

    for (i = 0; i < size * size; i++)
    {
        SDL_RenderCopy(rend, tex[i], NULL, &puzzleRect[i]);
    }

    sprintf(buffer, "timer : %d", curTime);
    surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
    time = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(rend, time, NULL, &tdest);
}