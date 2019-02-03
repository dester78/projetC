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

#include <SDLMain.h>

#include <SDL.h>
#include <mysql.h>



int SDLMainMenuLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, FileIndex *fileIndex){

    short windowLoop;
    unsigned short intersect=0;

    SDLEnvironment *environment;
    SDL_Point mousePoint;

    srand(time(NULL));//Initailisation du générateur de nombre aléatoire    

    environment=initSDLEnvironment(mainWindow,mainRenderer);

    environment->gui=initGUIHostMenu(mainWindow,SDLConfigElement,dbConnection);    
    printf("OKBackground");

    environment->background=initBackgroundHostMenu(mainWindow);
    environment->timer=initTimer(1);
    environment->timer->metroStationApparitionFrequency=1000;
    SDLCreateBackgroundHostMenu(mainRenderer,environment->background);

    for(int counterButton=0; counterButton<environment->gui->container->sizeArrayButtons; counterButton++){
        displayRectButton(mainRenderer,environment->gui->container->arrayButtons[counterButton]);
        displayTextButton(mainRenderer,environment->gui->container->arrayButtons[counterButton]);
        environment->gui->container->arrayButtons[counterButton]->display=1;
    }

    addMetroLineAndStationMenu(environment->background,environment->gui->container->arrayButtons,environment->gui->container->sizeArrayButtons);
    
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
                        controlHoverButton(mainRenderer, environment->gui->container->arrayButtons,counterButton, environment->gui->container->sizeArrayButtons,intersect);
                    }
                }
                if(intersect==0){
                        controlHoverButton(mainRenderer, environment->gui->container->arrayButtons,0, environment->gui->container->sizeArrayButtons,intersect);
                }
            break;


            case SDL_MOUSEBUTTONUP: 

                mousePoint=createPointXY(environment->event.button.x,environment->event.button.y);

                if(hasIntersectPointRect(&mousePoint,&environment->gui->container->arrayButtons[1]->rect)){  
                    freeBackground(environment->background);   
                    freeSDLGUI(environment->gui);  
                    levelLoop(environment,SDLConfigElement,fileIndex,_PARIS_,1);            
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



void addMetroLineAndStationMenu( SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons){

    SDLCreateMetroStations(backgroundMenu,_MENU_ );  
    fillArrayMetroStation(backgroundMenu->arrMetroStations,backgroundMenu->sizeArrMetroStations);     
    sortArrayMetroStationByDistance(backgroundMenu->arrMetroStations,backgroundMenu->sizeArrMetroStations);

    SDLCreateMetroLineMenu(backgroundMenu); 
    SDLCreateMetroSegmentMenu(backgroundMenu);
}



short levelLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *FileIndex, LevelName levelName, unsigned short difficulty){

    short levelLoop;
    SDL_Point mousePoint;
    short intersect;
    short select;

    environment->gui=initGUILevel(environment->mainWindow,SDLConfigElement);
    
    //Nouvelle partie : 
    switch(levelName){
        case _PARIS_:
            environment->level=initGameLevel( environment->timer,levelName,SDLConfigElement->img->parisMap,difficulty,FileIndex->metroLineColor,&environment->gui->leftContainer->rect);
            environment->gui->rightContainer=initContainer(environment->mainWindow,_RIGHT_,environment->level->background->sizeArrMetroLinesColor+3);
        break;
    }
    SDLCreateBackgroundLevel(environment->mainRenderer,environment->level->background,environment->mainWindow);
    SDLCreateMetroStations(environment->level->background,_LEVEL_);
    fillArrayMetroStation(environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroStations);     
    sortArrayMetroStationByDistance(environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroStations);


    if(initButtonSideContainerLevel(environment->gui->leftContainer,  _LEFT_, SDLConfigElement->ttf->fontMenu, environment->level->background)==0){
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    if(initButtonSideContainerLevel(environment->gui->rightContainer,  _RIGHT_, SDLConfigElement->ttf->fontMenu, environment->level->background)==0){
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }    

    // printf("background->texture apres :%p \n",environment->level->background->texture);
    printf("apres init");
    displayGUILevel(environment->mainRenderer,environment->gui);

    printf("APRES DISPLAY");
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
                    

                    buttonEventManagerLevel(environment->mainRenderer,&mousePoint,environment->gui->rightContainer,environment->gui->leftContainer,select);
                    metroLineEventManagerLevel(environment->mainRenderer, environment->level->background, environment->gui->rightContainer,environment->level->background->arrMetroLines,environment->level->background->arrMetroStations,environment->level->background->sizeArrMetroLines, environment->level->background->sizeArrMetroStations,environment->level->background->metroLineThickness,&mousePoint,select,_RIGHT_);

                    transportEventManager(environment->mainRenderer,&mousePoint,environment->gui->leftContainer,environment->gui->rightContainer, &environment->level->background->arrMetroLines, &environment->level->background->arrCar, &environment->level->background->arrEngine,environment->level->background->sizeArrMetroLines,&environment->level->background->sizeArrCar, &environment->level->background->sizeArrEngine, environment->level->background->sizeTransport, &mousePoint,environment->level->background->metroLineThickness, select);
                }
                
            break; 
                                
        }
        // printf("background->texture : %p\n",environment->level->background->texture);
        
        refreshBackground(environment,_LEVEL_);
        SDL_RenderPresent(environment->mainRenderer);

    }
    return 0;

}



