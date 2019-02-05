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
#include <SDLTransport.h>

#include <SDL.h>

//
// ─── FONCTIONS EVENEMENTIELS ─────────────────────────────────────────────────────
//

short transportEventManager(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *leftContainer, SDLContainer *rightContainer, MetroLine ***arrMetroLines , Car ***arrCar, Engine ***arrEngine,int sizeArrMetroLine,unsigned short *sizeArrCar, unsigned short *sizeArrEngine, unsigned short transportSize,  SDL_Point *mousePoint,  short selectBool){

    short selectedTransportSigned = getSelectedTransportButton(leftContainer);
    short counterMetroLine = getSelectedMetroLineCounter(rightContainer);

    if(selectBool){
        if(selectedTransportSigned!=-1&&counterMetroLine!=-1){
            ButtonName selectedTransport= selectedTransportSigned;

            if(selectedTransport==_ENGINE_BTN_){
                for(unsigned short counterEngine=0;counterEngine<*sizeArrEngine; counterEngine++){
                    if((*arrEngine)[counterEngine]==NULL){
                        if(createTransport(mainRenderer,NULL,&(*arrEngine)[counterEngine],&(*arrMetroLines)[counterMetroLine],transportSize,0,_ENGINE_)==0){
                            createErrorReport("Echec lors de la creation d'un transport",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                        break;
                    }
                }
                
            }
        }   
    }
    return 1;
}

//
// ─── FONCTIONS D'AFFICHAGE ───────────────────────────────────────────────────────
//

short updateDisplayEngines(SDL_Renderer *mainRenderer, SDLBackground *background,Engine ***arrEngine, MetroLine ***arrMetroLine, MetroStation ***arrMetroStation,unsigned short sizeArrEngine, unsigned short sizeArrMetroLine, int sizeArrMetroStation ){

    for(unsigned short counterEngine=0;counterEngine<sizeArrEngine; counterEngine++){

        if((*arrEngine)[counterEngine]!=NULL){
            
            if(SDL_RenderCopy(mainRenderer, background->texture, &(*arrEngine)[counterEngine]->rect, &(*arrEngine)[counterEngine]->rect)!=0){
                fprintf(stderr,"Echec lors de la copie d'une texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
                return 0;
            }
            if(controlTransportIntersection(mainRenderer,&(*arrEngine)[counterEngine],arrMetroStation,sizeArrMetroStation,arrMetroLine,sizeArrMetroLine)==0){
                createErrorReport("Echec lors du control des intersection d'un transport.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            defineNewEngineOrientation(&(*arrEngine)[counterEngine]);
            defineNewEnginePosition(&(*arrEngine)[counterEngine]); 
            defineNewEngineDirection( &(*arrEngine)[counterEngine]);
            if(copyTransportTexture(mainRenderer,&(*arrEngine)[counterEngine])==0){
                createErrorReport("Echec lors de la copie d'une texture de transport.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    return 1;
}

short copyTransportTexture(SDL_Renderer *mainRenderer, Engine **engine){

    switch ((*engine)->orientation){
        case _LEFT_RIGHT_:
            if(SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,90,NULL,SDL_FLIP_HORIZONTAL)!=0){
                fprintf(stderr,"Echec lors de la copie d'une texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
                return 0;
            }
        break;
        case _RIGHT_LEFT_:
            if(SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,-90,NULL,SDL_FLIP_HORIZONTAL)!=0){
                fprintf(stderr,"Echec lors de la copie d'une texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
                return 0;
            }
        break;
        case _BOTTOM_TOP_:
            if(SDL_RenderCopy(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect)!=0){
                fprintf(stderr,"Echec lors de la copie d'une texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
                return 0;
            }
        break;
        case _TOP_BOTTOM_:
            if(SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,-180,NULL,SDL_FLIP_HORIZONTAL)!=0){
                fprintf(stderr,"Echec lors de la copie d'une texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
                return 0;
            }           
        break;
    }
    return 1;
}

short controlTransportIntersection(SDL_Renderer *mainRenderer,Engine **engine, MetroStation ***arrMetroStation,int sizeArrMetroStation, MetroLine ***arrMetroLine, int sizeArrMetroLine){

    for(unsigned short counterMetroLine=0;counterMetroLine<sizeArrMetroLine; counterMetroLine++){

        for(int counterMetroSegment=0; counterMetroSegment<(*arrMetroLine)[counterMetroLine]->sizeArrSegment;counterMetroSegment++){

            SDL_Rect absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
            SDL_Rect absolutePathPointToDstPointRect=absoluteRectPositionInRect(&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

            if(SDL_HasIntersection(&(*engine)->rect,&absoluteSrcPointToPathPointRect)||SDL_HasIntersection(&(*engine)->rect,&absolutePathPointToDstPointRect)){
                if(updateDisplayMetroSegment(mainRenderer, (*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment], (*arrMetroLine)[counterMetroLine])==0){
                    createErrorReport("Echec lors de la mise a jour de l'affichage d'un segment",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
                if(updateColorMetroStation(mainRenderer,(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation)==0||updateColorMetroStation(mainRenderer,(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation)==0){
                    createErrorReport("Echec lors de la mise a jour de la couleur d'une station",__FILE__,__LINE__,__DATE__,__TIME__);           
                    return 0;  
                }
            }
        }
    }

    for(unsigned short counterMetroStation=0;counterMetroStation<sizeArrMetroStation; counterMetroStation++){

        if((*arrMetroStation)[counterMetroStation]->display&&SDL_HasIntersection(&(*engine)->rect,&(*arrMetroStation)[counterMetroStation]->rect)){
            if(updateColorMetroStation(mainRenderer, (*arrMetroStation)[counterMetroStation])==0){
                createErrorReport("Echec lors de la mise a jour de la couleur d'une station",__FILE__,__LINE__,__DATE__,__TIME__);           
                return 0;  
            }
        }
    }
    return 1;
}

//
// ─── FONCTIONS DE GESTION DE POSITION ET DE DEPLACEMENT ─────────────────────────
//

void defineNewEnginePosition(Engine **engine){

    switch ((*engine)->orientation){
        case _LEFT_RIGHT_:
            (*engine)->rect.x++;
        break;
        case _RIGHT_LEFT_:
            (*engine)->rect.x--;
        break;
        case _BOTTOM_TOP_:
            (*engine)->rect.y--;
        break;
        case _TOP_BOTTOM_:
            (*engine)->rect.y++;            
        break;
    }
}

void controlDirectionPointer(Engine **engine){

    if((*engine)->currentMetroSegment->nextSegment==NULL){
        (*engine)->direction=_BACKWARD_;
    }
    else if((*engine)->currentMetroSegment->precedentSegment==NULL){
        (*engine)->direction=_FORWARD_;
    }

}

Direction controlDirectionPosition(Engine **engine){

    Direction lastDirection=-1;
    switch ((*engine)->orientation){
        case _LEFT_RIGHT_:
            if((*engine)->rect.x+(*engine)->rect.w/2==(*engine)->dstPoint.x && (*engine)->rect.y+(*engine)->rect.h/2==(*engine)->dstPoint.y){
                lastDirection= (*engine)->direction;
                controlDirectionPointer(engine);
            }
        break;
        case _RIGHT_LEFT_:
            if((*engine)->rect.x-(*engine)->rect.w/2==(*engine)->dstPoint.x && (*engine)->rect.y+(*engine)->rect.h/2==(*engine)->dstPoint.y){
                lastDirection= (*engine)->direction;
                controlDirectionPointer(engine);
            }
        break;
        case _BOTTOM_TOP_:
            if((*engine)->rect.y-(*engine)->rect.h/2==(*engine)->dstPoint.y && (*engine)->rect.x+(*engine)->rect.w/2==(*engine)->dstPoint.x){
                lastDirection= (*engine)->direction;
                controlDirectionPointer(engine);
            }
        break;
        case _TOP_BOTTOM_:
            if((*engine)->rect.y+(*engine)->rect.h/2==(*engine)->dstPoint.y && (*engine)->rect.x+(*engine)->rect.w/2==(*engine)->dstPoint.x){
                lastDirection= (*engine)->direction;
                controlDirectionPointer(engine);
            }      
        break;
    }
    return lastDirection;
}


void defineNewEngineDirection(Engine **engine){

    Direction lastDirection;
    
    if((lastDirection=controlDirectionPosition(engine))!=-1){

        SDL_Point precedentPoint;
         if((*engine)->direction==_FORWARD_){

            if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->nextSegment!=NULL){              
                precedentPoint=(*engine)->dstPoint;
                definePositionAndOrientationEngine(engine, &precedentPoint, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect);
            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->nextSegment!=NULL){             
                (*engine)->currentMetroSegment=(*engine)->currentMetroSegment->nextSegment;
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine, &precedentPoint, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect);
            }    
        }
        else if((*engine)->direction==_BACKWARD_){
            if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment!=NULL){                         
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine,NULL, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect);
            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment!=NULL){
                (*engine)->currentMetroSegment=(*engine)->currentMetroSegment->precedentSegment;
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine,&precedentPoint, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect);
            }
            else if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){
                precedentPoint=(*engine)->dstPoint;
                definePositionAndOrientationEngine(engine,&precedentPoint, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect);
            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){               
                (*engine)->direction=_FORWARD_;
                definePositionAndOrientationEngine(engine, NULL, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect);
            }
        }
    }
}



void defineNewEngineOrientation(Engine **engine){

          
    switch ((*engine)->orientation){
        case _LEFT_RIGHT_:
            if((*engine)->rect.x+(*engine)->rect.w/2==(*engine)->pathPoint.x && (*engine)->rect.y+(*engine)->rect.h/2==(*engine)->srcPoint.y){
                (*engine)->orientation=defineOrientation(&(*engine)->pathPoint,&(*engine)->dstPoint);                  
                centerRectOnPoint(&(*engine)->rect,&(*engine)->dstPoint,_X_);
            }
        break;
        case _RIGHT_LEFT_:
            if((*engine)->rect.x-(*engine)->rect.w/2==(*engine)->pathPoint.x && (*engine)->rect.y+(*engine)->rect.h/2==(*engine)->srcPoint.y){
                (*engine)->orientation=defineOrientation(&(*engine)->pathPoint,&(*engine)->dstPoint);
                centerRectOnPoint(&(*engine)->rect,&(*engine)->dstPoint,_X_);
            }
        break;
        case _BOTTOM_TOP_:
            if((*engine)->rect.y-(*engine)->rect.h/2==(*engine)->pathPoint.y && (*engine)->rect.x+(*engine)->rect.w/2==(*engine)->srcPoint.x){
                (*engine)->orientation=defineOrientation(&(*engine)->pathPoint,&(*engine)->dstPoint);
                centerRectOnPoint(&(*engine)->rect,&(*engine)->dstPoint,_Y_);
            }
        break;
        case _TOP_BOTTOM_:
            if((*engine)->rect.y+(*engine)->rect.h/2==(*engine)->pathPoint.y && (*engine)->rect.x+(*engine)->rect.w/2==(*engine)->srcPoint.x){
                (*engine)->orientation=defineOrientation(&(*engine)->pathPoint,&(*engine)->dstPoint);
                centerRectOnPoint(&(*engine)->rect,&(*engine)->dstPoint,_Y_);
            }      
        break;
    }
}

short createTransport(SDL_Renderer *mainRenderer,Car **car, Engine **engine, MetroLine **metroLine, unsigned short transportSize,unsigned short sizeArrPassenger, TransportType transportType){


    switch(transportType){

        case _CAR_:
            // createCar(engine,car, metroLine,transportSize,sizeArrPassenger);
        break;

        case _ENGINE_:
            if(createEngine(mainRenderer,engine,metroLine,transportSize)==0){
                createErrorReport("Echec lors de la creation d'une locomotive",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        break;

    }

    return 1;
}

short createEngine(SDL_Renderer *mainRenderer, Engine **engine,MetroLine **metroLine, unsigned short transportSize){

    if((*engine)==NULL){
        if(((*engine)=malloc(sizeof(Engine)))==NULL){
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    }   

    if((*metroLine)->arrMetroSegment[0]!=NULL){
        (*engine)->currentMetroSegment=(*metroLine)->arrMetroSegment[0];
        (*engine)->precedentCar=NULL;
        (*engine)->rect=SDLChangeRect(0,0,transportSize,transportSize);

        definePositionAndOrientationEngine(engine,NULL, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect,  &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->srcPointToPathPointRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect, &(*engine)->currentMetroSegment->rect);
        (*engine)->color=(*metroLine)->color;
        (*engine)->insideColor=SDLChangeRGBColor((*metroLine)->color.r+20,(*metroLine)->color.g+20,(*metroLine)->color.b+20,(*metroLine)->color.a);
        (*engine)->surface=SDL_CreateRGBSurfaceWithFormat(0,(*engine)->rect.w,(*engine)->rect.h,32,SDL_PIXELFORMAT_RGBA8888);

        if(drawGeometricShapeInGeometricShape((*engine)->surface,&(*engine)->rect,
        SDL_MapRGBA((*engine)->surface->format,(*engine)->color.r,(*engine)->color.g,(*engine)->color.b,(*engine)->color.a),
        SDL_MapRGBA((*engine)->surface->format,(*engine)->insideColor.r,(*engine)->insideColor.g,(*engine)->insideColor.b,(*engine)->insideColor.a),_TRIANGLE_,4,_BOTTOM_TOP_)==0){
            createErrorReport("Echec lors de la création d'une forme géométrique vide",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }

        if(((*engine)->texture=SDL_CreateTextureFromSurface(mainRenderer,(*engine)->surface))==NULL){
            fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
        if(SDL_SetTextureBlendMode((*engine)->texture,SDL_BLENDMODE_BLEND)!=0){
            fprintf(stderr,"Echec lors du réglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
        (*engine)->display=0;
        (*engine)->direction=_FORWARD_;
    } 
    return 1;
}


void definePositionAndOrientationEngine(Engine **engine,SDL_Point *precedentPathPoint, SDL_Point *relativeSrcPoint,SDL_Point *relativePathPoint, SDL_Point *relativeDstPoint, SDL_Rect *relativeSrcRect, SDL_Rect *relativeDstRect, SDL_Rect *parentRect  ){

    SDL_Point tmpPrecedentPathPoint;
    if(precedentPathPoint!=NULL){
        tmpPrecedentPathPoint=*precedentPathPoint;
    }
    SDL_Point tmpSrcPoint=*relativeSrcPoint;
    SDL_Point tmpDstPoint=*relativePathPoint;

    setPointsPositionInRect(&tmpSrcPoint,&tmpDstPoint,relativeSrcRect,parentRect);
    (*engine)->srcPoint=tmpSrcPoint;
    (*engine)->pathPoint=tmpDstPoint;
    tmpSrcPoint=*relativePathPoint;
    tmpDstPoint=*relativeDstPoint;

    setPointsPositionInRect(&tmpSrcPoint,&tmpDstPoint,relativeDstRect,parentRect);
    (*engine)->dstPoint=tmpDstPoint;

    (*engine)->orientation=defineOrientation(&(*engine)->srcPoint,&(*engine)->pathPoint);
    if((*engine)->orientation==_TOP_BOTTOM_ || (*engine)->orientation==_BOTTOM_TOP_ ){
        if(precedentPathPoint!=NULL){
            centerRectOnPoint(&(*engine)->rect,&tmpPrecedentPathPoint,_Y_);
        }
        else{
            centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_Y_);
        }
        centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_X_);
    }
    else{
        if(precedentPathPoint!=NULL){
            centerRectOnPoint(&(*engine)->rect,&tmpPrecedentPathPoint,_X_);
        }
        else{
            centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_X_);
        }
        centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_Y_);
    }

}

// void createCar(Engine **engine,Car **car,MetroLine **metroLine, unsigned short transportSize, unsigned short sizeArrPassenger){

//     if(*car==NULL){
//         (*car)=malloc(sizeof(Car));
//     }   

//     if((*engine)!=NULL){
//         if((*engine)->precedentCar==NULL){
//             (*engine)->precedentCar=(*car);
//             (*car)->engine=(*engine);
//             (*car)->orientation=(*car)->engine->orientation;
//             setRectBehindRectWithOrientation(&(*car)->rect,&(*car)->engine->rect,(*car)->orientation);
//         }
//         if((*engine)->precedentCar!=NULL){
//             Car *nextCar=(*engine)->precedentCar;
//             while(nextCar->precedentCar!=NULL){
//                 nextCar=nextCar->precedentCar;
//             }
//             (*car)->nextCar=nextCar;
//             (*car)->engine=NULL;
//             nextCar->precedentCar=(*car);
//             (*car)->orientation=(*car)->nextCar->orientation;
//             setRectBehindRectWithOrientation(&(*car)->rect,&(*car)->nextCar,(*car)->orientation);
//         }
//         (*car)->precedentCar=NULL;   
//         (*car)->surface=SDL_CreateRGBSurfaceWithFormat(0,transportSize,transportSize,32,SDL_PIXELFORMAT_RGBA8888);
//         (*car)->color=(*metroLine)->color;
//         (*car)->insideColor=SDLChangeRGBColor((*metroLine)->color.r+20,(*metroLine)->color.g+20,(*metroLine)->color.b+20,(*metroLine)->color.a);
//         (*car)->display=0;
//         (*car)->arrPassenger=malloc(sizeof(Passenger*)*sizeArrPassenger);
//         for(unsigned short counterPassenger=0;counterPassenger<sizeArrPassenger;counterPassenger++){
//             (*car)->arrPassenger[counterPassenger]=malloc(sizeof(Passenger));
//         }
//     }  
// }
