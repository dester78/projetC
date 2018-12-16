#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRIANGLE 3
#define SQUARE 2 
#define CIRCLE 1


#include <SDLDraw.h>
#include <fileManager.h>
#include <SDLObjectsStructures.h>
#include <SDLConfigStructures.h>


#include <SDL.h>


void initButtonsHostMenu(SDL_Window  **mainWindow, SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, unsigned short *sizeArrayButtons, short connectionState){

    int wWindow;
    int hWindow;
    double yButtonFactor;
    
    SDL_GetWindowSize(*mainWindow,&wWindow,&hWindow);

    //Règle le placement vertical des boutons en fonction de l'affichage la fenêtre
    switch(hWindow){

        case 1080:
        yButtonFactor =1.3;
        break;

        case 1050:
        yButtonFactor=1.2;
        break;

        default :
        yButtonFactor=1;
        break;

    }

    for(unsigned short counterButton=0;counterButton<*sizeArrayButtons;counterButton++){//Boucle permettant de créer des bouttons pour le menu d'accueil

        switch(counterButton){

            case 0 : 
                buttonsHostMenu[counterButton]->color=connectionState==1?SDLChangeRGBColor(242,201,49,255):SDLChangeRGBColor(0,0,0,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("CONNEXION") + 1)))!=NULL){
                    strcpy(buttonsHostMenu[counterButton]->text->content,"CONNEXION");
                }
            break;

            case 1 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(137,199,214,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("JOUER") + 1)))!=NULL){
                    strcpy(buttonsHostMenu[counterButton]->text->content,"JOUER");
                }
            break;

            case 2 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(50,142,91,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("PARAMETRES") + 1)))!=NULL){
                    strcpy(buttonsHostMenu[counterButton]->text->content,"PARAMETRES");
                }
            break;
            
            case 3 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(222,139,83,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("QUITTER") + 1)))!=NULL){
                    strcpy(buttonsHostMenu[counterButton]->text->content,"QUITTER");
                }
            break;        
        }
        

        buttonsHostMenu[counterButton]->rect.w=containerHostMenu->rect.w/1.32;
        buttonsHostMenu[counterButton]->rect.h=containerHostMenu->rect.h*0.15;
        buttonsHostMenu[counterButton]->rect.x=((containerHostMenu->rect.x)+((containerHostMenu->rect.x)/2));

        buttonsHostMenu[counterButton]->text->fontPath=malloc(sizeof(char)*(strlen(fontPath)+1));
        strcpy(buttonsHostMenu[counterButton]->text->fontPath,fontPath);
        buttonsHostMenu[counterButton]->text->color=SDLChangeRGBColor(255,255,255,255);
        buttonsHostMenu[counterButton]->text->sizeFont=60;
        buttonsHostMenu[counterButton]->text->rect.w=buttonsHostMenu[counterButton]->rect.w;
        buttonsHostMenu[counterButton]->text->rect.h=buttonsHostMenu[counterButton]->rect.h;

        if(counterButton==0){
            buttonsHostMenu[counterButton]->rect.y=buttonsHostMenu[counterButton]->rect.h+containerHostMenu->rect.y;
        }
        else{
            buttonsHostMenu[counterButton]->rect.y=buttonsHostMenu[counterButton]->rect.h*yButtonFactor+buttonsHostMenu[counterButton-1]->rect.y;
        }
    }
}


void initContainerHostMenu(SDL_Window** mainWindow,SDLContainer *containerHostMenu){

    int wWindow;
    int hWindow;

    SDL_Color containerColor={249,249,249,0};
    containerHostMenu->color=containerColor;

    SDL_GetWindowSize(*mainWindow,&wWindow,&hWindow);//Récupère les dimensions de la fenêtre pour le centrage du conteneur

    containerHostMenu->rect.w = wWindow/1.5;
    containerHostMenu->rect.h = hWindow/1.1;
    containerHostMenu->rect.x = (wWindow/2)-(containerHostMenu->rect.w/2);//Permet de centrer le conteneur horizontalement
    containerHostMenu->rect.y = (hWindow/2)-(containerHostMenu->rect.h/2);//Pemet de centrer le conteneur verticalement
}

void initBackgroundHostMenu(SDL_Window **mainWindow,SDLBackground **backgroundHostMenu){
    
    int wWindow;
    int hWindow;

    SDL_Color backgroundColor={0,0,0,255};
    (*backgroundHostMenu)->color=backgroundColor;
    (*backgroundHostMenu)->sizeArrMetroStations=0;

    SDL_GetWindowSize(*mainWindow,&wWindow,&hWindow);

    (*backgroundHostMenu)->rect.w = wWindow;
    (*backgroundHostMenu)->rect.h = hWindow;
    (*backgroundHostMenu)->rect.x = 0;
    (*backgroundHostMenu)->rect.y = 0;


}

void initMetroStation(MetroStation *metroStation, unsigned short geometricShape, SDL_Rect rect, unsigned short maxSize, Uint32 color){

    metroStation->rect=rect;

    rect.x=0;
    rect.y=0;

    switch(geometricShape){

        case TRIANGLE : 
            metroStation->triangle=initTriangle(rect,maxSize);
        break; 

        case CIRCLE : 
            rect.x=rect.w/2;
            rect.y=rect.h/2;
            metroStation->circle=initCircle(rect,maxSize);
        break;

        case SQUARE : 
            metroStation->square=initSquare(rect,maxSize);
        break;
    }

    metroStation->maxSize=maxSize;
    metroStation->overlapRisk=0;
    metroStation->geometricShape=geometricShape;
    metroStation->color=color;
}

Triangle initTriangle(SDL_Rect rect, unsigned short maxSize){

    Triangle triangle; 

    triangle.rect.w=rect.w;
    triangle.rect.x=rect.x;
    triangle.rect.y=rect.w;
    triangle.rect.h=0;

    triangle.maxSize=maxSize;

    return triangle;

}

Square initSquare(SDL_Rect rect, unsigned short maxSize){
    
    Square square; 

    square.rect=rect;
    square.maxSize=maxSize;

    return square;

}

Circle initCircle(SDL_Rect rect, unsigned short maxSize){

    Circle circle;

    circle.radius=rect.w/2;
    circle.maxRadius=maxSize/2;
    circle.xCenter=rect.x;
    circle.yCenter=rect.y;

    return circle;

}

void freeSDLButton(SDLButtons *sdlButtonElement){

    SDL_DestroyTexture(sdlButtonElement->texture);
    freeSDLText(sdlButtonElement->text);

}


void freeSDLText(SDLText *sdlTextElement){

    free(sdlTextElement->content);
    SDL_DestroyTexture(sdlTextElement->texture);
    TTF_CloseFont(sdlTextElement->font);
}

