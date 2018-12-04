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

    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);//Récupère les dimensions de la fenêtre pour le centrage du conteneur
    
    if((containerHostMenu->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,wWindow/2,hWindow/1.1))!=NULL){
        
        if(SDL_SetRenderTarget(mainRenderer, containerHostMenu->texture)==0){
            if(SDL_SetRenderDrawColor(mainRenderer,containerHostMenu->color.r,containerHostMenu->color.g,containerHostMenu->color.b,containerHostMenu->color.a)==0){
                if(SDL_RenderClear(mainRenderer)==0){
                    if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
                        if(SDL_QueryTexture(containerHostMenu->texture, NULL, NULL, &containerHostMenu->rect.w, &containerHostMenu->rect.h)==0){
                            containerHostMenu->rect.x = (wWindow/2)-(containerHostMenu->rect.w/2);//Permet de centrer le conteneur horisontalement
                            containerHostMenu->rect.y = (hWindow/2)-(containerHostMenu->rect.h/2);//Pemet de centrer le conteneur verticalement
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

void SDLCreateTextButtonsHostMenu(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLButtons** buttonsHostMenu, char *fontPath, int *sizeArrayButtons){

    SDL_Color buttonColor={125,125,190,160};
    char arrayTextContent[4][12]={"","JOUER","PARAMETRES","QUITTER"};

    int wWindow;
    int hWindow;
    int wText;
    int hText;
    int sizeFont;

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

    SDL_Color color={1,1,1,255};

    for(int counterText=0; counterText<*sizeArrayButtons;counterText++){

       if((buttonsHostMenu[counterText]->text=malloc(sizeof(SDLText)))!=NULL){

            buttonsHostMenu[counterText]->text->color=color;
            buttonsHostMenu[counterText]->text->sizeFont=sizeFont;
            if((buttonsHostMenu[counterText]->text->font=TTF_OpenFont(fontPath,25))!=NULL){
                if((buttonsHostMenu[counterText]->text->surface=TTF_RenderText_Blended(buttonsHostMenu[counterText]->text->font,arrayTextContent[counterText],buttonsHostMenu[counterText]->text->color))!=NULL){
                    if((buttonsHostMenu[counterText]->text->texture=SDL_CreateTextureFromSurface(mainRenderer,buttonsHostMenu[counterText]->text->surface))!=NULL){
                        
                        buttonsHostMenu[counterText]->text->rect.w=buttonsHostMenu[counterText]->rect.w;
                        buttonsHostMenu[counterText]->text->rect.h=buttonsHostMenu[counterText]->rect.h;

                        if(SDL_QueryTexture(buttonsHostMenu[counterText]->text->texture, NULL, NULL, &buttonsHostMenu[counterText]->text->rect.w, &buttonsHostMenu[counterText]->text->rect.h)==0){
                            if(TTF_SizeText(buttonsHostMenu[counterText]->text->font,arrayTextContent[counterText],&wText,&hText)==0){
                                buttonsHostMenu[counterText]->text->rect.x=buttonsHostMenu[counterText]->rect.x+buttonsHostMenu[counterText]->rect.w/2 - wText/2;
                                buttonsHostMenu[counterText]->text->rect.y=buttonsHostMenu[counterText]->rect.y+buttonsHostMenu[counterText]->rect.h/2 - hText/2;
                                if(SDL_RenderCopy(mainRenderer,buttonsHostMenu[counterText]->text->texture,NULL,&buttonsHostMenu[counterText]->text->rect)==0){
                                    SDL_RenderPresent(mainRenderer);
                                }
                            }
                        }
                    }
                } 
            }
        } 
    }
}



void SDLCreateButtonsHostMenu(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, int *sizeArrayButtons, int connectionState){

    SDL_Color buttonColor={125,125,190,255};
    SDL_Color noConnectionColor={255,132,135,255};

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

    for(int counterButton=0;counterButton<*sizeArrayButtons;counterButton++){//Boucle permettant de créer des bouttons pour le menu d'accueil

        if((buttonsHostMenu[counterButton]=malloc(sizeof(SDLButtons)))!=NULL){

            if(counterButton==0){
                printf("%d",connectionState);
                buttonsHostMenu[counterButton]->color=connectionState==1?buttonColor:noConnectionColor;
            }
            else{
                buttonsHostMenu[counterButton]->color=buttonColor;
            }
            
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
    int dbConnectionStatus;
    
    dbConnectionStatus=(mysql_get_host_info(dbConnection)!=NULL);//Status de connexion vaut 1 si fonction retourne une valeur différente à NULL
    SDL_Event event;
    SDLContainer containerHostMenu;
    SDLButtons **buttonsHostMenu;

    SDL_Color color={255,255,255,255};

    sizeArrayButtons=4;
    
    buttonsHostMenu=malloc(sizeof(SDLButtons*)*sizeArrayButtons);

    SDL_SetRenderDrawColor(mainRenderer,255,170,28,125);
    SDL_RenderClear(mainRenderer);

    SDL_SetRenderTarget(mainRenderer,NULL);

    SDLCreateContainerHostMenu(mainWindow,mainRenderer,&containerHostMenu);
    SDLCreateButtonsHostMenu(mainWindow,mainRenderer,&containerHostMenu, buttonsHostMenu,&sizeArrayButtons,dbConnectionStatus);


    SDLCreateTextButtonsHostMenu(mainWindow,mainRenderer,buttonsHostMenu,SDLConfigElement->ttf->fontMenu, &sizeArrayButtons);

    while(windowLoop){

        

        SDL_PollEvent(&event);
        
        // printf("%d largeur, %d hauteur",wWindows,hWindows);
        switch(event.type){

            case SDL_QUIT : 
            windowLoop = 0;
            break;

            case SDL_MOUSEBUTTONUP: 
                if(event.button.x>=buttonsHostMenu[3]->rect.x && event.button.x<=buttonsHostMenu[3]->rect.w+buttonsHostMenu[3]->rect.x){
                    if(event.button.y>=buttonsHostMenu[3]->rect.y && event.button.y<=buttonsHostMenu[3]->rect.h+buttonsHostMenu[3]->rect.y){
                        event.type=SDL_QUIT;
                    }
                }
            break;
            
        }
    }

    
    return 0;
}

int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes){

    int modeNumber = SDL_GetNumDisplayModes(0);//Récupère le nombre de mode d'affichage disponibles sur l'écran principal de l'utilisateur 0 (écran principal)

    if (modeNumber < 0){

        fprintf(stderr,"Echec lors de la recuperation du nombre de modes (%s)\n",SDL_GetError());
    }

    else{

        if((*arrayDisplayModes=malloc(sizeof(SDL_DisplayMode*)*modeNumber))!=NULL){

            for (int modeCounter= 0 ; modeCounter < modeNumber ; modeCounter++){

                if (SDL_GetDisplayMode(0, modeCounter, ((*arrayDisplayModes)+modeCounter))< 0){//Affectation des modes d'affichage au tableau de modes d'affichage
                    
                    fprintf(stderr, "Echec lors de la recuperation du mode d'affichage (%s)\n", SDL_GetError());
                    return 0;
                }
            }  
             return modeNumber;
        }
        else{
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        } 
    }

    return 0;
}




