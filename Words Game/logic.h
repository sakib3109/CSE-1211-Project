#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
#include "textures.h"
using namespace std;
int strlen(char word[])
{
	// This function will find the length of a string.
	int char_count = 0;
	while (word[char_count])
	{
		char_count++;
	}

	return char_count;
}
char sdltocharacter()
{
	// This function will poll SDL events from the keyboard and convert the input into a character type variable.

	char ch;

	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		ch = 'a';
		break;
	case SDLK_b:
		ch = 'b';
		break;
	case SDLK_c:
		ch = 'c';
		break;
	case SDLK_d:
		ch = 'd';
		break;
	case SDLK_e:
		ch = 'e';
		break;
	case SDLK_f:
		ch = 'f';
		break;
	case SDLK_g:
		ch = 'g';
		break;
	case SDLK_h:
		ch = 'h';
		break;
	case SDLK_i:
		ch = 'i';
		break;
	case SDLK_j:
		ch = 'j';
		break;
	case SDLK_k:
		ch = 'k';
		break;
	case SDLK_l:
		ch = 'l';
		break;
	case SDLK_m:
		ch = 'm';
		break;
	case SDLK_n:
		ch = 'n';
		break;
	case SDLK_o:
		ch = 'o';
		break;
	case SDLK_p:
		ch = 'p';
		break;
	case SDLK_q:
		ch = 'q';
		break;
	case SDLK_r:
		ch = 'r';
		break;
	case SDLK_s:
		ch = 's';
		break;
	case SDLK_t:
		ch = 't';
		break;

	case SDLK_u:
		ch = 'u';
		break;
	case SDLK_v:
		ch = 'v';
		break;
	case SDLK_w:
		ch = 'w';
		break;
	case SDLK_x:
		ch = 'x';
		break;
	case SDLK_y:
		ch = 'y';
		break;
	case SDLK_z:
		ch = 'z';
		break;
	case SDLK_RETURN:
		ch = '\\';
		break;
	default:
		ch = '-';
		break;
	}

	return ch;
}

int validity_check(char word[], char c, int position_array[])
{
	// When the player gives any input character, this function will check whether the character is present in the word or not. If the word doesn’t contain the character, then this will be considered as a wrong attempt and the player will lose one of his lives.

	int n = strlen(word);
	int count = 0;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (word[i] == c)
		{
			position_array[i] = i;

			count++;
		}
	}
	return count;
}

int next_step(bool &quit)
{
	// This function will check whether the player wants to play another round or he wants to go to the “Menu” option.

	SDL_Event mouse;
	int x, y;
	bool close = false;
	while (!close)
	{
		SDL_PollEvent(&mouse);
		SDL_GetMouseState(&x, &y);
		if (mouse.type == SDL_QUIT)
		{
			quit = true;
			game = 0;
			return 0; // quit
		}

		if (x >= 850 && x <= (850 + 300) && y <= (550 + 100) && y >= 550)
		{
			if (mouse.type == SDL_MOUSEBUTTONUP)
				return 1; // next round
		}
		if (x >= 80 && x <= (80 + 200) && y <= (550 + 100) && y >= 550)
		{
			if (mouse.type == SDL_MOUSEBUTTONUP)
				return 2; // menu
		}
	}

	return 0; // quit
}

void logic_for_adult(SDL_Renderer *&renderer, TTF_Font *&font, bool &quit)
{
	// This function will be executed if the player chooses “Normal mode”. Here no character of the word will be visible at first. This function will choose a random word and its clue from files and load the textures on the window. It will take input from the user, check the result and print the result accordingly.

	srand(time(0));
	FILE *fil;
	FILE *hin;
	fil = fopen("words", "r");
	if (fil == NULL)
	{
		printf("Failed\n");
	}

	hin = fopen("hints", "r");
	if (hin == NULL)
	{
		printf("Failed\n");
	}

	int word_count;

	fscanf(fil, "%d", &word_count);

	char words[word_count + 5][100];
	char hints[word_count + 5][150];
	for (int i = 0; i < word_count; i++)
	{
		fscanf(fil, "%s", words[i]); // fetching words from file
	}
	for (int i = 0; i < word_count; i++)
	{
		fscanf(hin, "%[^\n]%*c", hints[i]); // fetching hints from file
	}

	fclose(fil);
	fclose(hin);

	int word_pos = rand() % word_count; // choosing a random word
	surface = TTF_RenderText_Solid(font, hints[word_pos], {0, 0, 0});

	hinti = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, hinti, NULL, &hint);
	int dash_number = strlen(words[word_pos]);

	SDL_Rect Correct_word;

	Correct_word.x = 450;
	Correct_word.y = 350;
	Correct_word.h = 100;
	Correct_word.w = 250;
	SDL_Texture *Correct_word_tex = NULL;

	surface = TTF_RenderText_Solid(font, words[word_pos], {127, 0, 255});

	Correct_word_tex = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Texture *dashtex = NULL;

	SDL_Rect dash[dash_number];

	surface = TTF_RenderText_Solid(font, "_", {0, 0, 0});

	SDL_Texture *under_score = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	int dash_x_pos = 50;
	int dash_width = 40;
	for (int i = 0; i < dash_number; i++)
	{
		dash[i].w = dash_width;
		dash[i].h = (int)40;
		dash[i].x = dash_x_pos;
		dash_x_pos += 50; // loading textures on the window
		dash[i].y = 80;

		SDL_RenderCopy(renderer, under_score, NULL, &dash[i]);
	}
	surface = IMG_Load("Alphabet_image/23.png");

	heart = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(heart, NULL, NULL, &life[0].w, &life[0].h);
	int life_x_pos = 900;
	int life_width = life[0].w * .04;
	int life_height = life[0].h * .04;

	for (int i = 0; i < 5; i++)
	{
		life[i].w = (int)life_width;
		life[i].h = (int)life_height;
		life[i].x = life_x_pos;
		life_x_pos += life_width + 10;
		life[i].y = 80;
		SDL_RenderCopy(renderer, heart, NULL, &life[i]);
	}

	SDL_Texture *white = NULL;
	surface = IMG_Load("Alphabet_image/24.png");
	white = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Alphabet_image/22.png");

	SDL_Texture *broken = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_RenderPresent(renderer);

	int character_count = 0;
	int correct_ch_count = 0;
	int position_array[dash_number];
	int tracking_array[dash_number];
	memset(tracking_array, -1, sizeof tracking_array);
	int life_count = 1;

	char ager_char = '9';

	bool q = 1;

	// taking input from the user
	while (q)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
		{
			quit = true;
			q = 0;
			game = 0;
			return;
		}
		else if (e.type == SDL_KEYUP)
		{
			if (life_count < 5)
			{

				char ch = sdltocharacter();

				if (ch == '\\')
					break;
				char buffer[5];
				sprintf(buffer, " %c", ch);

				surface = TTF_RenderText_Solid(font, buffer, {0, 0, 0});
				SDL_Texture *chf = NULL;
				chf = SDL_CreateTextureFromSurface(renderer, surface);

				SDL_FreeSurface(surface);

				memset(position_array, -1, sizeof position_array);
				if (validity_check(words[word_pos], ch, position_array)) // checking whether input is correct or not
				{

					for (int i = 0; i < dash_number; i++)
					{
						if (position_array[i] != -1)
						{
							tracking_array[i] = 1;
							SDL_RenderCopy(renderer, chf, NULL, &dash[position_array[i]]);
						}
					}
					correct_ch_count++; // in case of correct answer
				}

				else
				{
					life_count++; // in case of wrong answer
				}

				SDL_RenderCopy(renderer, white, NULL, &life[6 - life_count]);
				SDL_RenderCopy(renderer, broken, NULL, &life[6 - life_count]);
				SDL_RenderPresent(renderer);
			}

			else
			{
				q = 0;
			}
		}
	}

	bool flag = 1;
	for (int i = 0; i < dash_number; i++)
	{
		if (tracking_array[i] == -1)
			flag = 0;
	}

	// evaluating and rendering the answer
	if (flag)
	{
		SDL_RenderCopy(renderer, correct, NULL, &ans);
	}
	else
	{
		SDL_RenderCopy(renderer, white, NULL, &life[0]);
		SDL_RenderCopy(renderer, broken, NULL, &life[0]);

		SDL_RenderCopy(renderer, incorrect, NULL, &ans);
	}

	memset(tracking_array, -1, sizeof tracking_array);
	SDL_RenderCopy(renderer, menuee, NULL, &menu);

	SDL_RenderCopy(renderer, Next_round, NULL, &next_round);

	SDL_RenderCopy(renderer, Correct_word_tex, NULL, &Correct_word);

	SDL_RenderPresent(renderer);

	return;
}

void logic_for_kids(SDL_Renderer *&renderer, TTF_Font *&font, bool &quit)
{
	// This function will be executed if the player chooses “Kids mode”. Here some characters of the word will be visible at first. This function will choose a random word and its clue from files and load the textures on the window. It will take input from the user, check the result and print the result accordingly.

	srand(time(0));
	FILE *fil;
	FILE *hin;
	fil = fopen("words", "r");
	if (fil == NULL)
	{
		printf("Failed\n");
	}

	hin = fopen("hints", "r");
	if (hin == NULL)
	{
		printf("Failed\n");
	}

	int word_count;

	fscanf(fil, "%d", &word_count);

	char words[word_count + 5][100];
	char hints[word_count + 5][150];
	for (int i = 0; i < word_count; i++)
	{
		fscanf(fil, "%s", words[i]); // fetching words from file
	}
	for (int i = 0; i < word_count; i++)
	{
		fscanf(hin, "%[^\n]%*c", hints[i]); // fetching hints from file
	}

	fclose(fil);
	fclose(hin);

	int word_pos = rand() % word_count;
	SDL_Rect Correct_word;

	Correct_word.x = 450;
	Correct_word.y = 350;
	Correct_word.h = 100;
	Correct_word.w = 250;
	SDL_Texture *Correct_word_tex = NULL;

	surface = TTF_RenderText_Solid(font, words[word_pos], {127, 0, 255});

	Correct_word_tex = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(font, hints[word_pos], {0, 0, 0});

	hinti = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, hinti, NULL, &hint);

	int dash_size = strlen(words[word_pos]);

	int x = rand() % dash_size;
	int y = rand() % dash_size;
	int z = rand() % dash_size;
	int dash_number = dash_size;

	char kids_word[dash_size];
	int tracking_array[dash_number];
	memset(tracking_array, -1, sizeof tracking_array);

	// rendering dash spaces along with some letters as hints
	for (int i = 0; i < dash_size; i++)
	{
		if (i == x || i == y || i == z)
		{
			kids_word[i] = '_';
		}
		else
		{
			kids_word[i] = words[word_pos][i];
			tracking_array[i] = 1;
		}
	}

	SDL_Texture *dashtex = NULL;
	SDL_Rect dash[dash_number];

	int dash_x_pos = 50;
	int dash_width = 40;
	for (int i = 0; i < dash_number; i++)
	{
		dash[i].w = dash_width;
		dash[i].h = (int)40;
		dash[i].x = dash_x_pos;
		dash_x_pos += 50;
		dash[i].y = 80;

		if (kids_word[i] == '_')
		{
			surface = TTF_RenderText_Solid(font, "_", {0, 0, 0});
			SDL_Texture *under_score = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_RenderCopy(renderer, under_score, NULL, &dash[i]);
		}
		else
		{
			char s[1];
			s[0] = kids_word[i];
			surface = TTF_RenderText_Solid(font, s, {0, 0, 0});
			SDL_Texture *under_score = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_RenderCopy(renderer, under_score, NULL, &dash[i]);
		}
	}
	surface = IMG_Load("Alphabet_image/23.png");

	heart = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(heart, NULL, NULL, &life[0].w, &life[0].h);
	int life_x_pos = 900;
	int life_width = life[0].w * .04;
	int life_height = life[0].h * .04;

	for (int i = 0; i < 5; i++)
	{
		life[i].w = (int)life_width;
		life[i].h = (int)life_height;
		life[i].x = life_x_pos;
		life_x_pos += life_width + 10;
		life[i].y = 80;
		SDL_RenderCopy(renderer, heart, NULL, &life[i]);
	}
	// loading textures on the window
	SDL_Texture *white = NULL;
	surface = IMG_Load("Alphabet_image/24.png");
	white = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Alphabet_image/22.png");

	SDL_Texture *broken = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	SDL_RenderPresent(renderer);

	int character_count = 0;
	int correct_ch_count = 0;
	int position_array[dash_number];

	int life_count = 1;

	char ager_char = '9';

	bool q = 1;

	// taking input from the user
	while (q)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
		{
			quit = true;
			q = 0;
			game = 0;
			return;
		}
		else if (e.type == SDL_KEYUP)
		{
			if (life_count < 5)
			{

				char ch = sdltocharacter();

				if (ch == '\\')
					break;

				char fh[1];
				fh[0] = ch;
				surface = TTF_RenderText_Solid(font, fh, {0, 0, 0});
				SDL_Texture *chf = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);

				memset(position_array, -1, sizeof position_array);
				if (validity_check(words[word_pos], ch, position_array)) // checking whether input is correct or not
				{

					for (int i = 0; i < dash_number; i++)
					{
						if (position_array[i] != -1)
						{
							tracking_array[i] = 1;
							SDL_RenderCopy(renderer, chf, NULL, &dash[position_array[i]]);
						}
					}
					correct_ch_count++; // in case of correct answer
				}

				else
				{
					life_count++; // in case of wrong answer
				}
				SDL_RenderCopy(renderer, white, NULL, &life[6 - life_count]);
				SDL_RenderCopy(renderer, broken, NULL, &life[6 - life_count]);
				SDL_RenderPresent(renderer);
			}

			else
			{
				q = 0;
			}
		}
	}

	bool flag = 1;
	for (int i = 0; i < dash_number; i++)
	{
		if (tracking_array[i] == -1)
			flag = 0;
	}

	// evaluating and rendering the answer
	if (flag)
	{
		SDL_RenderCopy(renderer, correct, NULL, &ans);
	}
	else
	{
		SDL_RenderCopy(renderer, white, NULL, &life[0]);
		SDL_RenderCopy(renderer, broken, NULL, &life[0]);
		SDL_RenderCopy(renderer, incorrect, NULL, &ans);
	}

	memset(tracking_array, -1, sizeof tracking_array);
	SDL_RenderCopy(renderer, Next_round, NULL, &next_round);

	SDL_RenderCopy(renderer, menuee, NULL, &menu);
	SDL_RenderCopy(renderer, Correct_word_tex, NULL, &Correct_word);
	SDL_RenderPresent(renderer);

	return;
}
