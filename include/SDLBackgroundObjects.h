#ifndef SDLBACKGROUNDOBJECTS
#define SDLBACKGROUNDOBJECTS

#include <SDLObjectsStructures.h>

#include <SDL.h>

/*
 * ─── FONCTIONS D"AFFICHAGE DE BACKGROUNDS ────────────────────────────────────────
 */

//Affiche le background dans le menu, ce dernier fait par défaut la taille de la fenêtre et a pour couleur la couleur blanche 
short SDLDisplayBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background);

//Affiche le background dans le menu, ce dernier a une taille adaptée aux conteneurs présent dans la fenêtre et a comme texture une image BitMap
short SDLDisplayBackgroundLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDL_Window *mainWindow);
#endif