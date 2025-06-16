
void buttonShow(SDL_Renderer *&rend, SDL_Texture *text[], SDL_Rect dest[], SDL_Texture *&bg, bool flag, int idx)
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
		SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // if flag is false then the colour will be blue
		SDL_RenderFillRect(rend, &dest[idx]);		  // if flag is true then the colour will be green
		SDL_SetRenderDrawColor(rend, 60, 50, 180, 170);
	}
	else
	{
		SDL_RenderFillRect(rend, &dest[idx]);
	}
	for (i = idx + 1; i < 3; i++)
	{
		SDL_RenderFillRect(rend, &dest[i]);
	}

	for (i = 0; i < 3; i++)
	{
		SDL_RenderCopy(rend, text[i], NULL, &dest[i]);
	}
	SDL_RenderPresent(rend);
}

void mode_screen(SDL_Renderer *&renderer, TTF_Font *&font, SDL_Texture *text[], SDL_Rect des[], SDL_Texture *&bg)
{
	// This function will load all the mode ( “Kids mode” or “Normal mode” ) options on the window.

	surface = TTF_RenderText_Solid(font, "KIDS MODE", {255, 0, 255});
	text[0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(font, "QUIT", {255, 0, 255});
	text[2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect full_screen;
	full_screen.w = 1200;
	full_screen.h = 800;
	full_screen.x = 0;
	full_screen.y = 0;

	des[0].w = 200;
	des[0].h = 90;
	des[0].x = 500;
	des[0].y = 100;

	des[2].w = 150;
	des[2].h = 70;
	des[2].x = 530;
	des[2].y = 500;

	des[1].w = 220;
	des[1].h = 90;
	des[1].x = 490;
	des[1].y = 300;

	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 170);
	SDL_RenderFillRect(renderer, &full_screen);
	surface = IMG_Load("Alphabet_image/background.png");
	bg = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, bg, NULL, NULL);
	SDL_SetRenderDrawColor(renderer, 60, 50, 180, 170);
	SDL_RenderFillRect(renderer, &des[0]);
	SDL_RenderFillRect(renderer, &des[2]);
	SDL_RenderFillRect(renderer, &des[1]);
	SDL_RenderCopy(renderer, text[2], NULL, &des[2]);
	SDL_RenderCopy(renderer, text[0], NULL, &des[0]);

	surface = TTF_RenderText_Solid(font, "NORMAL MODE", {255, 0, 255});
	text[1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, text[1], NULL, &des[1]);

	SDL_RenderPresent(renderer);
	return;
}

int mode(SDL_Renderer *&renderer, TTF_Font *&font, bool &quit)
{
	// Here the player will choose whether he will play “Kids mode” or “Normal mode”.
	// In “kids mode” some letters of the word will be given along with a clue statement. So, this is a mode of less difficulty.
	// On the other hand, in “Normal mode” only the clue statement will be given but no letter would be visible. So this is a comparatively difficult level.

	SDL_Texture *text[3];
	SDL_Rect des[3];
	SDL_Texture *bg;

	mode_screen(renderer, font, text, des, bg);

	surface = IMG_Load("Alphabet_image/background.png");
	bg = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Event mode;
	bool close = false;
	bool flag[3] = {false, false, false};
	int option = 10;
	while (!close)
	{
		int x, y;
		SDL_PollEvent(&mode);
		SDL_GetMouseState(&x, &y);

		if (mode.type == SDL_QUIT)
		{
			quit = true;
			game = 0;
			return 0;
		}

		for (int i = 0; i < 3; i++)
		{
			if (x >= des[i].x && x <= (des[i].x + des[i].w) && y >= des[i].y && y <= (des[i].y + des[i].h))
			{
				if (!flag[i])
				{
					buttonShow(renderer, text, des, bg, flag[i], i); // display buttons
					flag[i] = true;
				}
				if (mode.type == SDL_MOUSEBUTTONUP)
				{
					option = i;
					if (option == 0)
						return 0; // kids mode
					if (option == 1)
						return 1; // normal mode
					if (option == 2)
						return -1; // quit
					close = true;
				}
			}
			else
			{
				if (flag[i])
				{
					buttonShow(renderer, text, des, bg, flag[i], i);
					flag[i] = false;
				}
			}
		}
	}
	return 10;
}
