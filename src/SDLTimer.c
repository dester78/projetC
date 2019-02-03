#include <SDLObjectsStructures.h>
#include <SDLMetroStation.h>
#include <SDLMetroLine.h>
#include <SDLTransport.h>


#include<SDL.h>





// void refreshBackgroundHostMenu(SDLEnvironment *environment){

//     environment->timer->refreshCurrentTime = SDL_GetTicks();
//         if (environment->timer->refreshCurrentTime - environment->timer->refreshPastTime > 1000) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */{
            
//             if(environment->background->countMetroStation<environment->background->sizeArrMetroStations){
//                 environment->background->countMetroStation++; 
//             }
//             updateDisplayMetroLineMenu(environment->mainRenderer, environment->background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
//             updateDisplayMetroStations(environment->mainRenderer,environment->background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_);

//              environment->timer->refreshPastTime = environment->timer->refreshCurrentTime ; 
//         }
// }

void refreshBackground(SDLEnvironment *environment,MenuLevel menuOrLevel){

    SDLBackground *background;
    // int frequency;

    background=menuOrLevel==_LEVEL_?environment->level->background:environment->background;
    // frequency=menuOrLevel==_LEVEL_?environment->timer->refreshFrequency:1000;

    environment->timer->refreshCurrentTime = SDL_GetTicks();
    environment->timer->addMetroStationCurrentTime = SDL_GetTicks();
        if (environment->timer->refreshCurrentTime - environment->timer->refreshPastTime > environment->timer->refreshFrequency){
            
            if(environment->timer->addMetroStationCurrentTime - environment->timer->addMetroStationPastTime > environment->timer->metroStationApparitionFrequency){


                if(background->countMetroStation<background->sizeArrMetroStations){
                        background->countMetroStation++; 
                        environment->timer->addMetroStationPastTime=environment->timer->addMetroStationCurrentTime;
                        // updateDisplayMetroStations(environment->mainRenderer,background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_);
                    }
                
                if(menuOrLevel==_MENU_){
                    updateDisplayMetroLineMenu(environment->mainRenderer, background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
                    updateDisplayMetroStations(environment->mainRenderer,background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_);
                    
                }
                
                
            }
            if(menuOrLevel==_LEVEL_){
                    
                updateDisplayMetroLineLevel(environment->mainRenderer, &background->arrMetroLines,&background->arrMetroStations, background->sizeArrMetroLines, background->sizeArrMetroStations );
                updateDisplayMetroStations(environment->mainRenderer,background,NULL,NULL,_LEVEL_);
                updateDisplayEngines(environment->mainRenderer,background,&background->arrEngine,&background->arrMetroLines,&background->arrMetroStations,background->sizeArrEngine,background->sizeArrMetroLines,background->sizeArrMetroStations,background->metroLineThickness);
                // updateDisplayEngines(environment->mainRenderer, environment->level->background,environment->level->background->arrEngine, MetroLine **arrMetroLine, MetroStation **arrMetroStation,unsigned short sizeArrEngine, unsigned short sizeArrMetroLine, int sizeArrMetroStation ){

                // updateColorMetroStation(environment->mainRenderer,environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroStations);
            }
        
                
            environment->timer->refreshPastTime = environment->timer->refreshCurrentTime ; 
        }
}

//Permet de gérer la durée des évenements provenant des utilisateurs
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
// SDL_Event

