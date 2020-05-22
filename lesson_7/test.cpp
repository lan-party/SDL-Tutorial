
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

bool Init();
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture * loadTexture(string path);
SDL_Window * gWindow = NULL;
SDL_Renderer * gRenderer = NULL;
SDL_Texture * gTexture = NULL;


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

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					cout << "=-=-= 4 =-=-=\n" << SDL_GetError();
					success = false;
				}
			}
		}
	}
	return success;
}

SDL_Texture * loadTexture(string path){
	SDL_Texture * newTexture = NULL;

	SDL_Surface * loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL){
		cout << "=-=-= 5 =-=-=\n" << SDL_GetError();
	}else{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL){
			cout << "=-=-= 6 =-=-=\n" << SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

bool loadMedia(){
	bool success = true;

	gTexture = loadTexture("texture.png");
	if(gTexture == NULL){
		cout << "=-=-= 7 =-=-=\n" << SDL_GetError();
		success = false;
	}
	
	return success;
}

void close(){
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
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

				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}
