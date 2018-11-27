#include <stdio.h>
#include <stdlib.h>

#include <structures.h> 
#include <SDLMain.h>

#include <SDL.h>
// #include <SDL_ttf.h>


SDL_Window *SDLCreateMainWindow(SDLConfig *SDLConfigElement){

SDL_Window* mainWindow;
// SDL_Renderer *renderer;

    mainWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,960,SDLConfigElement->window->windowFlag);
    // enderer = SDL_CreateRenderer(mainWind, -1, 0);

    if(mainWindow!=NULL){    
        return mainWindow;
    }

    else{
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return NULL;
    }
}

// SDL_Surface *SDLCreateHostMenu(SDL_Window* mainWindow){

//     int wWindow;
//     int hWindow;
//     SDL_Surface *hostMenu;
//     SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);
//     hostMenu=SDL_CreateRGBSurface(SDL_RENDERER_ACCELERATED,wWindow/2,hWindow/2,32,0,0,0,0);


// }


void SDLMainLoop(SDL_Window* mainWindow){

int windowLoop;
// SDL_DisplayMode *displayMode;
SDL_Event event;

    // SDLGetDisplayModes(displayMode);
    while(windowLoop){


        SDL_PollEvent(&event);
        
        // printf("%d largeur, %d hauteur",wWindows,hWindows);
        switch(event.type){

            case SDL_QUIT : 
            windowLoop = 0;
            break;
            
        }
    }
}

// void SDLGetDisplayModes(SDL_DisplayMode *displayMode){

//     int modeNumber = SDL_GetNumDisplayModes(0);

//     if (modeNumber < 0){

//     fprintf(stderr,"Échec lors de la récupération du nombre de modes (%s)\n",SDL_GetError());
//     }

//     fprintf(stdout,"Il y a %d mode(s) d'affichage", modeNumber);

//     for (int modeCounter= 0 ; modeCounter < modeNumber ; modeCounter++){

//         if (SDL_GetDisplayMode(0, modeCounter, displayMode)< 0){
//             fprintf(stderr, "Échec lors de la récupération du mode d'affichage (%s)\n", SDL_GetError());
//         }

//         fprintf(stdout, "Mode %d : %dx%dx%d\n", modeCounter, displayMode->w, displayMode->h, displayMode->refresh_rate);
//     }

// }




