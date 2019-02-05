#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <structures.h> 
#include <fileManager.h>
#include <SDLTimer.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>
#include <SDLColor.h>
#include <SDLObjects.h>
#include <SDLBackgroundObjects.h>
#include <SDLMetroStation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLTransport.h>

#include <SDLMain.h>

#include <SDL.h>
#include <mysql.h>

/*
 * ─── INITIALISATION DES BOUCLES ─────────────────────────────────────────────────
 */





SDLEnvironment *initMainMenuLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,MYSQL *dbConnection){

    SDLEnvironment *environment;

    if((environment=initSDLEnvironment(mainWindow,mainRenderer))==NULL){
        createErrorReport("Echec lors de l'initialisation d'un environnement",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    if((environment->gui=initGUIHostMenu(mainWindow,SDLConfigElement,dbConnection))==NULL){
        createErrorReport("Echec lors de l'initialisation de l'interface utilisateur",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }    

    if((environment->background=initBackgroundHostMenu(mainWindow))==NULL){
        createErrorReport("Echec lors de l'initialisation du background'",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    if((environment->timer=initTimer(1))==NULL){
        createErrorReport("Echec lors de l'initialisation du timer'",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    environment->timer->metroStationApparitionFrequency=1000;
    if(SDLDisplayBackgroundHostMenu(mainRenderer,environment->background)==0){
        createErrorReport("Impossible d'afficher le background de menu",__FILE__,__LINE__,__DATE__,__TIME__);  
        return NULL;
    }

    for(int counterButton=0; counterButton<environment->gui->container->sizeArrayButtons; counterButton++){
        if(displayRectButton(mainRenderer,environment->gui->container->arrayButtons[counterButton])==0){
            createErrorReport("Echec lors de l'affichage d'un bouton rectangulaire",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        if(displayTextButton(mainRenderer,environment->gui->container->arrayButtons[counterButton])==0){
            createErrorReport("Echec lors de l'affichage de texte dans un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        environment->gui->container->arrayButtons[counterButton]->display=1;
    }

    if(SDLCreateMetroStations(environment->background,_MENU_ )==0){
        createErrorReport("Echec lors de la creation de stations de metro",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    } 
    fillArrayMetroStation(environment->background->arrMetroStations,environment->background->sizeArrMetroStations);     
    sortArrayMetroStationByDistance(environment->background->arrMetroStations,environment->background->sizeArrMetroStations);

    if(SDLCreateMetroLineMenu(environment->background)==0){
        createErrorReport("Echec lors de l'initialisation des lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    if(SDLCreateMetroSegmentMenu(environment->background)==0){
        createErrorReport("Echec lors de l'initialisation des segment de lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    return environment;
}


short initLevelLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *fileIndex, LevelName levelName, unsigned short difficulty){

    if((environment->gui=initGUILevel(environment->mainWindow,SDLConfigElement))==NULL){
        createErrorReport("Echec lors de l'initialisation de l'interface utilisateur",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    
    //Nouvelle partie : 
    switch(levelName){
        case _PARIS_:
            if((environment->level=initGameLevel( environment->timer,levelName,SDLConfigElement->img->parisMap,difficulty,fileIndex->metroLineColor,&environment->gui->leftContainer->rect))==NULL){
                createErrorReport("Echec lors de l'initialisation du niveau",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }

            if((environment->gui->rightContainer=initContainer(environment->mainWindow,_RIGHT_,environment->level->background->sizeArrMetroLinesColor+3))==NULL){
                createErrorReport("Echec lors de l'initialisation du conteneur",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        break;
    }

    if(SDLDisplayBackgroundLevel(environment->mainRenderer,environment->level->background,environment->mainWindow)==0){
        createErrorReport("Impossible d'afficher le background de niveau",__FILE__,__LINE__,__DATE__,__TIME__);  
        return 0;
    }
    
    if(SDLCreateMetroStations(environment->level->background,_LEVEL_)==0){
        createErrorReport("Echec lors de la creation de stations de metro",__FILE__,__LINE__,__DATE__,__TIME__);  
        return 0;
    }

    fillArrayMetroStation(environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroStations);     
    sortArrayMetroStationByDistance(environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroStations);


    if(initButtonSideContainerLevel(environment->gui->leftContainer,  _LEFT_, SDLConfigElement->ttf->fontMenu, environment->level->background)==0){
        createErrorReport("Impossible d'initialiser un conteneur de niveau",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    if(initButtonSideContainerLevel(environment->gui->rightContainer,  _RIGHT_, SDLConfigElement->ttf->fontMenu, environment->level->background)==0){
        createErrorReport("Impossible d'initialiser un conteneur de niveau",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }    

    if(displayGUILevel(environment->mainRenderer,environment->gui)==0){
        createErrorReport("Echec lors de l'affichage de l'interface utilisateur",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    return 1;
}


/*
 * ─── BOUCLES SDL ────────────────────────────────────────────────────────────────
 */

int SDLMainMenuLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, FileIndex *fileIndex){

    short windowLoop;
    unsigned short intersect=0;

    SDLEnvironment *environment;
    SDL_Point mousePoint;

    srand(time(NULL));//Initailisation du générateur de nombre aléatoire    

    if((environment=initMainMenuLoop(mainWindow,mainRenderer,SDLConfigElement,dbConnection))==NULL){
        createErrorReport("Echec lors de l'initialisation de la boucle  de menu",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    
    
    while(windowLoop){

        SDL_PollEvent(&environment->event);

        switch(environment->event.type){
            
            case SDL_QUIT : 
            windowLoop = 0;
            break;

            case SDL_MOUSEMOTION : 
                mousePoint=createPointXY(environment->event.motion.x,environment->event.motion.y);
                intersect=0;
                for(int counterButton=0; counterButton<environment->gui->container->sizeArrayButtons; counterButton++){
                    if(hasIntersectPointRect(&mousePoint,&environment->gui->container->arrayButtons[counterButton]->rect)){
                        intersect=1;
                        if(controlHoverButton(mainRenderer, environment->gui->container->arrayButtons,counterButton, environment->gui->container->sizeArrayButtons,intersect)==0){
                            createErrorReport("Echec lors du controle de survol de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                    }
                }
                if(intersect==0){
                    if(controlHoverButton(mainRenderer, environment->gui->container->arrayButtons,0, environment->gui->container->sizeArrayButtons,intersect)==0){
                        createErrorReport("Echec lors du controle de survol de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }
                }
            break;

            case SDL_MOUSEBUTTONUP: 

                mousePoint=createPointXY(environment->event.button.x,environment->event.button.y);

                if(hasIntersectPointRect(&mousePoint,&environment->gui->container->arrayButtons[1]->rect)){  
                    freeBackground(environment->background);  
                    freeSDLGUI(environment->gui);  
                    levelLoop(environment,SDLConfigElement,fileIndex,_PARIS_,1);    
                    freeBackground(environment->level->background);
                    freeSDLGUI(environment->gui);        
                }

                else if(hasIntersectPointRect(&mousePoint,&environment->gui->container->arrayButtons[3]->rect)){                  
                    environment->event.type=SDL_QUIT;
                }
            break; 
                                              
        }

        refreshBackground(environment,_MENU_); 
        SDL_RenderPresent(mainRenderer);  
    }

    freeSDLEnvironment(environment);
    free(environment);
    
    return -1;
}


short levelLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *fileIndex, LevelName levelName, unsigned short difficulty){

    SDL_Point mousePoint;
    SDLBackground *backgroundLevel;
    short levelLoop;
    short select;
    

    if(initLevelLoop(environment, SDLConfigElement,fileIndex, levelName, difficulty)==0){
        createErrorReport("Echec lors de l'initialisation de la boucle de niveau'",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }  
    backgroundLevel=environment->level->background;

    while(levelLoop){

        SDL_PollEvent(&environment->event);

        switch(environment->event.type){          
            case SDL_QUIT : 
                levelLoop = 0;
            break;
            case SDL_MOUSEBUTTONUP: 

                switch(environment->event.button.button){
                    case SDL_BUTTON_LEFT:
                        select=1;
                    break;
                    case SDL_BUTTON_RIGHT:
                        select=0;
                    break;
                }
                if(controlUserEventTime(environment)){
                    mousePoint=createPointXY(environment->event.button.x,environment->event.button.y);
                    //   
                    if(buttonEventManagerLevel(environment->mainRenderer,&mousePoint,environment->gui->rightContainer,environment->gui->leftContainer,select)==0){
                        createErrorReport("Echec lors de la gestion des evenements lies aux boutons",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }
                    if(metroLineEventManagerLevel(environment->mainRenderer, backgroundLevel, environment->gui->rightContainer,backgroundLevel->arrMetroLines,backgroundLevel->arrMetroStations,&backgroundLevel->arrEngine,backgroundLevel->sizeArrMetroLines, backgroundLevel->sizeArrMetroStations,backgroundLevel->sizeArrEngine, backgroundLevel->metroLineThickness,&mousePoint,select,_RIGHT_)==0){
                        createErrorReport("Echec prendant la gestion des evenements lies aux lignes de metro.",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }

                    if(transportEventManager(environment->mainRenderer, backgroundLevel,environment->gui->leftContainer,environment->gui->rightContainer, &backgroundLevel->arrMetroLines, &backgroundLevel->arrCar, &backgroundLevel->arrEngine,backgroundLevel->sizeArrMetroLines,&backgroundLevel->sizeArrCar, &backgroundLevel->sizeArrEngine, backgroundLevel->sizeTransport, &mousePoint, select)==0){
                        createErrorReport("Echec prendant la gestion des evenements lies aux transports.",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }
                }
                
            break; 
                                
        }
        
        refreshBackground(environment,_LEVEL_);
        SDL_RenderPresent(environment->mainRenderer);
    }
    return 1;
}
