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

//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//

void getSelectedMetroStations(MetroStation **arrMetroStations, MetroStation **srcMetroStation, MetroStation **dstMetroStation, int sizeArrMetroStation){

    *srcMetroStation=NULL;
    *dstMetroStation=NULL;
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
                if(displayMetroStation(mainRenderer, arrayMetroStation[currentMetroStation],&arrayMetroStation[currentMetroStation]->srcStationColor,&arrayMetroStation[currentMetroStation]->insideColor)==0){
                    createErrorReport("Impossible de mettre a jour l'affichage d'une station de metro",__FILE__,__LINE__,__DATE__,__TIME__);  
                    return 0;
                }
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
            if(updateColorMetroStation(mainRenderer,arrayMetroStation[counterMetroStation])==0){
                createErrorReport("Impossible de mettre a jour la couleur et l'affichage d'une station de metro",__FILE__,__LINE__,__DATE__,__TIME__);  
                return 0;
            }
            
        }
    }
    return countSelectedMetroStations;
}

//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//


short updateColorMetroStation(SDL_Renderer *mainRenderer,MetroStation *metroStation){

    metroStation->display=0;

    if(metroStation->selected==2){         
        if(displayMetroStation(mainRenderer, metroStation,&metroStation->dstStationColor,&metroStation->insideColor)==0){
            createErrorReport("Echec lors de la mise à jour de l'affichage d'une station de metro",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    }
    else if(metroStation->selected==1){
        if(displayMetroStation(mainRenderer, metroStation,&metroStation->srcStationColor,&metroStation->insideColor)==0){
            createErrorReport("Echec lors de la mise à jour de l'affichage d'une station de metro",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    }
    else if(metroStation->selected==0){
        if(displayMetroStation(mainRenderer, metroStation,&metroStation->color,&metroStation->insideColor)==0){
            createErrorReport("Echec lors de la mise à jour de l'affichage d'une station de metro",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    }
    return 1;
}

short  updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons,MenuLevel menuOrLevel){

    unsigned short counterButton=0;

        for(unsigned short counterMetroStations=0; counterMetroStations<backgroundMenu->countMetroStation; counterMetroStations++){
            if(updateColorMetroStation(mainRenderer,backgroundMenu->arrMetroStations[counterMetroStations])==0){
                createErrorReport("Echec lors de la mise à jour de la couleur d'une station",__FILE__,__LINE__,__DATE__,__TIME__);           
                return 0;  
            }
            if(menuOrLevel==_MENU_){

                for(counterButton=0; counterButton<sizeArrayButtons; counterButton++){
                    if(SDL_HasIntersection(&backgroundMenu->arrMetroStations[counterMetroStations]->rect,&buttonsHostMenu[counterButton]->rect)){
                        if(updateMenuButtonColor(mainRenderer, buttonsHostMenu[counterButton],  buttonsHostMenu[counterButton]->color)==0){
                            createErrorReport("Echec lors du changment de couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                    } 
                } 
            } 
        }
    return 1;
}

short displayMetroStation(SDL_Renderer *mainRenderer, MetroStation *metroStation, SDL_Color *color, SDL_Color *insideColor){

    if(metroStation->display==0){

        metroStation->display=1;
        if((metroStation->surface=SDL_CreateRGBSurfaceWithFormat(0, metroStation->rect.w,metroStation->rect.h, 32, SDL_PIXELFORMAT_RGBA8888))==NULL){
            fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }

        if(drawGeometricShapeInGeometricShape(metroStation->surface,&metroStation->rect, SDL_MapRGBA(metroStation->surface->format,color->r,color->g,color->b,color->a), SDL_MapRGBA(metroStation->surface->format,insideColor->r,insideColor->g,insideColor->b,insideColor->a),metroStation->geometricShape,4,_BOTTOM_TOP_)==0){
            createErrorReport("Echec lors de la création d'une forme géométrique vide",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
        
        if(metroStation->texture!=NULL){
            SDL_DestroyTexture(metroStation->texture);
            metroStation->texture=NULL;
        }
        
        if((metroStation->texture=SDL_CreateTextureFromSurface(mainRenderer,metroStation->surface))==NULL){
            fprintf(stderr,"Echec lors la creation de la texture a partir d'une surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }

        if(SDL_RenderCopy(mainRenderer,metroStation->texture,NULL,&metroStation->rect)==0){
            if(metroStation->surface!=NULL){
                SDL_FreeSurface(metroStation->surface);  
                metroStation->surface=NULL;
            } 
        }
    }
    return 1;
}

//
// ─── FONCTIONS DE GESTION DE POSITION  ─────────────────────────
//


SDL_Rect controlOverlapMetroStations(MetroStation ***arrMetroStations, unsigned short counterMetroStations,SDL_Rect *parentRect,int sizeMetroStation, double sizeFactor){

    SDL_Rect riskRect;
    SDL_Rect verticalRayCaster;
    SDL_Rect horizontalRayCaster;
    int maxSize=sizeMetroStation*sizeFactor;

    //Les rayCaster nous permettent de contrôler que d'autre station se trouvent pas sur des x et y relativement similaires au rect controle, cela permet d'avoir une repartition plus aerer des stations de metro dans le background
 
    riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize);   
    verticalRayCaster=verticalRectInParentRect(&riskRect,parentRect);
    horizontalRayCaster=horizontalRectInParentRect(&riskRect,parentRect);

    for(unsigned short controlCounterMetroStation=0; controlCounterMetroStation<counterMetroStations; controlCounterMetroStation++){

        if(SDL_HasIntersection(&(*arrMetroStations)[controlCounterMetroStation]->rect,&verticalRayCaster)||SDL_HasIntersection(&(*arrMetroStations)[controlCounterMetroStation]->rect,&horizontalRayCaster)){  
            riskRect=SDLChangeRect(randInRange(parentRect->x+maxSize,parentRect->w-maxSize),randInRange(parentRect->y+maxSize,parentRect->h-maxSize)-maxSize, maxSize, maxSize); 
            verticalRayCaster=verticalRectInParentRect(&riskRect,parentRect);
            horizontalRayCaster=horizontalRectInParentRect(&riskRect,parentRect);
            controlCounterMetroStation=0;
        }
    } 

    return SDLChangeRect(riskRect.x,riskRect.y,sizeMetroStation,sizeMetroStation);
}


//
// ─── FONCTIONS DE MANIPULATION DE POINTEURS DE STATIONS DE METRO ──────────────────────────
//

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


//
// ─── FONCTIONS DE CREATION DE STATIONS DE METRO ───────────────────────
//


short SDLCreateMetroStations(SDLBackground *background, MenuLevel menuOrLevel){

SDL_Rect rectStation;
SDL_Color waterColor={211,237,248,255};
SDL_Color color={0,0,0,255};
SDL_Color insideColor={255,255,255,255};

int geometricShape;
short searchReturn=0;

    for(short counterMetroStations=0; counterMetroStations<background->sizeArrMetroStations; counterMetroStations++){

        counterMetroStations=counterMetroStations<0?0:counterMetroStations;

        geometricShape=rand()%3;
        rectStation=controlOverlapMetroStations(&background->arrMetroStations, counterMetroStations, &background->rect,background->sizeMetroStation,1.25);

        if(menuOrLevel==_LEVEL_){
            if((searchReturn=searchColorInSurface(&waterColor,&rectStation,background->surface,1))==-1){
                createErrorReport("Echec lors du controle de selection de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            else if(searchReturn){
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
    return 1;         
}
