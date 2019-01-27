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





// void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background){

//     if((background->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,background->rect.w,background->rect.h))!=NULL){
        
//         if(SDL_SetRenderTarget(mainRenderer, background->texture)==0){
//             if(SDL_SetRenderDrawColor(mainRenderer,background->color.r,background->color.g,background->color.b,background->color.a)==0){
//                 if(SDL_RenderClear(mainRenderer)==0){
//                     if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
//                         if(SDL_QueryTexture(background->texture, NULL, NULL, &background->rect.w, &background->rect.h)==0){

//                             if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&background->rect)==0){
//                                 SDL_RenderPresent(mainRenderer);
//                             }
//                             else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//                         }
//                         else{fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//                     } 
//                     else{fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//                 }
//                 else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//             } 
//             else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//         }
//         else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//     }
//     else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
// }


// void SDLUpdateBackgroundHostMenu(SDLBackground *background){

//     SDL_LockSurface(background);   
     
    

// }



