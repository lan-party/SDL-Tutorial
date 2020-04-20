// https://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php

#include <iostream>
#include "SDL.h"

using namespace std;

bool Init();
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window * gWindow = NULL;
SDL_Surface * gScreenSurface = NULL;
SDL_Surface * gHelloWorld = NULL;

bool Init(){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "=-=-= 1 =-=-=\n" << SDL_GetError();
		success = false;
	}else{
		gWindow = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			cout << "=-=-= 2 =-=-=\n" << SDL_GetError();
			success = false;
		}else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia(){
	bool success = true;

	gHelloWorld = SDL_LoadBMP("brick2.bmp");
	if(gHelloWorld == NULL){
		cout << "=-=-= 3 =-=-=\n" << SDL_GetError();
		success = false;
	}
	return success;
}

void close(){
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char * argv[]){
	if(Init()){
		if(loadMedia()){

			bool quit = false;
			SDL_Event e;

			while(!quit){
				while(SDL_PollEvent(&e) != 0){
					if(e.type == SDL_QUIT){
						quit = true;
					}
				}
			}
			
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			SDL_Delay(2000);
		}
	}

	close();
	return 0;
}
