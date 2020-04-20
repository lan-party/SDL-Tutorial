// http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php

#include <iostream>
#include "SDL.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char * argv[]){

	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "=-=-= 1 =-=-=\n" << SDL_GetError();
	}else{
		window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL){
			cout << "=-=-= 2 =-=-=\n" << SDL_GetError();
		}else{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
