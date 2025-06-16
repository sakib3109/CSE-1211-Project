
#include <stdio.h>
#include <bits/stdc++.h>
#include "sdlMouseInput.h"
#define maxWords 100
#define maxLength 20

struct ans
{
    int flag;
    int isHorizontal;
    int index;
};

int result(int, int, int, char[], struct point *, SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[], struct ans &);
struct ans crossCheck(char[], int, struct point *, int, int);
void wordCopy(char[], int, int, int, int);

// createPuzzle(), editPuzzle(), displayPuzzle(), printResult these functions are defined in gameEvents.h header file

void findPosition(struct choices choice, SDL_Renderer *&rend, TTF_Font *&font, bool &quit)
{
    // This function will call the function to create a puzzle. It will randomly choose one word from the word file. Then it will call the function editPuzzle() and displayPuzzle() to overwrite the selected word in a random position of the puzzle and display the puzzle. It will also call the functions to find and cross-check the result and print the result.

    char wordsAll[maxWords][maxLength];

    FILE *file;

    file = fopen("puzzleWords", "r");

    int wordCount;

    fscanf(file, "%d", &wordCount);

    for (int i = 0; i < wordCount; i++)
    {
        fscanf(file, "%s", wordsAll[i]); // fetching the words from "puzzleWords" file
    }

    fclose(file);

    int size = choice.puzzleSize;
    SDL_Surface *surface;
    SDL_Texture *bg;
    SDL_Rect dest[N];
    SDL_Rect puzzleRect[size * size];
    SDL_Rect inputRect[size];
    SDL_Rect Mousedest[2];
    SDL_Texture *inputText[size];
    SDL_Texture *text[N];
    SDL_Texture *tex[size * size];
    SDL_Texture *time;
    SDL_Texture *img[2];
    SDL_Texture *duals[N];
    struct position posi;

    int i, num, pos, length, isHorizontal, index;
    int yPos = 10, xPos;
    char input[20], word[20];
    char buffer[Size];

    Mousedest[0].w = Mousedest[1].w = 200;
    Mousedest[0].h = Mousedest[1].h = 50;
    Mousedest[0].x = Mousedest[1].x = 950;
    Mousedest[0].y = 200;
    Mousedest[1].y = 265;
    dest[0] = {150, 4, 900, 40};
    dest[1] = {150, 45, 900, 40};
    int idx = randomNumber() % wordCount; // choosing a word randomly from the word file

    length = stringLength(wordsAll[idx]);

    for (i = 0; i < length; i++)
    {
        word[i] = wordsAll[idx][i];
    }
    word[i] = '\0';

    surface = IMG_Load("Alphabet_image/background.png");
    bg = SDL_CreateTextureFromSurface(rend, surface);
    img[0] = SDL_CreateTextureFromSurface(rend, surface);
    img[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    sprintf(buffer, "Find the position of the word '%s' in puzzle", word);
    surface = TTF_RenderText_Solid(font, buffer, {255, 0, 255});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, "First click starting index, then last index", {255, 0, 255});
    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    createPuzzle(size); // creating puzzle with random characters
    int curTime;

    posi = editPuzzle(word, length, size); // overwriting the selected word in random position of the puzzle
    isHorizontal = posi.isHorizontal;
    int row, col;

    if (isHorizontal == 1)
    {
        row = posi.index;
        col = posi.startIdx;
    }
    else
    {
        col = posi.index;
        row = posi.startIdx;
    }
    struct ans answer;
    struct puzzleLocation location = displayPuzzle(rend, font, tex, size, inputRect, puzzleRect);

    // taking the position of word as mouse input from the user
    struct point *coordinates = getMouseInput(rend, font, bg, time, text, tex, img, Mousedest, puzzleRect, dest, curTime, size, choice, location, duals, quit);
    // see sdlMouseInput.h header file

    if (quit)
        return;

    // checking whether the result is correct or not

    int _flag = result(isHorizontal, row, col, word, coordinates, rend, font, text, dest, answer);

    bool ansr;
    if (_flag || answer.flag) // considering both simple check and cross check
        ansr = true;
    else
        ansr = false;

    windowLoad(size, rend, font, bg, text, tex, time, img, dest, puzzleRect, Mousedest, curTime);
    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, ansr, true, duals, quit);

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 2; i < 5; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    for (i = 2; i < 5; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    SDL_RenderPresent(rend);

    holdWindow(rend, quit);

    sdlTextureDestroy(bg, inputText, text, tex, time, img, duals, size, false, choice.playerNumber);
}

int result(int isHorizontal, int row, int col, char word[], struct point *coordinates, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[], struct ans &answer)
{
    // This function will check whether the result is right or wrong.
    int x0 = row, y0 = col, x1, y1, index;
    int length = stringLength(word);

    if (isHorizontal)
    {
        index = row;
        x1 = x0;
        y1 = y0 + length - 1;
    }
    else
    {
        index = col;
        x1 = x0 + length - 1;
        y1 = y0;
    }

    if (x0 == coordinates[0].x && y0 == coordinates[0].y && x1 == coordinates[1].x && y1 == coordinates[1].y)
    {
        printResult(1, isHorizontal, index, 1, word, rend, font, text, dest);
        return 1;
    }

    // crossChecking whether the word is present multiple times or not
    // if so then any one will be considered as correct answer
    answer = crossCheck(word, length, coordinates, isHorizontal, index);

    printResult(answer.flag, answer.isHorizontal, answer.index, 1, word, rend, font, text, dest);

    return 0;
}

struct ans crossCheck(char word[], int length, struct point *coordinates, int isHorizontal, int index)
{
    // In some cases, there might be multiple occurrences of the given word in the puzzle. In such a case any of the possible answers will be considered as correct. This function will handle this to print the result accordingly.

    struct ans answer;

    if (coordinates[0].x == coordinates[1].x)
    {
        answer.isHorizontal = 1;
        answer.index = coordinates[0].x;
    }

    else if (coordinates[0].y == coordinates[1].y)
    {
        answer.isHorizontal = 0;
        answer.index = coordinates[0].y;
    }

    else
    {
        answer.flag = 0;
        answer.isHorizontal = isHorizontal;
        answer.index = index;
        return answer;
    }

    if (coordinates[0].x >= coordinates[1].x || coordinates[0].y >= coordinates[1].y)
    {
        answer.flag = 0;
        answer.isHorizontal = isHorizontal;
        answer.index = index;
        return answer;
    }

    if (answer.isHorizontal)
        length = coordinates[1].x - coordinates[0].x;
    else
        length = coordinates[1].y - coordinates[0].y;

    char temp[15];

    wordCopy(temp, answer.isHorizontal, coordinates[0].x, coordinates[0].y, length);

    if (stringCmp(word, temp) == 1)
    {
        answer.flag = 1;
        return answer;
    }
    else
    {
        answer.flag = 0;
        answer.isHorizontal = isHorizontal;
        answer.index = index;
        return answer;
    }
}

void wordCopy(char temp[], int isHorizontal, int row, int col, int length)
{
    // Copy one string to another.
    int startIdx, endIdx;

    if (isHorizontal == 1)
    {
        startIdx = col;
    }
    else
    {
        startIdx = row;
    }

    endIdx = startIdx + length;
    int i, idx = 0;

    if (isHorizontal == 1)
    {
        for (i = startIdx; i < endIdx; i++, idx++)
        {
            temp[idx] = puzzle[row][i];
        }
    }
    else
    {
        for (i = startIdx; i < endIdx; i++, idx++)
        {
            temp[idx] = puzzle[i][col];
        }
    }
    temp[idx] = '\0';
}
