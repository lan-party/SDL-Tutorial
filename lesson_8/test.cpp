// https://lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

bool Init();
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window * gWindow = NULL;
SDL_Renderer * gRenderer = NULL;

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL){
				cout << "=-=-= 3 =-=-=\n" << SDL_GetError();
				success = false;
			}else{
				SDL_SetRenderDrawColor(gRenderer, 0x55, 0xEE, 0xFF, 0x11);

			}
		}
	}
	return success;
}


bool loadMedia(){
	bool success = true;
	
	return success;
}

void close(){

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

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

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x55, 0xFF, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);

				SDL_Rect outlinedRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
				//SDL_SetRenderDrawColor(gRenderer, 0x55, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &outlinedRect);

				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x55, 0x00, 0xFF);
				SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);
				SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);

				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				for(int a = 0; a < SCREEN_HEIGHT; a+=5){
					SDL_RenderDrawPoint(gRenderer, a, a);
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}
