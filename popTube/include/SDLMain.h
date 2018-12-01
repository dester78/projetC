#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>
#include <mysql.h>

    //Créer une fenêtre SDL grâce au paramètre windowFlag membre de la structure SDLConfig
    SDL_Window *SDLCreateMainWindow(long int windowFlag );

    
    SDL_Surface *SDLCreateHostMenu(SDL_Window* mainWindow );
    int SDLMainLoop(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles);
    

    //Fonction renvoyant les différents mode d'affichage présents sur l'écran numéro 1 du poste utilisateur
    SDL_DisplayMode *SDLGetArrayDisplayModes();
    
#endif