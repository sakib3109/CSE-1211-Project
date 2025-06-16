#include <stdio.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#define N 5
#define Size 100

// handling the case of double players

void doublePlayer(SDL_Renderer *&rend, TTF_Font *&font, int playerNo, int totalRound, int &currentTime, bool flag, bool _flag, SDL_Texture *text[], bool &quit)
{
    // This function will enable the dual player mode, calculate the score of each player and print the result accordingly.
    if (quit)
        return;

    if (playerNo == 1) // in case of single player game
        return;

    int i;

    SDL_Rect dest[N];
    SDL_Surface *surface;

    dest[0] = {20, 130, 100, 50};
    dest[1] = {20, 190, 140, 50};
    dest[2] = {20, 250, 150, 50};
    dest[3] = {20, 310, 210, 50};
    dest[4] = {20, 370, 230, 50};

    char buffer1[Size], buffer2[Size], buffer3[Size], buffer4[Size];

    static int round = 2;
    int temp = round / 2;

    if (_flag)
        round++; // keeping the record of round number

    sprintf(buffer1, "Round %d", temp);
    surface = TTF_RenderText_Solid(font, buffer1, {255, 0, 255});
    text[0] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    int player;
    static int ct = 1;

    // keeping the track of the turn of which player
    if (ct % 2 == 1)
    {
        player = 1;
    }
    else
    {
        player = 2;
    }

    if (_flag)
        ct++;

    sprintf(buffer2, "Player %d's turn", player);
    surface = TTF_RenderText_Solid(font, buffer2, {255, 0, 255});
    text[1] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    static int score1 = 0; // static variables are used to keep the track of score over multiple rounds
    static int score2 = 0;

    if (flag) // add the remaining time in score if the ans is correct. In case of wrong ans don't add.
    {
        // keeping track of scores of two players
        if (player == 1)
        {
            score1 += currentTime;
        }
        else
        {
            score2 += currentTime;
        }
    }

    sprintf(buffer3, "Player 1's score %d", score1);
    surface = TTF_RenderText_Solid(font, buffer3, {255, 0, 255});
    text[2] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    sprintf(buffer4, "Player 2's score %d", score2);
    surface = TTF_RenderText_Solid(font, buffer4, {255, 0, 255});
    text[3] = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);

    for (i = 0; i < 4; i++)
    {
        SDL_RenderFillRect(rend, &dest[i]);
    }

    for (i = 0; i < 4; i++)
    {
        SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
    }

    if (ct == 2 * totalRound + 1) // declaring the winner of the game
    {
        if (score1 > score2)
        {
            surface = TTF_RenderText_Solid(font, "Player 1 is winner", {255, 0, 255});
        }
        else if (score1 < score2)
        {
            surface = TTF_RenderText_Solid(font, "Player 2 is winner", {255, 0, 255});
        }
        else
        {
            surface = TTF_RenderText_Solid(font, "The game is drawn", {255, 0, 255});
        }
        text[4] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
        SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);
        SDL_RenderFillRect(rend, &dest[4]);
        SDL_RenderCopy(rend, text[4], NULL, &dest[4]);
    }
}
