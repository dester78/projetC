#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>
#include <mysql.h>

    //Créer une fenêtre SDL grâce au paramètre windowFlag membre de la structure SDLConfig
    SDL_Window *SDLCreateMainWindow(long int windowFlag );
    SDL_Renderer *SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag);

    
    void SDLCreateContainerHostMenu(SDL_Window* mainWindow,SDL_Renderer *mainRenderer,SDL_Texture *containerHostMenuTexture);
    int SDLMainLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles);
    void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer,SDL_Texture *containerHostMenuTexture,SDLButtons** buttonsHostMenuTexture,int *sizeArrayButtons, char *fontPath);

    //Fonction renvoyant les différents mode d'affichage présents sur l'écran numéro 1 du poste utilisateur
    SDL_DisplayMode *SDLGetArrayDisplayModes();
    
#endif