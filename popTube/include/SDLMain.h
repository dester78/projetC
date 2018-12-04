#ifndef SDLMAIN
#define SDLMAIN
#include <SDL.h>
#include <structures.h>
#include <mysql.h>

    //Créer une fenetre SDL grâce au paramètre windowFlag membre de la structure SDLConfig, 
    //si les dimensions de la fênetre de jeu ne sont pas placées dans le fichier configuration elle prend les dimensions courantes de la fenêtre utilisateur
    SDL_Window* SDLCreateMainWindow(SDLWindowConfig *windowConfigElement);

    //Créer un renderer en fonction des flags stockés dans la structure SDLRendererConfig enfant de SDLConfig
    SDL_Renderer *SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag);

    //Fonction créant un conteneur pour le menu principal
    void SDLCreateContainerHostMenu(SDL_Window* mainWindow,SDL_Renderer *mainRenderer,SDLContainer *containerHostMenuTexture);

    //Fonction intégrant les boutons du menu principal
    void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, int *sizeArrayButtons, int connectionState);
    
    //Fonction appliquant du texte aux bouttons du menu principal
    void SDLCreateTextButtonsHostMenu(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLButtons** buttonsHostMenu, char *fontPath, int *sizeArrayButtons);
    

    int SDLMainLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles);

    //Fonction modifiant un tableau en y intégrant les différents modes d'affichage disponibles sur l'écran 1 de l'utilisteur, elle retourne le nombre de mode disponibles
    int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes);
    
#endif