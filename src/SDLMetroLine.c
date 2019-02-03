
#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>
#include <SDLMetroLine.h>
#include <SDLMetroStation.h>

#include<SDL.h>



////////////////////// FONCTIONS DEDIEES AU MENU ////////////////////


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

                if(counterMetroSegment==0){
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment=NULL;
                }
                else{
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment=backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment-1];
                }

                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],0);

                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment+1],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],1);

                createGeometryMetroSegment(
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment, 
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation, 
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation, 
                    counterMetroLine,  backgroundMenu->metroLineThickness);
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





//////////////////////// FONCTIONS DEDIEES AUX NIVEAUX ////////////////////////

short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations){


    for(unsigned short counterMetroLine=0; counterMetroLine<sizeArrMetroLines;counterMetroLine++){

        if((*arrMetroLines)[counterMetroLine]!=0){


            for(unsigned short counterMetroSegment=0; counterMetroSegment<(*arrMetroLines)[counterMetroLine]->sizeArrSegment;counterMetroSegment++){

                if((*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->display && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->display){

                    if((counterMetroSegment==0 || (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment-1]->display ) && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display==0 ){

                        updateDisplayMetroSegment(mainRenderer, (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment], (*arrMetroLines)[counterMetroLine]);

                        SDL_Rect absoluteSrcPointToPathPointRect;
                        SDL_Rect absolutePathPointToDstPointRect;

                        SDL_Point absoluteSrcPoint;
                        SDL_Point absolutePathPoint;


                        absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
                        absolutePathPointToDstPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);


                        for(unsigned short counterMetroStations=0;counterMetroStations< sizeArrMetroStations;counterMetroStations++){
                            
                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&(*arrMetroStations)[counterMetroStations]->rect)||SDL_HasIntersection(&absolutePathPointToDstPointRect,&(*arrMetroStations)[counterMetroStations]->rect)){
                                updateColorMetroStation(mainRenderer,(*arrMetroStations)[counterMetroStations]);
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


short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine){

    //Indique que le segment est affiché et indique que les stations ne sont pas affiché pour mise à jour ultérieure
    metroSegment->display=1;
    metroSegment->srcStation->display=0;
    metroSegment->dstStation->display=0;

    SDL_SetRenderDrawColor(mainRenderer,metroLine->color.r,metroLine->color.g,metroLine->color.b,metroLine->color.a);

    if(metroSegment->texture==NULL){
        printf("TEXTURE SEGMENT : %p",metroSegment->texture);
        metroSegment->texture=SDL_CreateTexture(mainRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,metroSegment->rect.w,metroSegment->rect.h);

        SDL_SetTextureBlendMode(metroSegment->texture,SDL_BLENDMODE_BLEND);

        SDL_SetRenderTarget(mainRenderer,metroSegment->texture);
        
        SDL_RenderFillRect(mainRenderer,&metroSegment->srcPointToPathPointRect);
        SDL_RenderFillRect(mainRenderer,&metroSegment->pathPointToDstPointRect);

        //Colorie le contour de la ligne en blanc
        SDL_SetRenderDrawColor(mainRenderer,255,255,255,255);
        SDL_RenderDrawRect(mainRenderer,&metroSegment->srcPointToPathPointRect);
        SDL_RenderDrawRect(mainRenderer,&metroSegment->pathPointToDstPointRect);

        SDL_SetRenderTarget(mainRenderer,NULL);
    }

    SDL_RenderCopy(mainRenderer,metroSegment->texture,NULL,&metroSegment->rect);

    return 1;
}




void createGeometryMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, MetroStation * srcStation, MetroStation *dstStation, short counterMetroLine, short metroLineThickness){

    currentMetroSegment->srcStation=srcStation;
    currentMetroSegment->dstStation=dstStation;

    createRectBetweenTwoRect(
       &currentMetroSegment->srcStation->rect,&currentMetroSegment->dstStation->rect,&currentMetroSegment->rect,&currentMetroSegment->srcPointInRect,&currentMetroSegment->dstPointInRect);

   currentMetroSegment->display=0;

    shiftPointPositionMetroLine(&currentMetroSegment->rect,&currentMetroSegment->srcPointInRect, counterMetroLine,metroLineThickness);

    shiftPointPositionMetroLine(&currentMetroSegment->rect,&currentMetroSegment->dstPointInRect, counterMetroLine,metroLineThickness);


    if(precedentMetroSegment!=NULL){
        preparePathRectMetroSegment(currentMetroSegment, precedentMetroSegment,metroLineThickness, counterMetroLine);
    }
    else{
        preparePathRectMetroSegment(currentMetroSegment, NULL,metroLineThickness,counterMetroLine);
    }
}

void metroLineEventManagerLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *container, MetroLine **arrMetroLines , MetroStation **arrMetroStations, int sizeArrMetroLine,int sizeArrMetroStations, unsigned short metroLineThickness, SDL_Point *mousePoint, short selectBool, ContainerPosition containerPosition){

    short metroLineCounter;

    printf("background texture avant :%p",background->texture);

    if(containerPosition==_RIGHT_){
        metroLineCounter=getSelectedMetroLineCounter(container);
    }

        if((metroLineCounter)!=-1){

            for(int counterMetroStation=0; counterMetroStation<sizeArrMetroStations; counterMetroStation++){
                if(hasIntersectPointRect(mousePoint,&arrMetroStations[counterMetroStation]->rect) && arrMetroStations[counterMetroStation]->display){
                    if(controlSelectedMetroStation(mainRenderer, arrMetroStations,counterMetroStation, sizeArrMetroStations,selectBool)==2){    
                        manageMetroSegmentLevel(NULL,NULL,&arrMetroLines[metroLineCounter],arrMetroStations,NULL,sizeArrMetroStations,metroLineCounter,metroLineThickness,selectBool);
                    }
                }
            } 

            for(int metroSegmentCounter=0; metroSegmentCounter < arrMetroLines[metroLineCounter]->sizeArrSegment; metroSegmentCounter++){

                SDL_Rect absolutePathPointToDstPointRect= absoluteRectPositionInRect(&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->pathPointToDstPointRect,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->rect);
                SDL_Rect absoluteSrcPointToPathPointRect= absoluteRectPositionInRect(&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->srcPointToPathPointRect,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->rect);
                
                if((hasIntersectPointRect(mousePoint,&absolutePathPointToDstPointRect) || hasIntersectPointRect(mousePoint,&absoluteSrcPointToPathPointRect)) && selectBool==0 ){
                    manageMetroSegmentLevel(mainRenderer,background,&arrMetroLines[metroLineCounter],NULL,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter],0,metroLineCounter,metroLineThickness,selectBool);
                    printf("sizeApres delete :%d\n",arrMetroLines[metroLineCounter]->sizeArrSegment);
                }   
            }
    }
}


void manageMetroSegmentLevel(SDL_Renderer *mainRenderer, SDLBackground *background, MetroLine **metroLine, MetroStation **arrMetroStations, MetroSegment **currentMetroSegment, int sizeArrMetroStation, short counterMetroLine, short metroLineThickness,short addDeleteBool){


    if(addDeleteBool==1){

        MetroStation *srcMetroStation, *dstMetroStation;
        MetroSegment *newSegment;
        
        getSelectedMetroStations(arrMetroStations,&srcMetroStation,&dstMetroStation,sizeArrMetroStation);

        printf("arrMetroSegment avnt :%p",(*metroLine)->arrMetroSegment);
        printf("sizeArrSegment :%d\n",(*metroLine)->sizeArrSegment);

        if((newSegment=addNewSegment(&(*metroLine)->arrMetroSegment, &srcMetroStation , &dstMetroStation, &(*metroLine)->sizeArrSegment))!=NULL){

            printf("newSegment : %p",newSegment);
            newSegment->surface=NULL;
            newSegment->texture=NULL;
            
            createGeometryMetroSegment(newSegment, newSegment->precedentSegment, newSegment->srcStation, newSegment->dstStation, counterMetroLine, metroLineThickness);
        }   
    } 

    

    else if(addDeleteBool==0 && *currentMetroSegment!=NULL){
        
        printf("\nsizeArrAvant : %d\n",(*metroLine)->sizeArrSegment);
        deleteSegment(mainRenderer, background,&(*metroLine)->arrMetroSegment, currentMetroSegment,&(*metroLine)->sizeArrSegment);
        printf("\nsizeArrApres : %d\n",(*metroLine)->sizeArrSegment);

    }
}


void deleteSegment(SDL_Renderer *mainRenderer, SDLBackground *background,MetroSegment ***arrMetroSegment, MetroSegment **currentMetroSegment, unsigned short *sizeArrMetroSegment){

    printf("currentMetroSegment : %p\n",*currentMetroSegment);
    printf("nextSegment : %p\n",(*currentMetroSegment)->nextSegment);
    printf("precedentSegment : %p\n",(*currentMetroSegment)->precedentSegment);

    printf("BACKGROUND TEXTURE : %p",background->texture);

    if((*currentMetroSegment)->precedentSegment!=NULL){
        (*currentMetroSegment)->precedentSegment->nextSegment=NULL;
    }

    while((*currentMetroSegment)!=NULL){
        
        SDL_Rect absolutePathPointToDstPointRect= absoluteRectPositionInRect(&(*currentMetroSegment)->pathPointToDstPointRect,&(*currentMetroSegment)->rect);
        SDL_Rect absoluteSrcPointToPathPointRect= absoluteRectPositionInRect(&(*currentMetroSegment)->srcPointToPathPointRect,&(*currentMetroSegment)->rect);

        SDL_RenderCopy(mainRenderer,background->texture,&absolutePathPointToDstPointRect,&absolutePathPointToDstPointRect);
        SDL_RenderCopy(mainRenderer,background->texture,&absoluteSrcPointToPathPointRect,&absoluteSrcPointToPathPointRect);
        SDL_RenderPresent(mainRenderer);
        printf("renderer : %p\n",mainRenderer);
        // SDL_RenderCopy(mainRenderer,(*currentMetroSegment)->srcStation->texture,&(*currentMetroSegment)->srcStation->rect,&(*currentMetroSegment)->srcStation->rect);
        // SDL_RenderCopy(mainRenderer,(*currentMetroSegment)->dstStation->texture,&(*currentMetroSegment)->dstStation->rect,&(*currentMetroSegment)->dstStation->rect);
        // SDL_RenderPresent(mainRenderer);
        printf("currentMetroSegment : %p\n",*currentMetroSegment);
        // printf("COPY OK");
        if((*currentMetroSegment)->nextSegment!=NULL){
            (*currentMetroSegment)=(*currentMetroSegment)->nextSegment;
            freeMetroSegment((*currentMetroSegment)->precedentSegment);
            free((*currentMetroSegment)->precedentSegment);
            (*currentMetroSegment)->precedentSegment=NULL;
            printf("OK FREE\n");
        }
        else{
            freeMetroSegment(*currentMetroSegment);
            free(*currentMetroSegment);
            *currentMetroSegment=NULL;
            printf("OK FREE2\n");


        }

        printf("sizeArrPendant : %d\n",*sizeArrMetroSegment);
        (*sizeArrMetroSegment)--;
    }


    // printf("sizeArrPendant : %d\n",sizeArrMetroSegment);
    (*arrMetroSegment)=realloc((*arrMetroSegment),sizeof(MetroSegment*)*(*sizeArrMetroSegment));
    printf("fin boucle");


}

short getSegmentWithOrder(MetroSegment ***arrMetroSegment,MetroStation **srcStation , MetroStation **dstStation, unsigned short sizeArrSegment){

    
    MetroSegment *segment;
    short srcStationCounter=0;
    short dstStationCounter=0;

    if((*arrMetroSegment)[0]!=NULL){
        segment=(*arrMetroSegment)[0];
    }

    while(segment!=NULL){
        if(segment->srcStation==*dstStation||segment->dstStation==*dstStation){
            dstStationCounter ++;
        }
        if(segment->srcStation==*srcStation||segment->dstStation==*srcStation){
            srcStationCounter++;
        }
        segment=segment->nextSegment;
    }

    if(srcStationCounter>0 && dstStationCounter>0){
        return 0;
    }

    if((*arrMetroSegment)[sizeArrSegment-1]->dstStation==*srcStation||(*arrMetroSegment)[sizeArrSegment-1]->dstStation==*dstStation){
        return 2;
    }

    if((*arrMetroSegment)[0]->srcStation==*srcStation||(*arrMetroSegment)[0]->srcStation==*dstStation){
        return 1;
    }
    return 0;
}




MetroSegment *addNewSegment(MetroSegment ***arrMetroSegment, MetroStation **srcStation , MetroStation **dstStation, unsigned short *sizeArrMetroSegment ){

    short orderSegment=0;

    if(*sizeArrMetroSegment==0){

        (*arrMetroSegment)=realloc((*arrMetroSegment),(++*sizeArrMetroSegment)*sizeof(MetroSegment*));
        (*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment));
        (*arrMetroSegment)[*sizeArrMetroSegment-1]->precedentSegment=NULL;
        (*arrMetroSegment)[*sizeArrMetroSegment-1]->nextSegment=NULL;
        reorderSrcAndDestStations(&(*arrMetroSegment)[*sizeArrMetroSegment-1], srcStation, dstStation, 0);      

        return (*arrMetroSegment)[*sizeArrMetroSegment-1];
    }
    else{
        
        orderSegment=getSegmentWithOrder(arrMetroSegment,srcStation , dstStation,*sizeArrMetroSegment);

        if(orderSegment!=0){
            (*arrMetroSegment)=realloc((*arrMetroSegment),(++(*sizeArrMetroSegment))*sizeof(MetroSegment*));
            
        
            if(orderSegment==1){

                (*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment));
                reorderMetroSegmentsLastToFirst(arrMetroSegment,*sizeArrMetroSegment);
                (*arrMetroSegment)[0]->nextSegment=(*arrMetroSegment)[1];
                (*arrMetroSegment)[1]->precedentSegment=(*arrMetroSegment)[0];
                (*arrMetroSegment)[0]->precedentSegment=NULL;
                reorderSrcAndDestStations(&(*arrMetroSegment)[0], srcStation, dstStation, orderSegment);                   
                return (*arrMetroSegment)[0];
            }
            if(orderSegment==2){
                (*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment));
                (*arrMetroSegment)[*sizeArrMetroSegment-1]->precedentSegment=(*arrMetroSegment)[*sizeArrMetroSegment-2];
                (*arrMetroSegment)[*sizeArrMetroSegment-2]->nextSegment=(*arrMetroSegment)[*sizeArrMetroSegment-1];
                (*arrMetroSegment)[*sizeArrMetroSegment-1]->nextSegment=NULL;
                reorderSrcAndDestStations(&(*arrMetroSegment)[*sizeArrMetroSegment-1], srcStation, dstStation, orderSegment);       
                return (*arrMetroSegment)[*sizeArrMetroSegment-1];

            }  
        }
    }
    return NULL;
}

void reorderSrcAndDestStations(MetroSegment **currentMetroSegment, MetroStation **srcMetroStation, MetroStation **dstMetroStation, unsigned short order){


    switch (order){

        case 0:
            (*currentMetroSegment)->srcStation=*srcMetroStation;
            (*currentMetroSegment)->dstStation=*dstMetroStation;
        break;

        case 1:            
            if((*currentMetroSegment)->nextSegment->srcStation==*dstMetroStation){
                    (*currentMetroSegment)->srcStation=*srcMetroStation;
                    (*currentMetroSegment)->dstStation=(*currentMetroSegment)->nextSegment->srcStation;
                }
                else if((*currentMetroSegment)->nextSegment->srcStation==*srcMetroStation){
                    (*currentMetroSegment)->dstStation=(*currentMetroSegment)->nextSegment->srcStation;
                    (*currentMetroSegment)->srcStation=*dstMetroStation;          
                }
        break;

        case 2:
            if((*currentMetroSegment)->precedentSegment->dstStation==*srcMetroStation){
                    (*currentMetroSegment)->srcStation=*srcMetroStation;
                    (*currentMetroSegment)->dstStation=*dstMetroStation;
            }
            else if((*currentMetroSegment)->precedentSegment->dstStation==*dstMetroStation){
                (*currentMetroSegment)->srcStation=*dstMetroStation;
                (*currentMetroSegment)->dstStation=*srcMetroStation;          
            }
        break;
    }
    

}


void reorderMetroSegmentsLastToFirst(MetroSegment ***arrMetroSegment, unsigned short sizeArrSegment){

    MetroSegment *tmpSegment;
 
    tmpSegment=(*arrMetroSegment)[sizeArrSegment-1];

    for(unsigned short counterSegment = sizeArrSegment-1 ; counterSegment >0 ; counterSegment --){

    (*arrMetroSegment)[counterSegment]=(*arrMetroSegment)[(counterSegment-1)];
    }
    (*arrMetroSegment)[0]=tmpSegment;
}




//////////////////// FONCTIONS DE SUPPORT A LA CREATION DE SEGMENTS ET DE LIGNES ////////////////////



void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine){

    currentMetroSegment->pathPointInRect.x=currentMetroSegment->srcPointInRect.x;
    currentMetroSegment->pathPointInRect.y=currentMetroSegment->dstPointInRect.y;

    if(precedentMetroSegment!=NULL){

        avoidOverlapPathPointMetroSegment(
            &currentMetroSegment->pathPointInRect,
            &currentMetroSegment->rect,
            &precedentMetroSegment->pathPointInRect,
            &precedentMetroSegment->rect);      
    }

    placePointPositionInMiddleMetroStation(&currentMetroSegment->pathPointInRect,&currentMetroSegment->srcPointInRect, &currentMetroSegment->rect, &currentMetroSegment->srcStation->rect,currentMetroSegment->srcStation->geometricShape);
    placePointPositionInMiddleMetroStation(&currentMetroSegment->pathPointInRect,&currentMetroSegment->dstPointInRect, &currentMetroSegment->rect, &currentMetroSegment->dstStation->rect,currentMetroSegment->srcStation->geometricShape);

    setThicknessMetroSegmentRect(
    &currentMetroSegment->pathPointInRect,   
    &currentMetroSegment->srcPointInRect,
    &currentMetroSegment->rect,
    &currentMetroSegment->srcPointToPathPointRect,
    thickness, counterMetroLine);

    setThicknessMetroSegmentRect(
    &currentMetroSegment->pathPointInRect,
    &currentMetroSegment->dstPointInRect,
    &currentMetroSegment->rect,
    &currentMetroSegment->pathPointToDstPointRect,
    thickness, counterMetroLine);  
}

void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness){

    if(point->x==parentRect->w){
        point->x -= thickness * (counterMetroLine+1);
    }
    else{
        point->x += thickness * (counterMetroLine+1);
    }

    if(point->y==parentRect->h){
        point->y -= thickness * (counterMetroLine+1);
    }
    else{
        point->y += thickness * (counterMetroLine+1);
    }
}


void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine){

    SDL_Point tmpSrcPoint , tmpDstPoint;

    tmpSrcPoint = *srcPoint;
                         
    tmpDstPoint = *dstPoint;
            
    if(tmpSrcPoint.y==parentRect->h-(counterMetroLine+1)*thickness && tmpSrcPoint.y==tmpDstPoint.y){
        tmpSrcPoint.y-= thickness;
    }
    else if(tmpSrcPoint.y!=parentRect->h-(counterMetroLine+1)*thickness && tmpSrcPoint.y==tmpDstPoint.y) {
        tmpSrcPoint.y += thickness;
    }

    if(tmpSrcPoint.x==parentRect->w-(counterMetroLine+1)*thickness && tmpSrcPoint.x==tmpDstPoint.x){
        tmpSrcPoint.x-= thickness;
    }
    else if(tmpSrcPoint.x!=parentRect->w-(counterMetroLine+1)*thickness && tmpSrcPoint.x==tmpDstPoint.x) {
        tmpSrcPoint.x += thickness;
    }

    createRectBetweenTwoPoint(&tmpDstPoint,&tmpSrcPoint,finalRect,NULL,NULL);
}


void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect){

    SDL_Point tmpCurrentPathPoint, tmpPrecedentPathPoint;
    
    tmpCurrentPathPoint=absolutePointPositionInRect(currentPathPoint,currentRect);
    tmpPrecedentPathPoint=absolutePointPositionInRect(precedentPathPoint,precedentRect);

    if(tmpCurrentPathPoint.x==tmpPrecedentPathPoint.x && tmpCurrentPathPoint.y==tmpPrecedentPathPoint.y){

        currentPathPoint->x = currentPathPoint->x==0 ? currentRect->w : 0; 
        currentPathPoint->y = currentPathPoint->y==0 ? currentRect->h : 0; 
    }
}

// void avoidOverlapPathRectMetroSegment(SDL_Point *currentPathPoint,SDL_Rect *currentPathRect, SDL_Rect *currentParentRect, SDL_Point *otherPathRect, SDL_Rect *otherParentRect){

//     SDL_Rect tmpCurrentPathRect, tmpOtherPathRect;
    
//     tmpCurrentPathRect=absoluteRectPositionInRect(currentPathRect,currentParentRect);
//     tmpOtherPathRect=absoluteRectPositionInRect(otherPathRect,otherParentRect);

//     if(SDL_HasIntersection(&tmpCurrentPathRect,&tmpOtherPathRect)){

//         currentPathPoint->x = currentPathPoint->x==0 ? currentParentRect->w : 0; 
//         currentPathPoint->y = currentPathPoint->y==0 ? currentParentRect->h : 0; 
//     }
// }

void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape){

    SDL_Rect tmpRelativeRect; 

    tmpRelativeRect=relativeRectPositionInRect(dstRect,parentRect);

    if(dstPoint->x==srcPoint->x){
        if(geometricShape==_TRIANGLE_){       
            dstPoint->y=tmpRelativeRect.y+tmpRelativeRect.h;
        }
        else{
            dstPoint->y=tmpRelativeRect.y+tmpRelativeRect.h/2;
        }
    }

    else{
        dstPoint->x=tmpRelativeRect.x+tmpRelativeRect.w/2;
    }
}


void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool){

    if(srcDstBool){
        metroSegment->srcStation=metroStation;
    }
    else{
        metroSegment->dstStation=metroStation;
    }
        
}

