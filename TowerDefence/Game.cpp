#include "Game.h"


Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);


	window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * gridSize, height * gridSize, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (TTF_Init() == -1) {
		SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
	}

	font = TTF_OpenFont("BBHSansHegarty-Regular.ttf", 16);
	fontSmall = TTF_OpenFont("BBHSansHegarty-Regular.ttf", 12);
	if (!font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
	}

	
}

Game::~Game() {
	if (font) TTF_CloseFont(font);  
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

