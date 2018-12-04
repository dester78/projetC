#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>
#include <mysql.h>

    //Crer une fenetre SDL grâce au paramètre windowFlag membre de la structure SDLConfig
    SDL_Window* SDLCreateMainWindow(SDLWindowConfig *windowConfigElement);
    SDL_Renderer *SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag);

    
    void SDLCreateContainerHostMenu(SDL_Window* mainWindow,SDL_Renderer *mainRenderer,SDLContainer *containerHostMenuTexture);
    void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu,int *sizeArrayButtons, char *fontPath);

    int SDLMainLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles);


    //Fonction renvoyant les differents mode d'affichage presents sur l'ecran numero 1 du poste utilisateur
    int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes);
    
#endif