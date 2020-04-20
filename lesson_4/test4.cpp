// https://lazyfoo.net/tutorials/SDL/04_key_presses/index.php

#include <iostream>
#include "SDL.h"

using namespace std;

enum keyPressSurfaces{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool Init();
bool loadMedia();
void close();
SDL_Surface * loadSurface(string path); 	 

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window * gWindow = NULL;
SDL_Surface * gScreenSurface = NULL;
SDL_Surface * gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface * gCurrentSurface = NULL;

string loadMediaError = "=-=-= Error 4 =-=-=\nFailed to load one or more images.\n";


bool Init(){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "=-=-= Error 1 =-=-=\n" << SDL_GetError();
		success = false;
	}else{
		gWindow = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			cout << "=-=-= Error 2 =-=-=\n" << SDL_GetError();
			success = false;
		}else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

SDL_Surface * loadSurface(string path){
	SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL){
		cout << "=-=-= Error 3 =-=-=\n" << SDL_GetError();
	}
	return loadedSurface;
}

bool loadMedia(){
	bool success = true;
	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
		cout << loadMediaError;
		success = false;
	}
	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
		cout << loadMediaError;
		success = false;
	}
	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
		cout << loadMediaError;
		success = false;
	}
	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
		cout << loadMediaError;
		success = false;
	}
	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
		cout << loadMediaError;
		success = false;
	}

	return success;
}

void close(){
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char * argv[]){
	if(Init()){
		if(loadMedia()){
			bool quit = false;
			SDL_Event e;
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			
			while(!quit){
				while(SDL_PollEvent(&e) != 0){
					if(e.type == SDL_QUIT){
						quit = true;
					}
					else if(e.type = SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;
							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;
							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;
							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;
							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
						}
					}
				}
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	close();
	return 0;
}
