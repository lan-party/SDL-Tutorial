// https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

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
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)){
				cout << "=-=-= 3 =-=-=\n" << IMG_GetError();
				success = false;
			}else{
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadMedia(){
	bool success = true;

	gHelloWorld = IMG_Load("test.jpg");
	if(gHelloWorld == NULL){
		cout << "=-=-= 4 =-=-=\n" << SDL_GetError();
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


			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);

			while(!quit){
				while(SDL_PollEvent(&e) != 0){
					if(e.type == SDL_QUIT){
						quit = true;
					}
				}
			}
		}
	}

	close();
	return 0;
}
