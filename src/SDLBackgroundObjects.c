#include <stdio.h>

#include <SDLColor.h>
#include <SDLMetroLine.h>
#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>
#include <mathCalculation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLDraw.h>

#include <SDL.h>


void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background){
   
    if((background->surface=SDL_CreateRGBSurfaceWithFormat(0, background->rect.w,background->rect.h, 32, SDL_PIXELFORMAT_RGBA8888))!=NULL){

        if((SDL_FillRect(background->surface,&background->rect,SDL_MapRGBA(background->surface->format,255,255,255,255)))==0){

            if((background->texture=SDL_CreateTextureFromSurface(mainRenderer,background->surface))!=NULL){

                if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&background->rect)==0){
                    SDL_RenderPresent(mainRenderer);
                }
                else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
            }
            else{fprintf(stderr,"Echec lors de la convertion de la surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
        }
        else{fprintf(stderr,"Echec lors du remplissage de la surface par un rectangle dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
    }
    else{fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}


void SDLCreateBackgroundLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDL_Window *mainWindow){
   
    SDL_Rect windowRect;

    SDL_GetWindowSize(mainWindow,&windowRect.w,&windowRect.h);
    windowRect=SDLChangeRect(0,0,windowRect.w,windowRect.h);

    if((background->texture=SDL_CreateTextureFromSurface(mainRenderer,background->surface))!=NULL){

        if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&windowRect)==0){
            SDL_RenderPresent(mainRenderer);
        }
        else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
    }
    else{fprintf(stderr,"Echec lors de la convertion de la surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 

}



void SDLCreateMetroStations(SDLBackground *background, MenuLevel menuOrLevel){

SDL_Rect rectStation;
int geometricShape;
SDL_Color waterColor={211,237,248,255};
SDL_Color color={0,0,0,255};
SDL_Color insideColor={255,255,255,255};

    for(short counterMetroStations=0; counterMetroStations<background->sizeArrMetroStations; counterMetroStations++){

        counterMetroStations=counterMetroStations<0?0:counterMetroStations;

        geometricShape=rand()%3;
        rectStation=controlOverlapMetroStations(background->arrMetroStations, counterMetroStations, &background->rect,background->sizeMetroStation,1.2);
        if(menuOrLevel==_LEVEL_){
            if(searchColorInSurface(&waterColor,&rectStation,background->surface,1)){
                counterMetroStations--;
            }
            else{
                SDL_Color srcColor={255,207,0,255};
                SDL_Color dstColor={115,225,35,255};
                initMetroStation(background->arrMetroStations[counterMetroStations],geometricShape,&rectStation,&color,&insideColor,&srcColor,&dstColor);
            }
        }
        else{
            initMetroStation(background->arrMetroStations[counterMetroStations],geometricShape,&rectStation,&color,&insideColor,NULL,NULL);
        }      
    }          
}


short controlSelectedMetroStation(SDL_Renderer *mainRenderer, MetroStation **arrayMetroStation,unsigned short currentMetroStation, unsigned short sizeArrMetroStation, unsigned short selectedBool){

    MetroStation *firstMetroStation=NULL, *secondMetroStation=NULL;
    short countSelectedMetroStations=0;

    getSelectedMetroStations(arrayMetroStation,&firstMetroStation,&secondMetroStation,sizeArrMetroStation);

    if(selectedBool){
        if(arrayMetroStation[currentMetroStation]->display){
            if(firstMetroStation!=NULL&&secondMetroStation!=NULL){
                if(arrayMetroStation[currentMetroStation]!=secondMetroStation&&arrayMetroStation[currentMetroStation]!=firstMetroStation){
                    firstMetroStation->selected=0;
                    secondMetroStation->selected=1;
                    arrayMetroStation[currentMetroStation]->selected=2;
                    countSelectedMetroStations=2;
                }
            }
            else if(firstMetroStation!=NULL&&secondMetroStation==NULL){
                if(arrayMetroStation[currentMetroStation]!=firstMetroStation){
                    arrayMetroStation[currentMetroStation]->selected=2;
                    countSelectedMetroStations=2;
                }
            }
            else if(firstMetroStation==NULL&&secondMetroStation==NULL){
                arrayMetroStation[currentMetroStation]->selected=1;
                countSelectedMetroStations=1;
                arrayMetroStation[currentMetroStation]->display=0;
                displayMetroStation(mainRenderer, arrayMetroStation[currentMetroStation],&arrayMetroStation[currentMetroStation]->srcStationColor,&arrayMetroStation[currentMetroStation]->insideColor);
                return 1;
            }
        }
    }
    else{
        if(firstMetroStation!=NULL){
            if(arrayMetroStation[currentMetroStation]==firstMetroStation){
                firstMetroStation->selected=0;
                if(secondMetroStation!=NULL){
                    secondMetroStation->selected=0;
                }
            }
        }
        if(secondMetroStation!=NULL){
            if(arrayMetroStation[currentMetroStation]==secondMetroStation){
                secondMetroStation->selected=0;
                countSelectedMetroStations=1;
            }
        }
    }
    updateColorMetroStations(mainRenderer,arrayMetroStation,sizeArrMetroStation);
    return countSelectedMetroStations;
}

short getSelectedMetroLineCounter(SDLContainer *container){

    for(int counterButtons=3; counterButtons<container->sizeArrayButtons; counterButtons++){
        if(container->arrayButtons[counterButtons]->selected){
            return counterButtons-3; 
        }
    }
    return 0;
}


void updateColorMetroStations(SDL_Renderer *mainRenderer,MetroStation **arrMetroStations,int sizeArrMetroStation){

    for(unsigned short counterMetroStation=0; counterMetroStation<sizeArrMetroStation; counterMetroStation++){

        if(arrMetroStations[counterMetroStation]->selected==2){
            arrMetroStations[counterMetroStation]->display=0;
            displayMetroStation(mainRenderer, arrMetroStations[counterMetroStation],&arrMetroStations[counterMetroStation]->dstStationColor,&arrMetroStations[counterMetroStation]->insideColor);
        }
        else if(arrMetroStations[counterMetroStation]->selected==1){
            arrMetroStations[counterMetroStation]->display=0;
            displayMetroStation(mainRenderer, arrMetroStations[counterMetroStation],&arrMetroStations[counterMetroStation]->srcStationColor,&arrMetroStations[counterMetroStation]->insideColor);
        }
        else if(arrMetroStations[counterMetroStation]->selected==0&&arrMetroStations[counterMetroStation]->display){
            arrMetroStations[counterMetroStation]->display=0;
            displayMetroStation(mainRenderer, arrMetroStations[counterMetroStation],&arrMetroStations[counterMetroStation]->color,&arrMetroStations[counterMetroStation]->insideColor);
        }
    }
}


void getSelectedMetroStations(MetroStation **arrMetroStations, MetroStation **srcMetroStation, MetroStation **dstMetroStation, int sizeArrMetroStation){

    for(int counterMetroStation=0; counterMetroStation<sizeArrMetroStation; counterMetroStation++){

        if(arrMetroStations[counterMetroStation]!=NULL){
            if(arrMetroStations[counterMetroStation]->selected==1){
                *srcMetroStation=arrMetroStations[counterMetroStation];
            }
            else if(arrMetroStations[counterMetroStation]->selected==2){
                *dstMetroStation=arrMetroStations[counterMetroStation];
            }
        }
    }
}

short controlMetroStationOnLine(MetroSegment *startMetroSegment, MetroStation *srcStation, MetroStation *dstStation){

    MetroSegment *nextSegment;
    while(startMetroSegment->nextSegment!=NULL){

        nextSegment=startMetroSegment->nextSegment;

        if(&nextSegment->dstStation!=NULL){

            if(dstStation==nextSegment->dstStation){
                return 0;
            }
        }
    }

    while(startMetroSegment->precedentSegment!=NULL){

        nextSegment=startMetroSegment->precedentSegment;

        if(startMetroSegment->srcStation!=NULL&&nextSegment->srcStation!=NULL){
            if(startMetroSegment->srcStation==nextSegment->srcStation){
                return 0;
            }
        }
    }
    return 1;
}

void createMetroSegmentLevel(MetroLine **metroLine, MetroStation **arrMetroStations, int sizeArrMetroStation, short counterMetroLine, short metroLineThickness){

    MetroStation *srcMetroStation, *dstMetroStation;
    
    getSelectedMetroStations(arrMetroStations,&srcMetroStation,&dstMetroStation,sizeArrMetroStation);

    (*metroLine)->arrMetroSegment=realloc((*metroLine)->arrMetroSegment,(++(*metroLine)->sizeArrSegment)*sizeof(MetroSegment*));
    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]=malloc(sizeof(MetroSegment));

    if((*metroLine)->sizeArrSegment==1){
        (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->precedentSegment=NULL;
    }
    
    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->surface=NULL;
    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->texture=NULL;
    
    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->srcStation=srcMetroStation;
    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->dstStation=dstMetroStation;

    createRectBetweenTwoRect(
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->srcStation->rect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->dstStation->rect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->rect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->srcPointInRect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->dstPointInRect);

    (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->display=0;

    shiftPointPositionMetroLine(
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->rect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->srcPointInRect, 
        counterMetroLine,
        metroLineThickness);

    shiftPointPositionMetroLine(
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->rect,
        &(*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1]->dstPointInRect, 
        counterMetroLine,
        metroLineThickness);

    if((*metroLine)->sizeArrSegment>1){
        preparePathRectMetroSegment((*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-2], (*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-2],metroLineThickness, counterMetroLine);
    }
    else{
        preparePathRectMetroSegment((*metroLine)->arrMetroSegment[(*metroLine)->sizeArrSegment-1], NULL,metroLineThickness,counterMetroLine);
    }


}






SDL_Rect controlOverlapMetroStations(MetroStation **arrMetroStations, unsigned short counterMetroStations,SDL_Rect *parentRect,int sizeMetroStation, double sizeFactor){


    SDL_Rect riskRect;
    int maxSize=sizeFactor*sizeMetroStation;
 
    riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize);   


    for(unsigned short controlCounterMetroStation=0; controlCounterMetroStation<counterMetroStations; controlCounterMetroStation++){

        if(SDL_HasIntersection(&arrMetroStations[controlCounterMetroStation]->rect,&riskRect)){     
            riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize);   
            controlCounterMetroStation=0;
        }
    } 


    return SDLChangeRect(riskRect.x,riskRect.y,sizeMetroStation,sizeMetroStation);

}


void SDLCreateMetroLineMenu(SDLBackground *backgroundMenu){
    
    for(unsigned short counterMetroLine=0; counterMetroLine<backgroundMenu->sizeArrMetroLines; counterMetroLine++){


        short randValue=rand()%backgroundMenu->sizeArrMetroStations;

        backgroundMenu->arrMetroLines[counterMetroLine]=malloc(sizeof(MetroLine));

        backgroundMenu->arrMetroLines[counterMetroLine]->color=backgroundMenu->arrMetroLinesColor[counterMetroLine];

        backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment =rand()%(backgroundMenu->sizeArrMetroStations/2)+2;

        backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment = calloc(backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment,sizeof(MetroSegment*));

        backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation=backgroundMenu->arrMetroStations[randValue];
        
    }
}

void SDLCreateMetroSegmentMenu(SDLBackground *backgroundMenu){

    for(unsigned short counterMetroLine=0;counterMetroLine<backgroundMenu->sizeArrMetroLines;counterMetroLine++){

        if(backgroundMenu->arrMetroLines[counterMetroLine]!=0){

            for(unsigned short counterMetroSegment=0; counterMetroSegment<backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment;counterMetroSegment++){
                
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]=malloc(sizeof(MetroSegment));
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->surface=NULL;
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->texture=NULL;


                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],0);

                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment+1],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],1);

                createRectBetweenTwoRect(
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->rect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->rect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointInRect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstPointInRect);

                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display=0;

                shiftPointPositionMetroLine(
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointInRect, 
                    counterMetroLine,
                    backgroundMenu->metroLineThickness);

                shiftPointPositionMetroLine(
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect,
                    &backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstPointInRect, 
                    counterMetroLine,
                    backgroundMenu->metroLineThickness);

                if(counterMetroSegment>0){
                    preparePathRectMetroSegment(backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment], backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment-1],backgroundMenu->metroLineThickness, counterMetroLine);
                }
                else{
                    preparePathRectMetroSegment(backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment], NULL,backgroundMenu->metroLineThickness,counterMetroLine);
                }

            }
        }     
    }    
}



void sortArrayMetroStationPoints(MetroStation **arrMetroStations,unsigned short sizeArrMetroStations){

MetroStation *tmpMetroStationPointer;

    for(unsigned short counterMetroStations=0;counterMetroStations<sizeArrMetroStations;counterMetroStations++){

        for(unsigned short counterOtherMetroStations=0; counterOtherMetroStations<sizeArrMetroStations-1; counterOtherMetroStations++){

            for(unsigned short counterOtherMetroStationsBis=counterOtherMetroStations+1; counterOtherMetroStationsBis<sizeArrMetroStations-1; counterOtherMetroStationsBis++){
                
                if(distanceBetweenTwoPoint(&arrMetroStations[counterMetroStations]->centerPoint, &arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStations]->centerPoint) > distanceBetweenTwoPoint(&arrMetroStations[counterMetroStations]->centerPoint, &arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStationsBis]->centerPoint)){

                    tmpMetroStationPointer=arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStations];
                    arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStations]=arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStationsBis];
                    arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStationsBis]=tmpMetroStationPointer;
                }
            } 
        }

    }
}

void fillArrayMetroStationPoints(MetroStation **arrMetroStations, unsigned short sizeArrMetroStations){

    for(unsigned short counterMetroStations=0;counterMetroStations<sizeArrMetroStations;counterMetroStations++){

        printf("metroStationCounter : %d, metroStation :%p\n\n",counterMetroStations,arrMetroStations[counterMetroStations]);


        for(unsigned short counterOtherMetroStations=0; counterOtherMetroStations<sizeArrMetroStations-1; counterOtherMetroStations++){

            if(counterMetroStations<=counterOtherMetroStations){
                arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStations]=arrMetroStations[counterOtherMetroStations+1];

            }

            else if(counterMetroStations>counterOtherMetroStations){
                 arrMetroStations[counterMetroStations]->arrOtherMetroStations[counterOtherMetroStations]=arrMetroStations[counterOtherMetroStations];
                 
            }
        }
    }
}



short updateDisplayMetroLineMenu(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons){

    for(unsigned short counterMetroLine=0; counterMetroLine<backgroundMenu->sizeArrMetroLines;counterMetroLine++){

        if(backgroundMenu->arrMetroLines[counterMetroLine]!=0){

            for(unsigned short counterMetroSegment=0; counterMetroSegment<backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment;counterMetroSegment++){
                
                if(backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->display && backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->display){

                    if((counterMetroSegment==0 || backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment-1]->display ) && backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display==0 ){

                        updateDisplayMetroSegment(mainRenderer, backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment], backgroundMenu->arrMetroLines[counterMetroLine]);

                        SDL_Rect absoluteSrcPointToPathPointRect;
                        SDL_Rect absolutePathPointToDstPointRect;

                        absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
                        absolutePathPointToDstPointRect=absoluteRectPositionInRect(&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

                        for(unsigned short counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&buttonsHostMenu[counterButton]->rect) || SDL_HasIntersection(&absolutePathPointToDstPointRect,&buttonsHostMenu[counterButton]->rect) ){
                                // controlHoverButton(mainRenderer,buttonsHostMenu,counterButton,sizeArrayButtons);
                                updateMenuButtonColor(mainRenderer, buttonsHostMenu[counterButton],  buttonsHostMenu[counterButton]->color);

                            }
                        } 

                        for(unsigned short counterMetroStations=0;counterMetroStations< backgroundMenu->sizeArrMetroStations;counterMetroStations++){
                            
                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&backgroundMenu->arrMetroStations[counterMetroStations]->rect)||SDL_HasIntersection(&absolutePathPointToDstPointRect,&backgroundMenu->arrMetroStations[counterMetroStations]->rect)){
                                displayMetroStation(mainRenderer,backgroundMenu->arrMetroStations[counterMetroStations],&backgroundMenu->arrMetroStations[counterMetroStations]->color,&backgroundMenu->arrMetroStations[counterMetroStations]->insideColor);
                                backgroundMenu->arrMetroStations[counterMetroStations]->display=0;
                            }
                        } 
                        break;
                    }
                }         
            }
        }    
    }  
    return 1;
}

short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations){

    // printf("arrMetroLine : %p",**arrMetroLines);
    // printf("sizeArrayMetroLine : %d",sizeArrMetroLines);
    for(unsigned short counterMetroLine=0; counterMetroLine<sizeArrMetroLines;counterMetroLine++){
        // printf("metroLineFunc : %p\n",(*arrMetroLines)[counterMetroLine]);
        if((*arrMetroLines)[counterMetroLine]!=0){
        // printf("counterMetroLine: %d",counterMetroLine);

            for(unsigned short counterMetroSegment=0; counterMetroSegment<(*arrMetroLines)[counterMetroLine]->sizeArrSegment;counterMetroSegment++){
        // printf("SIZE ARR SEGMENT : %d\n",(*arrMetroLines)[counterMetroLine]->sizeArrSegment);
                
                // printf("OK");
                if((*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->display && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->display){

                    if((counterMetroSegment==0 || (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment-1]->display ) && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display==0 ){

        // printf("counterMetroLine: %d",counterMetroLine);

                        updateDisplayMetroSegment(mainRenderer, (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment], (*arrMetroLines)[counterMetroLine]);

                        SDL_Rect absoluteSrcPointToPathPointRect;
                        SDL_Rect absolutePathPointToDstPointRect;

                        absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
                        absolutePathPointToDstPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

                        for(unsigned short counterMetroStations=0;counterMetroStations< sizeArrMetroStations;counterMetroStations++){
                            
                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&(*arrMetroStations)[counterMetroStations]->rect)||SDL_HasIntersection(&absolutePathPointToDstPointRect,&(*arrMetroStations)[counterMetroStations]->rect)){
                                updateColorMetroStations(mainRenderer,arrMetroStations,sizeArrMetroStations);
                                // displayMetroStation(mainRenderer,(*arrMetroStations)[counterMetroStations],&(*arrMetroStations)[counterMetroStations]->color,&(*arrMetroStations)[counterMetroStations]->insideColor);
                                // (*arrMetroStations)[counterMetroStations]->display=0;
                            }
                        } 
                        break;
                    }
                }         
            }
        }    
    }  
    return 1;
}







short  updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons,MenuLevel menuOrLevel){

    int geometricShape=0;
    unsigned short counterButton=0;

        for(unsigned short counterMetroStations=0; counterMetroStations<backgroundMenu->countMetroStation; counterMetroStations++){
           if(displayMetroStation(mainRenderer,backgroundMenu->arrMetroStations[counterMetroStations],&backgroundMenu->arrMetroStations[counterMetroStations]->color,&backgroundMenu->arrMetroStations[counterMetroStations]->insideColor)){
                if(menuOrLevel==_MENU_){

                    for(counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                        if(SDL_HasIntersection(&backgroundMenu->arrMetroStations[counterMetroStations]->rect,&buttonsHostMenu[counterButton]->rect)){

                            updateMenuButtonColor(mainRenderer, buttonsHostMenu[counterButton],  buttonsHostMenu[counterButton]->color);
                        } 
                    } 
                } 
            }   
        }

    return (short)1;
}

short displayMetroStation(SDL_Renderer *mainRenderer, MetroStation *metroStation, SDL_Color *color, SDL_Color *insideColor){

    if(metroStation->display==0){

        metroStation->display=1;
        if((metroStation->surface=SDL_CreateRGBSurfaceWithFormat(0, metroStation->rect.w,metroStation->rect.h, 32, SDL_PIXELFORMAT_RGBA8888))!=NULL){
 
        }
        else{fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}

        drawGeometricShapeInGeometricShape(metroStation->surface,&metroStation->rect, SDL_MapRGBA(metroStation->surface->format,color->r,color->g,color->b,color->a), SDL_MapRGBA(metroStation->surface->format,insideColor->r,insideColor->g,insideColor->b,insideColor->a),metroStation->geometricShape,4,_BOTTOM_TOP_);
        
        if(metroStation->texture!=NULL){
            SDL_DestroyTexture(metroStation->texture);
            metroStation->texture=NULL;
        }
        
        metroStation->texture=SDL_CreateTextureFromSurface(mainRenderer,metroStation->surface);

        if(SDL_RenderCopy(mainRenderer,metroStation->texture,NULL,&metroStation->rect)==0){
            if(metroStation->surface!=NULL){
                SDL_FreeSurface(metroStation->surface);  
                metroStation->surface=NULL;
            } 
        }

        return 1;
    }

    return 0;
}

short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine){

    metroSegment->display=1;
    metroSegment->srcStation->display=0;
    metroSegment->dstStation->display=0;

    SDL_SetRenderDrawColor(mainRenderer,metroLine->color.r,metroLine->color.g,metroLine->color.b,metroLine->color.a);

    metroSegment->texture=SDL_CreateTexture(mainRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,metroSegment->rect.w,metroSegment->rect.h);

    SDL_SetTextureBlendMode(metroSegment->texture,SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(mainRenderer,metroSegment->texture);
    
    SDL_RenderFillRect(mainRenderer,&metroSegment->srcPointToPathPointRect);
    SDL_RenderFillRect(mainRenderer,&metroSegment->pathPointToDstPointRect);

    SDL_SetRenderDrawColor(mainRenderer,255,255,255,255);
    SDL_RenderDrawRect(mainRenderer,&metroSegment->srcPointToPathPointRect);
    SDL_RenderDrawRect(mainRenderer,&metroSegment->pathPointToDstPointRect);

    SDL_SetRenderTarget(mainRenderer,NULL);

    SDL_RenderCopy(mainRenderer,metroSegment->texture,NULL,&metroSegment->rect);

    return 1;
}
