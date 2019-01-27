#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>

#include<SDL.h>





void refreshBackgroundHostMenu(SDLEnvironment *environment){

    environment->timer->currentTime = SDL_GetTicks();
        if (environment->timer->currentTime - environment->timer->pastTime > 1000) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */{
            
            if(environment->background->countMetroStation<environment->background->sizeArrMetroStations){
                environment->background->countMetroStation++; 
            }
            updateDisplayMetroLineMenu(environment->mainRenderer, environment->background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
            updateDisplayMetroStations(environment->mainRenderer,environment->background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_);

             environment->timer->pastTime = environment->timer->currentTime ; 
        }
}

void refreshBackground(SDLEnvironment *environment,MenuLevel menuOrLevel){

    SDLBackground *background;
    int frequency;

    background=menuOrLevel==_LEVEL_?environment->level->background:environment->background;
    frequency=menuOrLevel==_LEVEL_?environment->level->metroStationApparitionFrequency:1000;

    environment->timer->currentTime = SDL_GetTicks();
        if (environment->timer->currentTime - environment->timer->pastTime > frequency){
            
            if(background->countMetroStation<background->sizeArrMetroStations){
                background->countMetroStation++; 
            }

            if(menuOrLevel==_MENU_){
                updateDisplayMetroLineMenu(environment->mainRenderer, background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
                updateDisplayMetroStations(environment->mainRenderer,background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons,_MENU_);
            }

            else{
                // printf("metroLine1 : %p\n",environment->level->background->arrMetroLines[0]);
                // printf("arrMetroLine : %p\n",environment->level->background->arrMetroLines);

                // printf("SIZE AR SGEMENT : %d",environment->level->background->arrMetroLines[0]->sizeArrSegment);
                updateDisplayMetroLineLevel(environment->mainRenderer, &environment->level->background->arrMetroLines,&environment->level->background->arrMetroStations, environment->level->background->sizeArrMetroLines, environment->level->background->sizeArrMetroStations );

                updateDisplayMetroStations(environment->mainRenderer,background,NULL,NULL,_LEVEL_);
            }
            // updateDisplayMetroLineMenu(environment->mainRenderer, background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
           

            environment->timer->pastTime = environment->timer->currentTime ; 
        }
}

short controlUserEventTime(SDLEnvironment *environment){


    environment->timer->currentTime = SDL_GetTicks();

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
