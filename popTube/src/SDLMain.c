#include <stdio.h>
#include <stdlib.h>

#include <structures.h> 
#include <SDLMain.h>
#include <fileManager.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql.h>


SDL_Window* SDLCreateMainWindow(long int windowFlag){

    SDL_Window  *mainWindow;

    if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,960,windowFlag))!=NULL){    
        return mainWindow;
    }

    else{
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return NULL;
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



void SDLCreateContainerHostMenu(SDL_Window* mainWindow,SDL_Renderer *mainRenderer,SDL_Texture *containerHostMenuTexture){

    int wWindow;
    int hWindow;

    SDL_Color backgroundColor={249,249,249,255};
    SDL_Rect position;

    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);

    if((containerHostMenuTexture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,wWindow/2,hWindow/1.1))!=NULL){
        
        if(SDL_SetRenderTarget(mainRenderer, containerHostMenuTexture)==0){
            if(SDL_SetRenderDrawColor(mainRenderer,backgroundColor.r,backgroundColor.g,backgroundColor.b,backgroundColor.a)==0){
                if(SDL_RenderClear(mainRenderer)==0){
                    if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
                        if(SDL_QueryTexture(containerHostMenuTexture, NULL, NULL, &position.w, &position.h)==0){

                            position.x = (wWindow/2)-(position.w/2);
                            position.y = (hWindow/2)-(position.h/2);
                            SDL_RenderCopy(mainRenderer,containerHostMenuTexture,NULL,&position);
                            SDL_RenderPresent(mainRenderer);
                        }
                        else{fprintf(stderr,"Échec lors de la perte du déciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                    } 
                    else{fprintf(stderr,"Échec lors du déciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                }
                else{fprintf(stderr,"Échec lors du remplissage de la texture par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            } 
            else{fprintf(stderr,"Échec lors du réglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
        }
        else{fprintf(stderr,"Échec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    else{fprintf(stderr,"Échec lors la création de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}

}


void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer,SDL_Texture *containerHostMenuTexture,SDLButtons** buttonsHostMenuTexture,int *sizeArrayButtons, char *fontPath){

    for(int counterButton=0;counterButton<*sizeArrayButtons;counterButton++){

        // buttonsHostMenuTexture[counterButton].

    }
}


int SDLMainLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles){

    int windowLoop;
    int wWindow;
    int hWindow;
    int sizeArrayButtons; 

    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture **containerHostMenuTexture;
    SDLButtons *buttonsHostMenuTexture;
    SDL_Texture *textureMessage;
    SDL_Surface *message;
    
    TTF_Font *font;
    SDL_Color color={255,255,255};
    
    buttonsHostMenuTexture=malloc(sizeof(SDLButtons)*sizeArrayButtons);

    font=TTF_OpenFont(SDLConfigElement->ttf->fontMenu,28);
    message=TTF_RenderText_Solid(font,"Test",color);
    textureMessage=SDL_CreateTextureFromSurface(mainRenderer,message);

    SDL_SetRenderDrawColor(mainRenderer,255,144,28,125);
    SDL_RenderClear(mainRenderer);

    SDL_SetRenderTarget(mainRenderer,NULL);

    SDLCreateContainerHostMenu(mainWindow,mainRenderer,containerHostMenuTexture);
    SDLCreateButtonsHostMenu(mainWindow,mainRenderer,containerHostMenuTexture, &buttonsHostMenuTexture,&sizeArrayButtons,SDLConfigElement->ttf->fontMenu);


    
    

    // SDL_QueryTexture(textureMessage, NULL, NULL, &position.w, &position.h);
    // position.x = (wWindow/2)-(position.w/2);
    // position.y = (hWindow/2)-(position.h/2);
    SDL_RenderCopy(mainRenderer,textureMessage,NULL,NULL);
    SDL_RenderPresent(mainRenderer);
    


    // if(renderer=SDL_CreateRenderer(mainWindow))
    // // SDL_DisplayMode *displayMode;
    

    // hostMenu=SDL_CreateRGBSurface(SDL_RENDERER_ACCELERATED,wWindow/2,hWindow/2,32,0,0,0,0);


    // SDL_Surface *buttonSurface; 
    // SDL_Color color;


    // SDLGetDisplayModes(displayMode);


    // printf("%p",SDL_GetWindowPixelFormat(*mainWindow));

    //SDL_FillRect(mainWindow, NULL, SDL_MapRGB(32, 238, 238, 238));
    while(windowLoop){

        

        SDL_PollEvent(&event);
        
        // printf("%d largeur, %d hauteur",wWindows,hWindows);
        switch(event.type){

            case SDL_QUIT : 
            windowLoop = 0;
            break;
            
        }
    }

    printf("%s",__func__);
    return 0;
}

SDL_DisplayMode *SDLGetArrayDisplayModes(){

    SDL_DisplayMode *arrayDisplayModes;

    int modeNumber = SDL_GetNumDisplayModes(0);

    if (modeNumber < 0){

        fprintf(stderr,"Échec lors de la récupération du nombre de modes (%s)\n",SDL_GetError());
    }

    else{

        if((arrayDisplayModes=malloc(sizeof(SDL_DisplayMode*)*modeNumber))!=NULL){

            for (int modeCounter= 0 ; modeCounter < modeNumber ; modeCounter++){

                if (SDL_GetDisplayMode(0, modeCounter, (arrayDisplayModes+modeCounter))< 0){
                    fprintf(stderr, "Échec lors de la récupération du mode d'affichage (%s)\n", SDL_GetError());
                }
             }
             return arrayDisplayModes;
        }

        else{
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }
    }
    return NULL;
}




