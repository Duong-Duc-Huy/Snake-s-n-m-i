#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

const int step = 25;
const int SCREEN_WIDTH = 1150;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);

#endif // SDL_H_INCLUDED

