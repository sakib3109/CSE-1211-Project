
#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "stringLib.h"
#include "sdlTextInput.h"

// createPuzzle(), editPuzzle(), displayPuzzle(), printResult these functions are defined in gameEvents.h header file

using namespace std;

int findResult(char[], char[], int, int, int, int, SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[]);
int crossCheckResult(char[], char[], int, int, int, SDL_Renderer *&, TTF_Font *&, SDL_Texture *[], SDL_Rect[]);
int isPresent(char[][15], char[]);
void copyWord(char[], int, int, int, int);

void findWord(struct choices choice, SDL_Renderer *&rend, TTF_Font *&font, bool &quit)
{
    // This function will call the function to create a puzzle. It will randomly choose one group of ten words and one random word from the selected group. Then it will call the function editPuzzle() and displayPuzzle() to overwrite the selected word in a random position of the puzzle and display the puzzle. It will also call the functions to find and cross-check the result and print the result.

    // this array stres all the groups of ten words
    char words[8][10][15] = {{"java", "python", "ruby", "php", "javascript", "swift", "csharp", "dart", "cotlin", "fortran"},
                             {"dhaka", "cumilla", "barishal", "rajshahi", "rangpur", "bogra", "sylhet", "khulna", "jessore", "noakhali"},
                             {"usa", "england", "india", "france", "japan", "germany", "italy", "norway", "finland", "russia"},
                             {"bengali", "english", "chinese", "french", "german", "hindi", "rush", "arabic", "swidish", "japanese"},
                             {"mango", "banana", "guava", "lichi", "orange", "lemon", "pear", "cherry", "grape", "apple"},
                             {"rose", "tulip", "marigold", "daisy", "lily", "orchid", "jasmine", "dahlia", "iris", "aster"},
                             {"crow", "eagle", "kite", "pegion", "swan", "bat", "dove", "duck", "crane", "parrot"},
                             {"dog", "cat", "tiger", "lion", "giraf", "zebra", "deer", "sheep", "horse", "goat"}};

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

    int i, num, pos, length, isHorizontal, index, idx;
    int yPos = 4, xPos;
    char input[20], word[20];
    char buffer[Size];

    for (i = 0; i < 2; i++)
    {
        dest[i].w = 1150;
        dest[i].h = 38;
        dest[i].x = 25;
        dest[i].y = yPos;

        yPos += 41;
    }
    surface = TTF_RenderText_Solid(font, "Among the following words find which word is present in the puzzle", {255, 0, 255});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    num = randomNumber() % 8;  // choosing one group randomly
    pos = randomNumber() % 10; // choosing one word from the group randomly

    length = stringLength(words[num][pos]);

    word[length + 1];

    for (i = 0; i < length; i++)
    {
        word[i] = words[num][pos][i];
    }
    word[i] = '\0';

    switch (num)
    {
    case 0:
        surface = TTF_RenderText_Solid(font, "java,python,ruby,php,javascript,swift,csharp,dart,cotlin,fortran", {255, 0, 255});
        break;
    case 1:
        surface = TTF_RenderText_Solid(font, "dhaka,cumilla,barishal,rajshahi,rangpur,bogra,sylhet,khulna,jessore,noakhali", {255, 0, 255});
        break;
    case 2:
        surface = TTF_RenderText_Solid(font, "usa,england,india,france,japan,germany,italy,norway,finland,russia", {255, 0, 255});
        break;
    case 3:
        surface = TTF_RenderText_Solid(font, "bengali,english,chinese,french,german,hindi,rush,arabic,swidish,japanese", {255, 0, 255});
        break;
    case 4:
        surface = TTF_RenderText_Solid(font, "mango,banana,guava,lichi,orange,lemon,pear,cherry,grape,apple", {255, 0, 255});
        break;
    case 5:
        surface = TTF_RenderText_Solid(font, "rose,tulip,marigold,daisy,lily,orchid,jasmine,dahlia,iris,aster", {255, 0, 255});
        break;
    case 6:
        surface = TTF_RenderText_Solid(font, "crow,eagle,kite,pegion,swan,bat,dove,duck,crane,parrot", {255, 0, 255});
        break;
    default:
        surface = TTF_RenderText_Solid(font, "dog,cat,tiger,lion,giraf,zebra,deer,sheep,horse,goat", {255, 0, 255});
        break;
    }

    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    for (i = 0; i < size; i++)
    {
        surface = IMG_Load("Alphabet_image/underscore.png");
        inputText[i] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
    }

    createPuzzle(size); // creating the puzzle with random characters
    int curTime;

    posi = editPuzzle(word, length, size); // overwriting the selected word in random position of the puzzle
    isHorizontal = posi.isHorizontal;
    index = posi.index;

    surface = IMG_Load("Alphabet_image/bg1.jpg");

    SDL_RenderClear(rend);
    bg = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    displayPuzzle(rend, font, tex, size, inputRect, puzzleRect);

    // taking the input from user
    sdlTextInput(rend, font, bg, time, inputText, text, tex, dest, inputRect, puzzleRect, num, input, size, choice, curTime, duals, quit);
    // see sdlTextInput.h header file

    if (quit)
        return;
    // finding whether the result is correct or not
    int flag = findResult(word, input, length, isHorizontal, index, size, rend, font, text, dest);
    int _flag = 0;
    bool ans;

    if (flag == 0)
    {
        int flag1 = isPresent(words[num], input); // checking whether the input word is present in the group of ten words or not

        if (flag1 == 1)
        {
            // if the input word is present in the group then do this
            // crossChecking whether multiple words are present or not
            // if so then anyone will be considersd as correct result
            _flag = crossCheckResult(input, word, size, isHorizontal, index, rend, font, text, dest);
        }
        else
        {
            printResult(0, isHorizontal, index, 0, word, rend, font, text, dest);
        }
    }

    if (flag || _flag) // evaluting both results from simple check and cross check
        ans = true;
    else
        ans = false;

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    loadWindow(rend, font, bg, text, tex, inputText, time, dest, inputRect, puzzleRect, curTime, 0, size);
    doublePlayer(rend, font, choice.playerNumber, choice.roundNumber, curTime, ans, true, duals, quit);
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

    sdlTextureDestroy(bg, inputText, text, tex, time, img, duals, size, true, choice.playerNumber);
}

int findResult(char word[], char input[], int length, int isHorizontal, int index, int size, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[])
{
    // This function will check whether the result is right or wrong.

    if (stringCmp(word, input) == 1)
    {
        printResult(1, isHorizontal, index, 0, word, rend, font, text, dest);
        return 1;
    }
    else
    {
        return 0;
    }
}

int crossCheckResult(char input[], char word[], int size, int isHorizontal, int index, SDL_Renderer *&rend, TTF_Font *&font, SDL_Texture *text[], SDL_Rect dest[])
{
    // In some cases, from the group of ten words, multiple words might be present in the puzzle. In such a case any of the possible answers will be considered as correct. This function will handle this with the help of isPresent() function.

    // if findResult() function returns false then
    // isPresent() function will check whether the input word is one of the given ten words or not. If yes, then the crossCheckResult() function will check whether the input word is present in the puzzle or not and print the result accordingly.

    int i, j, endIndex, length;

    length = stringLength(input);
    endIndex = size - length;

    // checking horizontal presence of the word
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < endIndex; i++)
        {
            char temp[15];
            int flag = 1;
            copyWord(temp, i, j, length, flag);
            int res = stringCmp(input, temp);

            if (res == 1)
            {
                printResult(1, 1, j, 0, input, rend, font, text, dest);
                return 1;
            }
        }
    }

    // checking vertical presence of the word
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < endIndex; i++)
        {
            char temp[15];
            int flag = 0;
            copyWord(temp, i, j, length, flag);
            int res = stringCmp(input, temp);

            if (res == 1)
            {
                printResult(1, 0, j, 0, input, rend, font, text, dest);
                return 1;
            }
        }
    }
    printResult(0, isHorizontal, index, 0, word, rend, font, text, dest);
    return 0;
}

int isPresent(char words[][15], char input[])
{
    // This function will check whether the input word is one of the given ten words or not.

    int i;
    for (i = 0; i < 10; i++)
    {
        if (stringCmp(words[i], input) == 1)
        {
            return 1;
        }
    }
    return 0;
}

void copyWord(char temp[], int i, int j, int length, int isHorizontal)
{
    // Copy one string to another.
    int row, col, idx, idx1 = 0;

    if (isHorizontal == 1)
        row = j;
    else
        col = j;

    if (isHorizontal == 1)
    {
        for (idx = i; idx < i + length; idx++, idx1++)
        {
            temp[idx1] = puzzle[row][idx];
        }
    }

    else
    {
        for (idx = i; idx < i + length; idx++, idx1++)
        {
            temp[idx1] = puzzle[idx][col];
        }
    }

    temp[idx1] = '\0';
}
