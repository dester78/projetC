#include <stdio.h>

#include <SDLColor.h>
#include <SDLMetroLine.h>
#include <SDLMetroStation.h>
#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>
#include <mathCalculation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLDraw.h>

#include <SDL.h>


void updateColorMetroStation(SDL_Renderer *mainRenderer,MetroStation *metroStation){


        // printf("metroStation : %p, counter : %d, selected : %d\n",arrMetroStations[counterMetroStation],counterMetroStation, arrMetroStations[counterMetroStation]->selected);
        metroStation->display=0;
        if(metroStation->selected==2){   
            displayMetroStation(mainRenderer, metroStation,&metroStation->dstStationColor,&metroStation->insideColor);
        }
        else if(metroStation->selected==1){
            displayMetroStation(mainRenderer, metroStation,&metroStation->srcStationColor,&metroStation->insideColor);
        }
        else if(metroStation->selected==0){
            displayMetroStation(mainRenderer, metroStation,&metroStation->color,&metroStation->insideColor);
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


// short controlMetroStationOnLine(MetroSegment *startMetroSegment, MetroStation *srcStation, MetroStation *dstStation){

//     MetroSegment *nextSegment;
//     while(startMetroSegment->nextSegment!=NULL){

//         nextSegment=startMetroSegment->nextSegment;

//         if(&nextSegment->dstStation!=NULL){

//             if(dstStation==nextSegment->dstStation){
//                 return 0;
//             }
//         }
//     }

//     while(startMetroSegment->precedentSegment!=NULL){

//         nextSegment=startMetroSegment->precedentSegment;

//         if(startMetroSegment->srcStation!=NULL&&nextSegment->srcStation!=NULL){
//             if(startMetroSegment->srcStation==nextSegment->srcStation){
//                 return 0;
//             }
//         }
//     }
//     return 1;
// }



SDL_Rect controlOverlapMetroStations(MetroStation **arrMetroStations, unsigned short counterMetroStations,SDL_Rect *parentRect,int sizeMetroStation, double sizeFactor){

    SDL_Rect riskRect;
    SDL_Rect verticalRayCaster;
    SDL_Rect horizontalRayCaster;

    int maxSize=sizeFactor*sizeMetroStation;
 
    riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize);   
    verticalRayCaster=verticalRectInParentRect(&riskRect,parentRect);

    horizontalRayCaster=horizontalRectInParentRect(&riskRect,parentRect);

    for(unsigned short controlCounterMetroStation=0; controlCounterMetroStation<counterMetroStations; controlCounterMetroStation++){

        if(SDL_HasIntersection(&arrMetroStations[controlCounterMetroStation]->rect,&verticalRayCaster)||SDL_HasIntersection(&arrMetroStations[controlCounterMetroStation]->rect,&horizontalRayCaster)){  
            riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize); 
            verticalRayCaster=verticalRectInParentRect(&riskRect,parentRect);
            horizontalRayCaster=horizontalRectInParentRect(&riskRect,parentRect);
  
            controlCounterMetroStation=0;
        }
    } 


    return SDLChangeRect(riskRect.x,riskRect.y,sizeMetroStation,sizeMetroStation);
}


void sortArrayMetroStationByDistance(MetroStation **arrMetroStations,unsigned short sizeArrMetroStations){

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

void fillArrayMetroStation(MetroStation **arrMetroStations, unsigned short sizeArrMetroStations){

    for(unsigned short counterMetroStations=0;counterMetroStations<sizeArrMetroStations;counterMetroStations++){

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

short  updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons,MenuLevel menuOrLevel){

    int geometricShape=0;
    unsigned short counterButton=0;

        for(unsigned short counterMetroStations=0; counterMetroStations<backgroundMenu->countMetroStation; counterMetroStations++){
            updateColorMetroStation(mainRenderer,backgroundMenu->arrMetroStations[counterMetroStations]);
            if(menuOrLevel==_MENU_){

                for(counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                    if(SDL_HasIntersection(&backgroundMenu->arrMetroStations[counterMetroStations]->rect,&buttonsHostMenu[counterButton]->rect)){

                        updateMenuButtonColor(mainRenderer, buttonsHostMenu[counterButton],  buttonsHostMenu[counterButton]->color);
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
    for(int counterMetroStation=0;counterMetroStation<sizeArrMetroStation;counterMetroStation++){
        if(arrayMetroStation[counterMetroStation]->display){
            updateColorMetroStation(mainRenderer,arrayMetroStation[counterMetroStation]);
        }
    }
    return countSelectedMetroStations;
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
        rectStation=controlOverlapMetroStations(background->arrMetroStations, counterMetroStations, &background->rect,background->sizeMetroStation,1.5);
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



