#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>
#include <mysql.h>


    SDL_Window *SDLCreateMainWindow(long int windowFlag );
    SDL_Surface *SDLCreateHostMenu(SDL_Window* mainWindow );
    int SDLMainLoop(SDL_Window* mainWindow, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles);
    
    SDL_DisplayMode *SDLGetArrayDisplayModes();
    // void SDLGetDisplayModes(SDL_DisplayMode *displayMode);


#endif