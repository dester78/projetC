#include <SDLObjectsStructures.h>
#include <SDLMetroStation.h>
#include <SDLMetroLine.h>
#include <SDLTransport.h>


#include<SDL.h>

short refreshBackground(SDLEnvironment *environment,MenuLevel menuOrLevel){

    SDLBackground *background;

    //On modifie le pointeur de background en fonction du menu ou du niveau
    background=menuOrLevel==_LEVEL_?environment->level->background:environment->background;

    environment->timer->refreshCurrentTime = SDL_GetTicks();
    environment->timer->addMetroStationCurrentTime = SDL_GetTicks();
    if (environment->timer->refreshCurrentTime - environment->timer->refreshPastTime > environment->timer->refreshFrequency){
        
        if(environment->timer->addMetroStationCurrentTime - environment->timer->addMetroStationPastTime > environment->timer->metroStationApparitionFrequency){

            if(background->countMetroStation<background->sizeArrMetroStations){
                background->countMetroStation++; 
                environment->timer->addMetroStationPastTime=environment->timer->addMetroStationCurrentTime;
            }
            
            if(menuOrLevel==_MENU_){
                if(updateDisplayMetroLineMenu(environment->mainRenderer, background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons)==0){
                    createErrorReport("Echec lors de la mise à jour de l'afichage des lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
                if(updateDisplayMetroStations(environment->mainRenderer,background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_)==0){
                    createErrorReport("Echec lors de la mise à jour de l'affichage des stations de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }  
        }
        if(menuOrLevel==_LEVEL_){

            if(updateDisplayMetroLineLevel(environment->mainRenderer, &background->arrMetroLines,&background->arrMetroStations, background->sizeArrMetroLines, background->sizeArrMetroStations )==0){
                createErrorReport("Echec lors de la mise à jour de l'afichage des lignes de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            } 
            if(updateDisplayMetroStations(environment->mainRenderer,background,NULL,0,_LEVEL_)==0){
                createErrorReport("Echec lors de la mise à jour de l'affichage des stations de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }   
            if(updateDisplayEngines(environment->mainRenderer,background,&background->arrEngine,&background->arrMetroLines,&background->arrMetroStations,background->sizeArrEngine,background->sizeArrMetroLines,background->sizeArrMetroStations)==0){
                createErrorReport("Echec lors de la mise à jour de l'affichage des locomotives",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }  
        }     
        environment->timer->refreshPastTime = environment->timer->refreshCurrentTime ; 
    }
    return 1;
}

short controlUserEventTime(SDLEnvironment *environment){
    
    environment->timer->userEventCurrentTime = SDL_GetTicks();

    switch(environment->event.type){

        case SDL_MOUSEBUTTONUP:
            if(environment->event.button.timestamp-environment->timer->clickTime>100){
                environment->timer->clickTime=environment->event.button.timestamp;
                return 1;
            }
        break;
    }
    return 0;
}

