#include <stdio.h>

#include <SDLColor.h>
#include <SDLMetroLine.h>
#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>
#include <mathCalculation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLDraw.h>

#include <SDL.h>

/*
 * ─── FONCTIONS D"AFFICHAGE DE BACKGROUNDS ────────────────────────────────────────
 */


short SDLDisplayBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background){
   
    if((background->surface=SDL_CreateRGBSurfaceWithFormat(0, background->rect.w,background->rect.h, 32, SDL_PIXELFORMAT_RGBA8888))==NULL){
        fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if((SDL_FillRect(background->surface,&background->rect,SDL_MapRGBA(background->surface->format,255,255,255,255)))!=0){
        fprintf(stderr,"Echec lors du remplissage de la surface par un rectangle dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if((background->texture=SDL_CreateTextureFromSurface(mainRenderer,background->surface))==NULL){
        fprintf(stderr,"Echec lors de la convertion de la surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&background->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
    }
    SDL_RenderPresent(mainRenderer);

    return 1;
}


short SDLDisplayBackgroundLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDL_Window *mainWindow){
   
    SDL_Rect windowRect;

    SDL_GetWindowSize(mainWindow,&windowRect.w,&windowRect.h);
    windowRect=SDLChangeRect(0,0,windowRect.w,windowRect.h);

    if((background->texture=SDL_CreateTextureFromSurface(mainRenderer,background->surface))==NULL){
        fprintf(stderr,"Echec lors de la convertion de la surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&windowRect)!=0){
        return 0;
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
    }
    SDL_RenderPresent(mainRenderer);

    return 1;

}
