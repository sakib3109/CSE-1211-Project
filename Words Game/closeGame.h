
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

bool closeGame(SDL_Renderer *&rend, TTF_Font *&font, int player)
{
    // This function will display the page where the player gets two options- “New game” and “Game over”. If the player chooses “New game” then the game loop will keep running. If he chooses the “Game over” option, then the game loop will be terminated.

    int i, j, option;
    SDL_Surface *surface;
    SDL_RenderClear(rend);

    surface = IMG_Load("Alphabet_image/start.jpg");
    SDL_Texture *start = SDL_CreateTextureFromSurface(rend, surface);
    SDL_RenderCopy(rend, start, NULL, NULL);

    bool close;

    // in case of single player
    if (player == 1)
    {

        SDL_Rect des[2];

        for (i = 0; i < 2; i++)
        {
            des[i].w = des[i].h = 300;
            des[i].y = 250;
        }
        des[0].x = 170;
        des[1].x = 730;

        SDL_Texture *img[2];

        surface = IMG_Load("Alphabet_image/newGame.png");
        img[0] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);

        surface = IMG_Load("Alphabet_image/gameOver.png");
        img[1] = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);

        for (i = 0; i < 2; i++)
        {
            SDL_RenderCopy(rend, img[i], NULL, &des[i]);
        }

        SDL_RenderPresent(rend);

        close = false;
        bool flag[2] = {false, false};
        bool frameChange = false;

        while (!close)
        {
            // checking whether the player chooses new game or game over
            int x, y;
            SDL_Event e;
            SDL_PollEvent(&e);
            int button = SDL_GetMouseState(&x, &y);

            if (e.type == SDL_QUIT)
            {
                close = true;
                return 1;
            }

            if (x >= des[0].x && x <= (des[0].x + des[0].w) && y >= des[0].y && y <= (des[0].y + des[0].h))
            {
                if (!flag[0])
                {
                    des[0].x = 120;
                    des[0].y = 200;
                    des[0].w = des[0].h = 400;
                    frameChange = true;
                }
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    option = 1;
                    close = true;
                }
            }
            else
            {
                des[0].x = 170;
                des[0].y = 250;
                des[0].w = des[0].h = 300;
                frameChange = true;
            }

            if (x >= des[1].x && x <= (des[1].x + des[1].w) && y >= des[1].y && y <= (des[1].y + des[1].h))
            {
                if (!flag[1])
                {
                    des[1].x = 680;
                    des[1].y = 200;
                    des[1].w = des[1].h = 400;
                    frameChange = true;
                }
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    option = 2;
                    close = true;
                }
            }
            else
            {
                des[1].x = 730;
                des[1].y = 250;
                des[1].w = des[1].h = 300;
                frameChange = true;
            }

            if (frameChange)
            {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, start, NULL, NULL);
                for (i = 0; i < 2; i++)
                {
                    SDL_RenderCopy(rend, img[i], NULL, &des[i]);
                }
                SDL_RenderPresent(rend);
                frameChange = false;
            }

            if (e.type == SDL_QUIT)
            {
                close = true;
                return 1;
            }
        }

        for (j = 0; j < 2; j++)
        {
            SDL_DestroyTexture(img[j]);
        }
    }

    if (player == 2)
    {
        // as static variables are used in dualPlayer function there will be no new game option in dualPlayer mode
        // to initialize the static variables again we have to terminate the game

        surface = IMG_Load("Alphabet_image/gameOver.png");
        SDL_Texture *gameOver = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
        SDL_Rect gameOverRect = {400, 200, 400, 400};
        SDL_RenderCopy(rend, gameOver, NULL, &gameOverRect);
        SDL_RenderPresent(rend);

        close = false;
        bool flag = false;
        int x, y;

        while (!close)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            int button = SDL_GetMouseState(&x, &y);

            if (e.type == SDL_QUIT)
            {
                close = true;
                return 1;
            }

            if (x >= gameOverRect.x && x <= (gameOverRect.x + gameOverRect.w) && y >= gameOverRect.y && y <= (gameOverRect.y + gameOverRect.h))
            {
                gameOverRect = {325, 125, 550, 550};
                flag = true;
            }
            else
            {
                gameOverRect = {400, 200, 400, 400};
                flag = true;
            }

            if (flag)
            {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, start, NULL, NULL);
                SDL_RenderCopy(rend, gameOver, NULL, &gameOverRect);
                SDL_RenderPresent(rend);
                flag = false;
            }

            if (e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONUP)
                close = true;
        }
        SDL_DestroyTexture(gameOver);
        option = 2;
    }

    SDL_DestroyTexture(start);
    SDL_RenderClear(rend);

    if (option == 1)
        return false;
    return true;
}
