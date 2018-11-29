#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>


    SDL_Window *SDLCreateMainWindow(long int windowFlag);
    SDL_Surface *SDLCreateHostMenu(SDL_Window* mainWindow);
    void SDLMainLoop(SDL_Window* mainWindow);
    
    SDL_DisplayMode *SDLGetArrayDisplayModes();
    // void SDLGetDisplayModes(SDL_DisplayMode *displayMode);


#endif