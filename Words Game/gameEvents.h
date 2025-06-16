
#include <stdio.h>
#include <bits/stdc++.h>
#include "number.h"
#define maxPuzzle 20
#define bufferSize 100

struct choices
{
    int playerNumber;
    int roundNumber;
    int puzzleSize;
    int totalTime;
};

struct position
{
    int isHorizontal;
    int index;
    int startIdx;
};

struct puzzleLocation
{
    int x;
    int y;
};

char puzzle[maxPuzzle][maxPuzzle];

void createPuzzle(int size)
{
    // this function will generate a puzzle board with random characters
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            int number = rand() % 26;
            char alphabet = 'a' + number;
            puzzle[i][j] = alphabet;
        }
    }
}

struct position editPuzzle(char word[], int length, int size)
{
    // overwriting the selected word at random position
    int m = size - length + 1;
    int startIndex = randomNumber() % m;
    int endIndex = startIndex + length;
    int isHorizontal = randomNumber() % 2;
    int index = randomNumber() % size;
    int i, j;

    if (isHorizontal == 1)
    {
        // placing the word horizontally
        for (i = startIndex, j = 0; i < endIndex; i++, j++)
        {
            puzzle[index][i] = word[j];
        }
    }
    else
    {
        // placing the word vertically
        for (i = startIndex, j = 0; i < endIndex; i++, j++)
        {
            puzzle[i][index] = word[j];
        }
    }

    struct position pos;
    pos.isHorizontal = isHorizontal;
    pos.index = index;
    pos.startIdx = startIndex;

    return pos;
}

struct puzzleLocation displayPuzzle(SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *tex[], int size, SDL_Rect inputRect[], SDL_Rect puzzleRect[])
{
    int n = size * size;

    int i, j;
    int idx = 0, xPos, yPos;

    switch (size)
    {
    case 15:
        xPos = 270;
        yPos = 89;
        break;
    case 14:
        xPos = 289;
        yPos = 106; // displaying the puzzle according to puzzle size
        break;
    case 13:
        xPos = 308;
        yPos = 123;
        break;
    case 12:
        xPos = 327;
        yPos = 140;
        break;
    case 11:
        xPos = 346;
        yPos = 157;
        break;
    case 10:
        xPos = 365;
        yPos = 174;
        break;
    }

    struct puzzleLocation location;

    location.x = xPos;
    location.y = yPos;

    int tempX = xPos, tempY = yPos;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            puzzleRect[idx].h = 33;
            puzzleRect[idx].w = 39;
            puzzleRect[idx].x = tempX;
            puzzleRect[idx].y = tempY;

            tempX += 43;
            idx++;
            if (idx == size)
                break;
        }
        tempX = xPos;
        tempY += 36;
    }

    for (i = 0; i < size; i++)
    {
        inputRect[i].h = 33;
        inputRect[i].w = 39;
        inputRect[i].x = tempX;
        inputRect[i].y = tempY;

        tempX += 43;
    }

    idx = 0;
    SDL_Surface *surface;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            char ch = puzzle[i][j];
            char buffer[5];
            sprintf(buffer, " %c ", ch);
            surface = TTF_RenderText_Solid(font, buffer, {0, 0, 0});
            tex[idx] = SDL_CreateTextureFromSurface(rend, surface);
            SDL_FreeSurface(surface);
            idx++;
            if (idx == size)
                break;
        }
    }

    return location;
}

void printResult(int flag, int isHorizontal, int index, int option, char word[], SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[])
{
    // this function will print the result after cross checking
    int i, j;
    char buffer1[bufferSize], buffer2[bufferSize];
    SDL_Surface *surface;

    if (flag == 1)
    {
        // correct answer
        surface = TTF_RenderText_Solid(font, "Congratulation!! Your ans is correct", {255, 0, 255});
        text[2] = SDL_CreateTextureFromSurface(rend, surface);
    }
    else
    {
        // wrong answer
        if (option == 0) // wordFind
            sprintf(buffer1, "Your ans is wrong. Correct word is %s", word);

        else // positionFind
            sprintf(buffer1, "Alas!! Your answer is wrong");
        surface = TTF_RenderText_Solid(font, buffer1, {255, 0, 255});
        text[2] = SDL_CreateTextureFromSurface(rend, surface);
    }

    SDL_FreeSurface(surface);

    // printing the position of the word in the puzzle
    if (isHorizontal == 1)
    {
        sprintf(buffer2, "The word is in %d th row", index + 1);
        surface = TTF_RenderText_Solid(font, buffer2, {255, 0, 255});
        text[3] = SDL_CreateTextureFromSurface(rend, surface);
    }
    else
    {
        sprintf(buffer2, "The word is in %d th column", index + 1);
        surface = TTF_RenderText_Solid(font, buffer2, {255, 0, 255});
        text[3] = SDL_CreateTextureFromSurface(rend, surface);
    }

    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "Press any key to continue", {255, 0, 255});
    text[4] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    int yPos = 672;

    for (i = 2; i < 5; i++)
    {
        dest[i].w = 800;
        dest[i].h = 38;
        dest[i].x = 200;
        dest[i].y = yPos;

        yPos += 41;
    }

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 2; i < 5; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    for (i = 0; i < 3; i++)
    {
        SDL_RenderCopy(rend, text[i + 2], NULL, &dest[i + 2]);
    }

    SDL_RenderPresent(rend);
}

void holdWindow(SDL_Renderer *&rend, bool &quit)
{
    // hold the frame untill the user gives any input
    bool close = false;

    while (!close)
    {
        SDL_Event e;
        SDL_PollEvent(&e);

        if (e.type == SDL_KEYUP)
            close = true;

        if (e.type == SDL_QUIT)
        {
            quit = true;
            close = true;
        }
    }

    SDL_RenderClear(rend);
}

void sdlTextureDestroy(SDL_Texture *&bg, SDL_Texture *inputText[], SDL_Texture *text[], SDL_Texture *tex[], SDL_Texture *&time, SDL_Texture *img[], SDL_Texture *duals[], int size, bool wordFind, int player)
{
    // destroy all the textures
    int i;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(time);

    for (i = 0; i < size * size; i++)
    {
        SDL_DestroyTexture(tex[i]);
    }

    for (i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(text[i]);
    }

    if (wordFind)
    {
        for (i = 0; i < size; i++)
        {
            SDL_DestroyTexture(inputText[i]);
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            SDL_DestroyTexture(img[i]);
        }
    }

    if (player == 2)
    {
        for (i = 0; i < 5; i++)
        {
            SDL_DestroyTexture(duals[i]);
        }
    }
}
