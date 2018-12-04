#include <stdio.h>
#include <stdlib.h>

#include <structures.h> 
#include <SDLMain.h>
#include <fileManager.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql.h>


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

    

    // printf(arrayDisplayModes[modeNumber-1].w);


    // if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1920,1080,windowConfigElement->windowFlag))!=NULL){    
    //     return mainWindow;
    // }

    // else{
    //     fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
    //     return NULL;
    // }
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



void SDLCreateContainerHostMenu(SDL_Window* mainWindow,SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu){

    int wWindow;
    int hWindow;

    SDL_Color containerColor={249,249,249,255};
    containerHostMenu->color=containerColor;

    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);
    
    if((containerHostMenu->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,wWindow/2,hWindow/1.1))!=NULL){
        
        if(SDL_SetRenderTarget(mainRenderer, containerHostMenu->texture)==0){
            if(SDL_SetRenderDrawColor(mainRenderer,containerHostMenu->color.r,containerHostMenu->color.g,containerHostMenu->color.b,containerHostMenu->color.a)==0){
                if(SDL_RenderClear(mainRenderer)==0){
                    if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
                        if(SDL_QueryTexture(containerHostMenu->texture, NULL, NULL, &containerHostMenu->rect.w, &containerHostMenu->rect.h)==0){
                            containerHostMenu->rect.x = (wWindow/2)-(containerHostMenu->rect.w/2);
                            containerHostMenu->rect.y = (hWindow/2)-(containerHostMenu->rect.h/2);
                            if(SDL_RenderCopy(mainRenderer,containerHostMenu->texture,NULL,&containerHostMenu->rect)==0){
                                 SDL_RenderPresent(mainRenderer);
                            }
                            else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                        }
                        else{fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                    } 
                    else{fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                }
                else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            } 
            else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
        }
        else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}

}


void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu,int *sizeArrayButtons, char *fontPath){

    SDL_Color buttonColor={125,125,190,160};

    int wWindow;
    int hWindow;
    double yButtonFactor;

    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);

    //Règle le placement vertical des boutons en fonction de l'affichage la fenêtre
    switch(hWindow){

        case 1080:
        yButtonFactor =1.3;
        break;

        case 1050:
        yButtonFactor=1.2;
        break;

        default:
        yButtonFactor=1;
    }

    for(int counterButton=0;counterButton<*sizeArrayButtons;counterButton++){

        if((buttonsHostMenu[counterButton]=malloc(sizeof(SDLButtons)))!=NULL){

            buttonsHostMenu[counterButton]->color=buttonColor;

            if((buttonsHostMenu[counterButton]->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,containerHostMenu->rect.w*0.8,containerHostMenu->rect.h*0.15))!=NULL){
                if(SDL_SetRenderTarget(mainRenderer,buttonsHostMenu[counterButton]->texture)==0){
                    if(SDL_SetRenderDrawColor(mainRenderer,buttonsHostMenu[counterButton]->color.r,buttonsHostMenu[counterButton]->color.g,buttonsHostMenu[counterButton]->color.b,buttonsHostMenu[counterButton]->color.a)==0){
                        if(SDL_RenderClear(mainRenderer)==0){
                            if(SDL_SetRenderTarget(mainRenderer,NULL)==0){
                                if(SDL_QueryTexture(buttonsHostMenu[counterButton]->texture, NULL, NULL, &buttonsHostMenu[counterButton]->rect.w, &buttonsHostMenu[counterButton]->rect.h)==0){

                                    buttonsHostMenu[counterButton]->rect.x=((buttonsHostMenu[counterButton]->rect.w/2)+((containerHostMenu->rect.x/2)*0.8));
                                    if(counterButton==0){
                                        buttonsHostMenu[counterButton]->rect.y=buttonsHostMenu[counterButton]->rect.h+containerHostMenu->rect.y;
                                    }
                                    else{
                                        buttonsHostMenu[counterButton]->rect.y=buttonsHostMenu[counterButton]->rect.h*yButtonFactor+buttonsHostMenu[counterButton-1]->rect.y;
                                    }

                                    if(SDL_RenderCopy(mainRenderer,buttonsHostMenu[counterButton]->texture,NULL,&buttonsHostMenu[counterButton]->rect)==0){
                                        SDL_RenderPresent(mainRenderer);
                                    }

                                    else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                                }
                                else{fprintf(stderr,"Echec lors de la recuperation des attribut de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                            }
                            else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                        }
                        else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                    }
                    else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                }
                else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            }
            else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
        }
        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);} 
    }    
}



int SDLMainLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files *arrayFiles){

    int windowLoop;
    int wWindow;
    int hWindow;
    int sizeArrayButtons; 

    SDL_Renderer *renderer;
    SDL_Event event;
    SDLContainer containerHostMenu;
    SDLButtons **buttonsHostMenu;
    SDL_Texture *textureMessage;
    SDL_Surface *message;
    
    TTF_Font *font;
    SDL_Color color={255,255,255,255};

    sizeArrayButtons=4;
    
    buttonsHostMenu=malloc(sizeof(SDLButtons*)*sizeArrayButtons);


    // font=TTF_OpenFont(SDLConfigElement->ttf->fontMenu,28);
    // message=TTF_RenderText_Solid(font,"Test",color);
    // textureMessage=SDL_CreateTextureFromSurface(mainRenderer,message);

    SDL_SetRenderDrawColor(mainRenderer,255,170,28,125);
    SDL_RenderClear(mainRenderer);

    SDL_SetRenderTarget(mainRenderer,NULL);

    SDLCreateContainerHostMenu(mainWindow,mainRenderer,&containerHostMenu);
    SDLCreateButtonsHostMenu(mainWindow,mainRenderer,&containerHostMenu, buttonsHostMenu,&sizeArrayButtons,SDLConfigElement->ttf->fontMenu);
    

    // SDL_QueryTexture(textureMessage, NULL, NULL, &position.w, &position.h);
    // position.x = (wWindow/2)-(position.w/2);
    // position.y = (hWindow/2)-(position.h/2);
    // SDL_RenderCopy(mainRenderer,textureMessage,NULL,NULL);
    // SDL_RenderPresent(mainRenderer);
    

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

int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes){

    int modeNumber = SDL_GetNumDisplayModes(0);

    if (modeNumber < 0){

        fprintf(stderr,"Echec lors de la recuperation du nombre de modes (%s)\n",SDL_GetError());
    }

    else{

        if((*arrayDisplayModes=malloc(sizeof(SDL_DisplayMode*)*modeNumber))!=NULL){

            for (int modeCounter= 0 ; modeCounter < modeNumber ; modeCounter++){

                if (SDL_GetDisplayMode(0, modeCounter, ((*arrayDisplayModes)+modeCounter))< 0){
                    
                    fprintf(stderr, "Echec lors de la recuperation du mode d'affichage (%s)\n", SDL_GetError());
                    return 0;
                }
             }     
        }

        else{
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }
    }
    return modeNumber;
}




