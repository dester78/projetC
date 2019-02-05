#include <stdio.h>

#include <SDLConfigStructures.h>
#include <SDLObjects.h>

#include <SDL.h>




SDL_Window* SDLCreateMainWindow(SDLWindowConfig *windowConfigElement){

    SDL_Window  *mainWindow;
    SDL_DisplayMode currentDisplayMode;

    if(windowConfigElement->windowHeight>0&&windowConfigElement->windowWidth>0){
        if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowConfigElement->windowWidth,windowConfigElement->windowHeight,windowConfigElement->windowFlag))!=NULL){    
            return mainWindow;
        }
        else{
            fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
            return NULL;
        }
    }

    else{
        if(SDL_GetCurrentDisplayMode(0,&currentDisplayMode)==0){
            if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,currentDisplayMode.w,currentDisplayMode.h,windowConfigElement->windowFlag))!=NULL){   
                windowConfigElement->windowWidth=currentDisplayMode.w;
                windowConfigElement->windowHeight=currentDisplayMode.h;
                return mainWindow;
            }
            else{
                fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
                return NULL;
            }
        }
        else{
            fprintf(stderr,"Erreur lors du chargement des modes d'affichage");
            return NULL;
        }
    }
}

SDL_Renderer* SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag){

    SDL_Renderer  *mainRenderer;

    if((mainRenderer=SDL_CreateRenderer(mainWindow,-1,rendererFlag))!=NULL){    
        return mainRenderer;
    }

    else{
        fprintf(stderr,"Erreur de mise en place de moteur de rendu : %s\n",SDL_GetError());
        return NULL;
    }
}

