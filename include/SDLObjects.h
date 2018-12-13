#ifndef SDLOBJECTS
#define SDLOBJECTS

#include <SDLObjectsStructures.h>
#include <SDLConfigStructures.h>

#include <SDL.h>


    //Créer une fenetre SDL grâce au paramètre windowFlag membre de la structure SDLConfig, 
    //si les dimensions de la fênetre de jeu ne sont pas placées dans le fichier configuration elle prend les dimensions courantes de la fenêtre utilisateur
    SDL_Window* SDLCreateMainWindow(SDLWindowConfig *windowConfigElement);

    //Créer un renderer en fonction des flags stockés dans la structure SDLRendererConfig enfant de SDLConfig
    SDL_Renderer *SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag);

    void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer,SDLBackground *background);

    //Fonction créant un conteneur pour le menu principal
    void SDLCreateContainerHostMenu(SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu);

    //Fonction intégrant les boutons du menu principal
    void SDLCreateButton(SDL_Renderer *mainRenderer,SDLButtons* button);

    //Fonction appliquant du texte aux bouttons du menu principal
    void SDLCreateTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu);

    void SDLCreateMetroStation(MetroStation *metroStation);


#endif