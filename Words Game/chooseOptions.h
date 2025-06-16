
#include <stdio.h>
#include "posFind.h"
#define MAX 28

void frameLoad(int, SDL_Renderer *&, TTF_Font *&, SDL_Texture *&, SDL_Texture *[], SDL_Rect[]);
bool choosePlayer(SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], struct choices &, SDL_Texture *&);
bool chooseRound(SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], struct choices &, SDL_Texture *&);
bool choosePuzzle(SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], struct choices &, SDL_Texture *&);
bool chooseTimer(SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], struct choices &, SDL_Texture *&);
void showButton(SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], SDL_Texture *&, bool, int, int);

int chooseOptions(int size, int option, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, bool &quit)
{
    struct choices choice;

    SDL_Texture *text[MAX];
    SDL_Rect dest[MAX];

    bool flag;

    flag = choosePlayer(rend, font, text, dest, choice, bg); // choose single player or dual player
    if (!flag)
        return 10;
    flag = chooseRound(rend, font, text, dest, choice, bg); // choose number of rounds
    if (!flag)
        return 10;
    flag = choosePuzzle(rend, font, text, dest, choice, bg); // choose size of puzzle
    if (!flag)
        return 10;
    flag = chooseTimer(rend, font, text, dest, choice, bg); // choose total time
    if (!flag)
        return 10;

    SDL_DestroyTexture(bg);
    for (int i = 0; i < MAX; i++)
    {
        SDL_DestroyTexture(text[i]);
    }

    int ct = choice.roundNumber;

    if (choice.playerNumber == 2)
        ct = 2 * choice.roundNumber;

    for (int i = 0; i < ct; i++)
    {
        if (quit)
            return 10;
        if (option == 1)
        {
            findWord(choice, rend, font, quit); // callling findWord game
        }
        else
        {
            findPosition(choice, rend, font, quit); // calling findPosition game
        }
    }

    return choice.playerNumber;
}

bool choosePlayer(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], struct choices &choice, SDL_Texture *&bg)
{
    dest[0] = {275, 45, 650, 60};
    dest[1] = {300, 125, 250, 60};
    dest[2] = {650, 125, 250, 60};

    SDL_Surface *surface = TTF_RenderText_Solid(font, "How many players you are", {255, 255, 255});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "Single player", {255, 255, 255});
    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "Double player", {255, 255, 255});
    text[2] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    frameLoad(3, rend, font, bg, text, dest);

    int x, y;
    SDL_Event e;

    bool close = false;
    bool flag[2] = {false, false};

    while (!close)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            int button = SDL_GetMouseState(&x, &y);

            if (x >= dest[1].x && x <= (dest[1].x + dest[1].w) && y >= dest[1].y && y <= (dest[1].y + dest[1].h))
            {
                if (!flag[0])
                {
                    showButton(rend, font, text, dest, bg, flag[0], 1, 3); // displaying buttons
                    flag[0] = true;
                }
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    choice.playerNumber = 1;
                    close = true;
                }
            }
            else
            {
                if (flag[0])
                {
                    showButton(rend, font, text, dest, bg, flag[0], 1, 3);
                    flag[0] = false;
                }
            }
            if (x >= dest[2].x && x <= (dest[2].x + dest[2].w) && y >= dest[2].y && y <= (dest[2].y + dest[2].h))
            {
                if (!flag[1])
                {
                    showButton(rend, font, text, dest, bg, flag[1], 2, 3);
                    flag[1] = true;
                }
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    choice.playerNumber = 2;
                    close = true;
                }
            }
            else
            {
                if (flag[1])
                {
                    showButton(rend, font, text, dest, bg, flag[1], 2, 3);
                    flag[1] = false;
                }
            }
            if (e.type == SDL_QUIT)
            {
                close = true;
                return false;
            }
        }
    }
    return true;
}

bool chooseRound(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], struct choices &choice, SDL_Texture *&bg)
{

    dest[3] = {200, 205, 800, 60};

    dest[4] = {520, 285, 60, 60};
    
    dest[5] = {620, 285, 60, 60};

    SDL_Surface *surface = TTF_RenderText_Solid(font, "How many rounds do you want to play", {255, 0, 255});
    text[3] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("Alphabet_image/underscore.png");
    text[4] = SDL_CreateTextureFromSurface(rend, surface);
    text[5] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    frameLoad(6, rend, font, bg, text, dest);

    int length = 0, digit[3];
    digit[0] = digit[1] = 0;
    bool close = false;

    int enterFlag = 0;
    int backspaceFlag = 0;
    int flag = 0;

    SDL_Event e;
    int i;

    while (!close)
    {
        // taking the input of total number of rounds from keyboard
        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_KEYUP)
            {
                backspaceFlag = 0;
                flag = 0;
                switch (e.key.keysym.sym)
                {
                case SDLK_KP_0:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 0;
                    }
                    break;
                case SDLK_0:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 0;
                    }
                    break;
                case SDLK_KP_1:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 1;
                    }
                    break;
                case SDLK_1:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 1;
                    }
                    break;
                case SDLK_2:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 2;
                    }
                    break;
                case SDLK_3:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 3;
                    }
                    break;
                case SDLK_4:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 4;
                    }
                    break;
                case SDLK_5:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 5;
                    }
                    break;
                case SDLK_6:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 6;
                    }
                    break;
                case SDLK_7:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 7;
                    }
                    break;
                case SDLK_8:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 8;
                    }
                    break;
                case SDLK_9:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 9;
                    }
                    break;
                case SDLK_KP_2:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 2;
                    }
                    break;
                case SDLK_KP_3:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 3;
                    }
                    break;
                case SDLK_KP_4:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 4;
                    }
                    break;
                case SDLK_KP_5:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 5;
                    }
                    break;
                case SDLK_KP_6:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 6;
                    }
                    break;
                case SDLK_KP_7:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 7;
                    }
                    break;
                case SDLK_KP_8:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 8;
                    }
                    break;
                case SDLK_KP_9:
                    if (length < 2)
                    {
                        flag = 1;
                        digit[length] = 9;
                    }
                    break;

                case SDLK_BACKSPACE:
                    if (length > 0)
                    {
                        flag = 1;
                        length--;
                        backspaceFlag = 1;
                        surface = IMG_Load("Alphabet_image/underscore.png");
                        text[length + 4] = SDL_CreateTextureFromSurface(rend, surface);
                        SDL_FreeSurface(surface);
                        SDL_RenderClear(rend);

                        SDL_RenderCopy(rend, bg, NULL, NULL);
                        SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

                        for (i = 0; i < 6; i++)
                        {
                            SDL_RenderFillRect(rend, &dest[i]);
                        }

                        for (i = 0; i<6; i++)
                        {
                            SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
                        }

                        SDL_RenderPresent(rend);
                    }
                    break;
                case SDLK_RETURN:
                    enterFlag = 1;
                    close = true;
                    break;
                }
                if (flag && !enterFlag && !backspaceFlag)
                {
                    surface = IMG_Load("Alphabet_image/bg1.jpg");
                    text[length + 4] = SDL_CreateTextureFromSurface(rend, surface);
                    SDL_FreeSurface(surface);
                    int n = digit[length];

                    char buffer[5];
                    sprintf(buffer, " %d ", n);
                    surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
                    text[length + 4] = SDL_CreateTextureFromSurface(rend, surface);
                    SDL_FreeSurface(surface);

                    length++;

                    SDL_RenderClear(rend);

                    SDL_RenderCopy(rend, bg, NULL, NULL);
                    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

                    for (i = 0; i < 6; i++)
                    {
                        SDL_RenderFillRect(rend, &dest[i]);
                    }

                    for (i = 0; i < 6; i++)
                    {
                        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
                    }

                    SDL_RenderPresent(rend);
                }
            }
            if (e.type == SDL_QUIT)
            {
                close = true;
                return false;
            }
        }
    }

    int ct;
    if (length == 1)
        ct = digit[0];
    else
        ct = digit[0] * 10 + digit[1];

    choice.roundNumber = ct;

    return true;
}

bool choosePuzzle(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], struct choices &choice, SDL_Texture *&bg)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Choose difficulty level", {255, 0, 255});
    text[6] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    dest[6] = {400, 365, 400, 60};

    surface = TTF_RenderText_Solid(font, "Choose puzzle size", {255, 0, 255});
    text[7] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    dest[7] = {425, 445, 350, 60};

    int xPos = 300, lowestSize = 10, i, x, y;

    for (i = 8; i < 14; i++)
    {
        dest[i].x = xPos;
        dest[i].y = 525;
        dest[i].w = 60;
        dest[i].h = 60;

        xPos += 100;
    }

    for (i = 8; i < 14; i++)
    {
        char buffer[5];
        int n = lowestSize + i - 8;
        sprintf(buffer, " %d ", n);
        surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
        text[i] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
    }

    frameLoad(14, rend, font, bg, text, dest);

    bool close = false;
    bool flag[6] = {false, false, false, false, false, false};
    SDL_Event e;

    while (!close)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            int button = SDL_GetMouseState(&x, &y);

            for (int i = 0; i < 6; i++)
            {
                if (x >= dest[8 + i].x && x <= (dest[8 + i].x + dest[8 + i].w) && y >= dest[8 + i].y && y <= (dest[8 + i].y + dest[8 + i].h))
                {
                    if (!flag[i])
                    {
                        showButton(rend, font, text, dest, bg, flag[i], 8 + i, 14);
                        flag[i] = true;
                    }
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        choice.puzzleSize = 10 + i;
                        close = true;
                    }
                }
                else
                {
                    if (flag[i])
                    {
                        showButton(rend, font, text, dest, bg, flag[i], 8 + i, 14);
                        flag[i] = false;
                    }
                }
            }

            if (e.type == SDL_QUIT)
            {
                close = true;
                return false;
            }
        }
    }
    return true;
}

bool chooseTimer(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], struct choices &choice, SDL_Texture *&bg)
{

    SDL_Surface *surface = TTF_RenderText_Solid(font, "Choose timer (sec)", {255, 0, 255});
    text[14] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    dest[14] = {425, 605, 350, 60};

    int i, xPos = 60, x, y;

    for (i = 15; i < 28; i++)
    {
        dest[i].x = xPos;
        dest[i].y = 685;
        dest[i].w = 60;
        dest[i].h = 60;

        xPos += 85;
    }

    int temp = 0;

    for (i = 15; i < 28; i++)
    {
        char buffer[5];
        int n = 30 + temp;
        sprintf(buffer, " %d ", n);
        surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
        text[i] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);

        temp += 5;
    }

    frameLoad(28, rend, font, bg, text, dest);
    bool close = false;
    bool flag[13];
    memset(flag, false, sizeof(flag));
    SDL_Event e;

    while (!close)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            int button = SDL_GetMouseState(&x, &y);

            for (int i = 0; i < 13; i++)
            {
                if (x >= dest[15 + i].x && x <= (dest[15 + i].x + dest[15 + i].w) && y >= dest[15 + i].y && y <= (dest[15 + i].y + dest[15 + i].h))
                {
                    if (!flag[i])
                    {
                        showButton(rend, font, text, dest, bg, flag[i], 15 + i, 28);
                        flag[i] = true;
                    }
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        choice.totalTime = 30 + i * 5;
                        close = true;
                    }
                }
                else
                {
                    if (flag[i])
                    {
                        showButton(rend, font, text, dest, bg, flag[i], 15 + i, 28);
                        flag[i] = false;
                    }
                }
            }

            if (e.type == SDL_QUIT)
            {
                close = true;
                return false;
            }
        }
    }
    return true;
}

void frameLoad(int n, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *&bg, SDL_Texture *text[], SDL_Rect dest[])
{
    int i;

    SDL_RenderClear(rend);

    SDL_RenderCopy(rend, bg, NULL, NULL);

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < n; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    for (i = 0; i < n; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    SDL_RenderPresent(rend);
}

void showButton(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], SDL_Texture *&bg, bool flag, int idx, int n)
{
    // This function will display the buttons. In this case, if the cursor comes to an option, the colour of that option will be changed. If the cursor is moved away, then the colour is changed again and gets its previous look.

    int i;
    SDL_RenderClear(rend);

    SDL_RenderCopy(rend, bg, NULL, NULL);

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < idx; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }
    if (!flag)
    {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);  // if flag is false then the colour will be blue
        SDL_RenderFillRect(rend, &dest[idx]);         // if flag is true then the colour will be green
        SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);
    }
    else
    {
        SDL_RenderFillRect(rend, &dest[idx]);
    }
    for (i = idx + 1; i < n; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    for (i = 0; i < n; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }
    SDL_RenderPresent(rend);
}
