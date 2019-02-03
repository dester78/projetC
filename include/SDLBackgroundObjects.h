#ifndef SDLBACKGROUNDOBJECTS
#define SDLBACKGROUNDOBJECTS

#include <SDLObjectsStructures.h>

#include <SDL.h>

void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background);
void SDLCreateBackgroundLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDL_Window *mainWindow);
#endif