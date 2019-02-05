#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDLObjectsStructures.h>
#include <SDLColor.h>
#include <SDLDraw.h>
#include <SDLRectPoint.h>
#include <fileManager.h>
#include <SDLConfigStructures.h>
#include <fileManager.h>
#include <mathCalculation.h>


#include <SDL.h>
#include <SDL_image.h>
#include <mysql.h>


/*
 * ─── FONCTIONS D'INITIALISATION DE STRUCTURES ────────────────────────────────────
 */

SDLEnvironment *initSDLEnvironment( SDL_Window *mainWindow,SDL_Renderer *mainRenderer){

    SDLEnvironment *environment;

    if((environment=malloc(sizeof(SDLEnvironment)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    
    environment->timer=NULL;
    environment->background=NULL;
    environment->gui=NULL;
    environment->level=NULL;
    environment->mainRenderer=mainRenderer;
    environment->mainWindow=mainWindow;

    return environment;
}
SDLGUI *initGUIHostMenu(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement,MYSQL *dbConnection){ 

    SDLGUI *guiHostMenu;
    short connectionState=(mysql_get_host_info(dbConnection)!=NULL);//Status de connexion vaut 1 si fonction retourne une valeur différente à NULL

    if((guiHostMenu=malloc(sizeof(SDLGUI)))==NULL){
        createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    guiHostMenu->rightContainer=NULL;
    guiHostMenu->leftContainer=NULL;
    if((guiHostMenu->container=initContainer(mainWindow,_CENTER_,4))==NULL){
        createErrorReport("Echec lors de l'initialisation d'un conteneur",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL; 
    }

    if(initButtonsHostMenu(guiHostMenu->container,guiHostMenu->container->arrayButtons,SDLConfigElement->ttf->fontMenu,guiHostMenu->container->sizeArrayButtons,connectionState)==0){
        createErrorReport("Echec lors de l'initialisation des boutons d'un conteneur du menu",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }  
    return guiHostMenu;
}


SDLGUI *initGUILevel(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement){

    SDLGUI *guiLevel;

    if((guiLevel=malloc(sizeof(SDLGUI)))==NULL){
        createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL; 
    }
    if((guiLevel->leftContainer=initContainer(mainWindow,_LEFT_,2))==NULL){
        createErrorReport("Echec lors de l'initialisation d'un conteneur",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL; 
    }
    return guiLevel;
}


SDLTimer *initTimer(int refreshFrequency){

    SDLTimer *timer;

    if((timer=malloc(sizeof(SDLTimer)))==NULL){
        createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL; 
    }
    timer->refreshCurrentTime=SDL_GetTicks();
    timer->refreshFrequency=refreshFrequency;
    timer->refreshPastTime=timer->refreshCurrentTime;
    timer->clickTime=timer->refreshCurrentTime;
    return timer;
}

short initButtonsHostMenu( SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, unsigned short sizeArrayButtons, short connectionState){

    for(unsigned short counterButton=0;counterButton<sizeArrayButtons;counterButton++){//Boucle permettant de créer des bouttons pour le menu d'accueil

        switch(counterButton){

            case 0 : 
                buttonsHostMenu[counterButton]->color=connectionState==1?SDLChangeRGBColor(242,201,49,255):SDLChangeRGBColor(0,0,0,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("CONNEXION") + 1)))==NULL){
                    createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0; 
                }
                strcpy(buttonsHostMenu[counterButton]->text->content,"CONNEXION");
            break;

            case 1 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(137,199,214,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("JOUER") + 1)))==NULL){
                    createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;  
                }
                strcpy(buttonsHostMenu[counterButton]->text->content,"JOUER");
            break;

            case 2 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(50,142,91,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("PARAMETRES") + 1)))==NULL){
                    createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0; 
                }
                strcpy(buttonsHostMenu[counterButton]->text->content,"PARAMETRES");
            break;
            
            case 3 : 
                buttonsHostMenu[counterButton]->color=SDLChangeRGBColor(222,139,83,255);
                if((buttonsHostMenu[counterButton]->text->content=malloc(sizeof(char)*(strlen("QUITTER") + 1)))==NULL){
                    createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0; 
                }
                strcpy(buttonsHostMenu[counterButton]->text->content,"QUITTER");
            break;        
        }
        
        buttonsHostMenu[counterButton]->hover=0;
        buttonsHostMenu[counterButton]->display=0;
        buttonsHostMenu[counterButton]->rect.w=containerHostMenu->rect.w/1.5;
        buttonsHostMenu[counterButton]->rect.h=containerHostMenu->rect.h*0.20;
        marginAuto(&containerHostMenu->rect,&containerHostMenu->arrayButtons[counterButton]->rect,0,1,_X_);

        if((buttonsHostMenu[counterButton]->text->fontPath=malloc(sizeof(char)*(strlen(fontPath)+1)))==NULL){
            createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
        strcpy(buttonsHostMenu[counterButton]->text->fontPath,fontPath);
        buttonsHostMenu[counterButton]->text->color=SDLChangeRGBColor(255,255,255,255);
        buttonsHostMenu[counterButton]->text->sizeFont=60;
        buttonsHostMenu[counterButton]->text->rect.w=buttonsHostMenu[counterButton]->rect.w;
        buttonsHostMenu[counterButton]->text->rect.h=buttonsHostMenu[counterButton]->rect.h;
        marginAuto(&containerHostMenu->rect,&containerHostMenu->arrayButtons[counterButton]->rect,counterButton,containerHostMenu->sizeArrayButtons,_Y_);
    }
    return 1;
}



short initButtonSideContainerLevel(SDLContainer *container, ContainerPosition containerPosition,  char *fontPath, SDLBackground *backgroundLevel){

    for(unsigned short counterButton=0; counterButton<container->sizeArrayButtons; counterButton++){

        switch(containerPosition){
            case _LEFT_:               
                switch(counterButton){
                    case 0:
                        if((container->arrayButtons[counterButton]->surface=IMG_Load("img/loco60x60.png"))==NULL){
                            createErrorReport("Echec lors du chargement d'une image",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                        container->arrayButtons[counterButton]->buttonName=_ENGINE_BTN_;
                        if((container->arrayButtons[counterButton]->text->content=malloc(sizeof(char)*backgroundLevel->sizeArrEngine))==NULL){
                            createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                    break;
                    case 1:
                        if((container->arrayButtons[counterButton]->surface=IMG_Load("img/railcar60x60.png"))==NULL){
                            createErrorReport("Echec lors du chargement d'une image",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                        container->arrayButtons[counterButton]->buttonName=_CAR_BTN_;
                        if((container->arrayButtons[counterButton]->text->content=malloc(sizeof(char)*backgroundLevel->sizeArrCar))==NULL){
                            createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                    break;               
                }               
                container->arrayButtons[counterButton]->insideColor=SDLChangeRGBColor(255,255,255,255);
                container->arrayButtons[counterButton]->color=container->arrayButtons[counterButton]->insideColor;
                container->arrayButtons[counterButton]->rect.w=diamCircumscribeCircleOnRect(container->arrayButtons[counterButton]->surface->w,container->arrayButtons[counterButton]->surface->h);
                container->arrayButtons[counterButton]->rect.h=container->arrayButtons[counterButton]->rect.w;
                marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,0,0,_X_);
                marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,counterButton,container->sizeArrayButtons,_Y_);
                container->arrayButtons[counterButton]->display=1;    

            break;            
            case _RIGHT_:
                switch(counterButton){
                    case 0:
                        container->arrayButtons[counterButton]->buttonName=_PLAY_;
                        if((container->arrayButtons[counterButton]->surface=IMG_Load("img/play40x40.png"))==NULL){
                            createErrorReport("Echec lors du chargement d'une image",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                        container->arrayButtons[counterButton]->insideColor=SDLChangeRGBColor(8,133,0,255);
                    break;

                    case 1:
                        container->arrayButtons[counterButton]->buttonName=_PAUSE_;
                        if((container->arrayButtons[counterButton]->surface=IMG_Load("img/pause40x40.png"))==NULL){
                            createErrorReport("Echec lors du chargement d'une image",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }   
                        container->arrayButtons[counterButton]->insideColor=SDLChangeRGBColor(243,232,71,255);
                    break;

                    case 2:
                        container->arrayButtons[counterButton]->buttonName=_FASTER_;
                        if((container->arrayButtons[counterButton]->surface=IMG_Load("img/faster40x40.png"))==NULL){
                            createErrorReport("Echec lors du chargement d'une image",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                        container->arrayButtons[counterButton]->insideColor=SDLChangeRGBColor(33,68,162,255);
                    break;

                    default:
                        container->arrayButtons[counterButton]->insideColor=backgroundLevel->arrMetroLinesColor[counterButton-3];
                        container->arrayButtons[counterButton]->metroLine=backgroundLevel->arrMetroLines[counterButton-3];
                        if(counterButton-3<backgroundLevel->countUnlockMetroLine){
                            container->arrayButtons[counterButton]->display=1;    
                        }
                    break;
                }
                           
                if(counterButton<3){
                    container->arrayButtons[counterButton]->rect.w=diamCircumscribeCircleOnRect(container->arrayButtons[counterButton]->surface->w,container->arrayButtons[counterButton]->surface->h);
                    container->arrayButtons[counterButton]->rect.h=container->arrayButtons[counterButton]->rect.w;
                    marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,0,backgroundLevel->sizeArrMetroLinesColor,_Y_);
                    marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,counterButton,3,_X_); 
                    container->arrayButtons[counterButton]->display=1;    

                }
                else{    
                    container->arrayButtons[counterButton]->rect.w=container->arrayButtons[counterButton-1]->rect.w;
                    container->arrayButtons[counterButton]->rect.h=container->arrayButtons[counterButton]->rect.w;
                    marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,0,1,_X_);
                    marginAuto(&container->rect,&container->arrayButtons[counterButton]->rect,counterButton-1,backgroundLevel->sizeArrMetroLinesColor+3,_Y_);
                }
                container->arrayButtons[counterButton]->color=SDLChangeRGBColor(255,255,255,255);
            break;
            default : 
            break;
        }   
        
        container->arrayButtons[counterButton]->savedColor=container->arrayButtons[counterButton]->insideColor;
        container->arrayButtons[counterButton]->selected=0;
    }
    return 1;
}

SDLContainer *initContainer(SDL_Window *mainWindow, ContainerPosition containerPosition,unsigned short sizeArrayButtons){


    SDLContainer *container;
    int wWindow,hWindow;

    if((container=malloc(sizeof(SDLContainer)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    container->color=SDLChangeRGBColor(20,20,20,50);
    container->sizeArrayText=0;
    
    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);//Récupère les dimensions de la fenêtre pour le centrage du conteneur

    switch(containerPosition){
        case _CENTER_:
            container->sizeArrayButtons=sizeArrayButtons;
            container->rect.w=wWindow/1.5;
            container->rect.h = hWindow/1.5;
            container->rect.x = (wWindow/2)-(container->rect.w/2);//Permet de centrer le conteneur horizontalement
            container->rect.y = (hWindow/2)-(container->rect.h/2);//Pemet de centrer le conteneur verticalement
            // container->rect=SDLChangeRect (wWindow/2 - (wWindow/1.5)/2,hWindow/2 - (hWindow/1.1)/2, wWindow/1.5,wWindow/1.1);
        break;
        case _LEFT_:
            container->sizeArrayButtons=sizeArrayButtons;
            container->rect.w=wWindow/10;
            container->rect.h = hWindow/1.5;
            container->rect.x = 0;
            container->rect.y = (hWindow/2)-(container->rect.h/2);
        break;
        case _RIGHT_:
            container->sizeArrayButtons=sizeArrayButtons;
            container->sizeArrayText=2;
            container->rect.w=wWindow/10;
            container->rect.h = hWindow/1.5;
            container->rect.x = wWindow-container->rect.w;
            container->rect.y = (hWindow/2)-(container->rect.h/2);
        break;
    }

    if(container->sizeArrayButtons!=0){
        if((container->arrayButtons=malloc(sizeof(SDLButtons*)*container->sizeArrayButtons))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        for(unsigned short counterButton=0; counterButton<container->sizeArrayButtons; counterButton++){
            
            if((container->arrayButtons[counterButton]=malloc(sizeof(SDLButtons)))==NULL){
                createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                return NULL;
            }
            container->arrayButtons[counterButton]->surface=NULL;
            container->arrayButtons[counterButton]->texture=NULL;
            container->arrayButtons[counterButton]->backgroundSurface=NULL;
            container->arrayButtons[counterButton]->backgroundTexture=NULL;
            container->arrayButtons[counterButton]->display=0;
            if((container->arrayButtons[counterButton]->text=malloc(sizeof(SDLText)))==NULL){
                createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
                return NULL;
            }
        } 
    }
    return container;
}

SDLBackground *initBackgroundHostMenu(SDL_Window *mainWindow){
    
    int wWindow;
    int hWindow;

    SDLBackground *backgroundHostMenu;

    if((backgroundHostMenu=malloc(sizeof(SDLBackground)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    SDL_Color backgroundColor={0,0,0,255};
    backgroundHostMenu->color=backgroundColor;
    backgroundHostMenu->surface=NULL;
    backgroundHostMenu->texture=NULL;
    backgroundHostMenu->countMetroStation=0;
    backgroundHostMenu->sizeArrMetroLines=3;
    backgroundHostMenu->sizeArrMetroStations=10;
    backgroundHostMenu->sizeArrMetroLinesColor=3;
    backgroundHostMenu->sizeMetroStation=40;
    backgroundHostMenu->metroLineThickness=backgroundHostMenu->sizeMetroStation/(backgroundHostMenu->sizeArrMetroLines+1);
    
    SDL_GetWindowSize(mainWindow,&wWindow,&hWindow);

    backgroundHostMenu->rect.w = wWindow;
    backgroundHostMenu->rect.h = hWindow;
    backgroundHostMenu->rect.x = 0;
    backgroundHostMenu->rect.y = 0;

    backgroundHostMenu->arrMetroStations=calloc(backgroundHostMenu->sizeArrMetroStations,sizeof(MetroStation*));
    backgroundHostMenu->arrMetroLinesColor=calloc(backgroundHostMenu->sizeArrMetroLinesColor,sizeof(SDL_Color));
    backgroundHostMenu->arrMetroLines=calloc(backgroundHostMenu->sizeArrMetroLines,sizeof(MetroLine*));

    if(backgroundHostMenu->arrMetroStations==NULL||backgroundHostMenu->arrMetroLinesColor==NULL||backgroundHostMenu->arrMetroLines==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    for(short counterMetroStation=0;counterMetroStation<backgroundHostMenu->sizeArrMetroStations;counterMetroStation++){
        if((backgroundHostMenu->arrMetroStations[counterMetroStation]=malloc(sizeof(MetroStation)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        if((backgroundHostMenu->arrMetroStations[counterMetroStation]->arrOtherMetroStations=malloc((backgroundHostMenu->sizeArrMetroStations-1)*sizeof(MetroStation*)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
    }

    returnRandomColor(&backgroundHostMenu->arrMetroLinesColor,backgroundHostMenu->sizeArrMetroLinesColor);

    return backgroundHostMenu;
}


void initMetroStation(MetroStation *metroStation, unsigned short geometricShape, SDL_Rect *rect, SDL_Color *color, SDL_Color *insideColor, SDL_Color *srcStationColor, SDL_Color *dstStationColor){

    metroStation->rect=*rect;
    metroStation->display=0;
    metroStation->selected=0;

    metroStation->centerPoint.x=rect->x+rect->w/2;
    metroStation->centerPoint.y=rect->y+rect->h/2;
    
    metroStation->surface=NULL;
    metroStation->texture=NULL;
    metroStation->geometricShape=geometricShape;
    metroStation->color=*color;
    metroStation->insideColor=*insideColor;

    if(srcStationColor!=NULL){
        metroStation->srcStationColor=*srcStationColor;

    }
    if(dstStationColor!=NULL){
        metroStation->dstStationColor=*dstStationColor;
    }
}


SDLLevel *initGameLevel(SDLTimer *timer,LevelName levelName,char *backgroundIMGPath, unsigned short difficulty,File *metroLineColorFile, SDL_Rect *borderContainer){


    SDLLevel *level;

    if((level=malloc(sizeof(SDLLevel)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    level->cycleCounter=0;
    level->cycleProgression=0;
    level->passengersCount=0;
    level->difficulty=difficulty;
    
    switch(levelName){
        case _PARIS_:

            if(level->difficulty==1){
                timer->metroStationApparitionFrequency=1000;
                level->satisfactionFactor=1.2;
                level->cycleDuration=3;
                if((level->background=initLevelBackground(backgroundIMGPath,metroLineColorFile,levelName,borderContainer,3,3,10,40,20))==NULL){
                    return NULL;
                } 
                level->background->countUnlockMetroLine=3;
            }    
        break;
    }
    return level;
}

SDLBackground *initLevelBackground(  char *backgroundIMGPath, File *metroLineColorFile, LevelName levelName, SDL_Rect *borderContainer, unsigned short sizeArrCar, unsigned short sizeArrEngine, unsigned short sizeArrMetroStation, unsigned short sizeMetroStation, unsigned short sizeTransport ){

    SDLBackground *background;

    
    if((background=malloc(sizeof(SDLBackground)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    
    if((background->arrMetroLinesColor=malloc(sizeof(SDL_Color)))==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    background->sizeArrMetroLinesColor=0;
    background->sizeArrMetroStations=sizeArrMetroStation;
    background->sizeArrEngine=sizeArrEngine;
    background->sizeArrCar=sizeArrCar;
    background->countMetroStation=0;
    background->surface=NULL;
    background->texture=NULL;
    background->sizeMetroStation=sizeMetroStation;
    background->sizeTransport=sizeTransport;
    
    if((metroLineColorFile->filePointer=openFile(metroLineColorFile->fullName,metroLineColorFile->openMode))==NULL){
        createErrorReport("Echec lors de l'ouverture d'un fichier de couleurs de lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    switch(levelName){
        case _PARIS_:
            if(loadMetroLineColor(metroLineColorFile->filePointer,"PARIS",&background->arrMetroLinesColor,&background->sizeArrMetroLinesColor)==0){
                createErrorReport("Echec lors de la lecture du fichier de couleurs de lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                return NULL;
            }
        break;
    }
    if(fclose(metroLineColorFile->filePointer)==EOF){
        createErrorReport("Echec lors de la fermeture d'un fichier de couleur de lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    metroLineColorFile->filePointer=NULL;
    background->sizeArrMetroLines=background->sizeArrMetroLinesColor;
    background->metroLineThickness=background->sizeMetroStation/background->sizeArrMetroLinesColor;

    background->arrMetroStations=calloc(background->sizeArrMetroStations,sizeof(MetroStation*));
    background->arrMetroLines=malloc(sizeof(MetroLine*)*background->sizeArrMetroLinesColor);
    background->arrCar=calloc(background->sizeArrCar,sizeof(Car*));
    background->arrEngine=calloc(background->sizeArrEngine,sizeof(Engine*));


    if(background->arrMetroStations==NULL||background->arrMetroLines==NULL||background->arrCar==NULL||background->arrEngine==NULL){
        createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    if((background->surface=SDL_LoadBMP(backgroundIMGPath))==NULL){
        fprintf(stderr,"Echec lors du chargement d'un BitMap dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return NULL;
    }
    background->rect=SDLChangeRect(borderContainer->w,borderContainer->w,background->surface->w-borderContainer->w,background->surface->h-borderContainer->w);

    for(short counterMetroStation=0;counterMetroStation<background->sizeArrMetroStations;counterMetroStation++){
        if((background->arrMetroStations[counterMetroStation]=malloc(sizeof(MetroStation)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        if((background->arrMetroStations[counterMetroStation]->arrOtherMetroStations=malloc((background->sizeArrMetroStations-1)*sizeof(MetroStation*)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
    }

    for(short counterCar=0; counterCar <background->sizeArrCar; counterCar++){
        background->arrCar[counterCar]=NULL;
    }

    for(short counterEngine=0; counterEngine <background->sizeArrEngine; counterEngine++){
        background->arrEngine[counterEngine]=NULL;
    }

    for(short counterMetroLine=0;counterMetroLine<background->sizeArrMetroLinesColor;counterMetroLine++){
        if((background->arrMetroLines[counterMetroLine]=malloc(sizeof(MetroLine)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        background->arrMetroLines[counterMetroLine]->color=background->arrMetroLinesColor[counterMetroLine];

        if((background->arrMetroLines[counterMetroLine]->arrMetroSegment=malloc(sizeof(MetroSegment*)))==NULL){
            createErrorReport("Echec lors d'une allocation de memoire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        background->arrMetroLines[counterMetroLine]->sizeArrSegment=0;
    }
    return background;
}


/*
 * ─── FONCTIONS DE LIBERATION D'ALLOCATION ────────────────────────────────────────
 */

void freeSDLEnvironment(SDLEnvironment *environment){

    if(environment->timer!=NULL){
        free(environment->timer);
        environment->timer=NULL;
    }
    if(environment->background!=NULL){
        freeBackground(environment->background);
        free(environment->background);
        environment->background=NULL;
    }

    if(environment->gui!=NULL){
        freeSDLGUI(environment->gui);
        free(environment->gui);
        environment->gui=NULL;
    }
    
    if(environment->level!=NULL){
        freeSDLLevel(environment->level);
        free(environment->level);
        environment->level=NULL;
    }
}


void freeSDLLevel(SDLLevel *level){

    if(level->background!=NULL){
        freeBackground(level->background);
    }
    free(level->background);
    level->background=NULL;
}

void freeSDLGUI(SDLGUI *gui){

    if(gui->container!=NULL){
        freeSDLContainer(gui->container);
        free(gui->container);
        gui->container=NULL;
    }

    if(gui->leftContainer!=NULL){
        freeSDLContainer(gui->leftContainer);
        free(gui->leftContainer);
        gui->leftContainer=NULL;
    }
    
    if(gui->rightContainer!=NULL){
        freeSDLContainer(gui->rightContainer);
        free(gui->rightContainer);
        gui->rightContainer=NULL;
    }
        
}


void freeSDLContainer(SDLContainer *container){

unsigned short counter;

    for(counter=0;counter<container->sizeArrayButtons;counter++){
        freeSDLButton(container->arrayButtons[counter]);
    }
    free(container->arrayButtons);
    container->arrayButtons=NULL;
    
}
void freeSDLButton(SDLButtons *sdlButtonElement){

    if(sdlButtonElement->texture!=NULL){
        SDL_DestroyTexture(sdlButtonElement->texture);  
    }
    freeSDLText(sdlButtonElement->text);
    sdlButtonElement->text=NULL;

}


void freeSDLText(SDLText *sdlTextElement){

    free(sdlTextElement->content);
    sdlTextElement->content=NULL;
    SDL_DestroyTexture(sdlTextElement->texture);
    TTF_CloseFont(sdlTextElement->font);
}

void freeBackground(SDLBackground *background){

unsigned short counter;

    if(background->arrMetroStations!=NULL){
        for(counter=0;counter<background->sizeArrMetroStations;counter++){
            if(background->arrMetroStations[counter]!=NULL){
                freeMetroStation(background->arrMetroStations[counter]);
                free(background->arrMetroStations[counter]);
                background->arrMetroStations[counter]=NULL;
            }
        }
        free(background->arrMetroStations);
        background->arrMetroStations=NULL;
    }
    
    if(background->arrMetroLines!=NULL){
        for(counter=0;counter<background->sizeArrMetroLines;counter++){
            if(background->arrMetroLines[counter]!=NULL){
                freeMetroLine(background->arrMetroLines[counter]);
                free(background->arrMetroLines[counter]);
                background->arrMetroLines[counter]=NULL;
            } 
        }
        free(background->arrMetroLines);
        background->arrMetroLines=NULL;
    }

    if(background->arrEngine!=NULL){
        for(counter=0;counter<background->sizeArrEngine;counter++){
            if(background->arrEngine[counter]!=NULL){
                freeEngine(background->arrEngine[counter]);
                free(background->arrEngine[counter]);
                background->arrEngine[counter]=NULL;
            } 
        }
        free(background->arrEngine);
        background->arrEngine=NULL;
    }

    if(background->arrMetroLinesColor!=NULL){
        free(background->arrMetroLinesColor);
        background->arrMetroLinesColor=NULL;
    }

    if(background->surface!=NULL){
        SDL_FreeSurface(background->surface);
    }

    if(background->texture!=NULL){
        SDL_DestroyTexture(background->texture);
    }

}

void freeMetroLine(MetroLine *metroLine){

    unsigned short counter;

    if(metroLine->arrMetroSegment!=NULL){
        for(counter=0;counter<metroLine->sizeArrSegment;counter++){
            if(metroLine->arrMetroSegment[counter]!=NULL){
                freeMetroSegment(metroLine->arrMetroSegment[counter]),
                free(metroLine->arrMetroSegment[counter]);
                metroLine->arrMetroSegment[counter]=NULL;
            }
        }
        free(metroLine->arrMetroSegment);
        metroLine->arrMetroSegment=NULL;
    }
}

void freeMetroSegment(MetroSegment *metroSegment){

    if(metroSegment->surface!=NULL){
        SDL_FreeSurface(metroSegment->surface);
    }
    if(metroSegment->texture){
        SDL_DestroyTexture(metroSegment->texture);
    }
}



void freeMetroStation(MetroStation *metroStation){

    if(metroStation->arrOtherMetroStations!=NULL){
        free(metroStation->arrOtherMetroStations);
        metroStation->arrOtherMetroStations=NULL;
    }   

    if(metroStation->surface!=NULL){
        SDL_FreeSurface(metroStation->surface);
    }
    if(metroStation->texture){
        SDL_DestroyTexture(metroStation->texture);
    }

}

void freeEngine(Engine *engine){

    if(engine->surface!=NULL){
        SDL_FreeSurface(engine->surface);
    }
    if(engine->texture){
        SDL_DestroyTexture(engine->texture);
    }
}

