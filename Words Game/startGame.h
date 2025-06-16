#include "chooseGame.h"

void gameInit(SDL_Window *&window, SDL_Renderer *&rend, TTF_Font *&font)
{
    // initialing game loop

    SDL_Surface *surface = IMG_Load("Alphabet_image/start_game1.jpg");

    SDL_RenderClear(rend);
    SDL_Texture *start = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(rend, start, NULL, NULL);

    SDL_Rect startRect = {350, 250, 500, 300};

    surface = TTF_RenderText_Solid(font, "WORD GAME", {255, 0, 0});
    SDL_Texture *startText = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(rend, startText, NULL, &startRect);

    SDL_RenderPresent(rend);

    bool close = false;

    while (!close)
    {
        SDL_Event e;
        SDL_PollEvent(&e);

        if (e.type == SDL_QUIT)
        {
            close = true;
            return;
        }

        if (e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONUP)
            close = true;
    }

    SDL_DestroyTexture(start);
    SDL_DestroyTexture(startText);

    chooseGame(window, rend, font); // this function is in chooseGame.h header file
}