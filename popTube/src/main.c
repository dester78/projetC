#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


int main(int argc, char *argv[]) {
     
    int status =  EXIT_FAILURE;
    SDL_Window *fenetre = NULL;
    SDL_Event event; 
     
    // Initialisation + vérification de la SDL : VIDEO.
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL : %s\n", SDL_GetError());
        goto quit;
    }
     
    // Création fenêtre.
    fenetre = SDL_CreateWindow("Tuto SDL 2.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(fenetre == NULL) {
        fprintf(stderr, "Impossible de créer la fenêtre : %s\n", SDL_GetError());
        goto quit;
    }
    
    do {
        SDL_WaitEvent(&event);
    }
    while(event.type != SDL_QUIT);
    SDL_DestroyWindow(fenetre); 
    status = EXIT_SUCCESS;
    
quit:
    // Quitter SDL.
    SDL_Quit();
     
    return status;
}