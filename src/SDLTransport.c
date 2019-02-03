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




void transportEventManager(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *leftContainer, SDLContainer *rightContainer, MetroLine ***arrMetroLines , Car ***arrCar, Engine ***arrEngine,int sizeArrMetroLine,unsigned short *sizeArrCar, unsigned short *sizeArrEngine, int transportSize,  SDL_Point *mousePoint, unsigned short metroLineThickness, short selectBool){

    short selectedTransportSigned = getSelectedTransportButton(leftContainer);
    short counterMetroLine = getSelectedMetroLineCounter(rightContainer);

    if(selectBool){
        if(selectedTransportSigned!=-1&&counterMetroLine!=-1){
            ButtonName selectedTransport= selectedTransportSigned;

            if(selectedTransport==_ENGINE_BTN_){
                for(unsigned short counterEngine=0;counterEngine<*sizeArrEngine; counterEngine++){
                    if((*arrEngine)[counterEngine]==NULL){
                        printf("OKENGINE\n");
                        createTransport(mainRenderer,NULL,&(*arrEngine)[counterEngine],&(*arrMetroLines)[counterMetroLine],transportSize,0,_ENGINE_, metroLineThickness);
                        printf("engine.x : %d, engine.y : %d, engin.w : %d, engine.h : %d\n",(*arrEngine)[counterEngine]->rect.x,(*arrEngine)[counterEngine]->rect.y,(*arrEngine)[counterEngine]->rect.w,(*arrEngine)[counterEngine]->rect.h);
                        printf("texture AVANT : %p\n",(*arrEngine)[counterEngine]->texture);
                        SDL_RenderCopyEx(mainRenderer,(*arrEngine)[counterEngine]->texture,NULL,&(*arrEngine)[counterEngine]->rect,90,NULL,SDL_FLIP_HORIZONTAL);
                        break;
                    }
                }
                
            }

            // else if(selectedTransport==_CAR_BTN_){
            //     for(unsigned short counterCar=0;counterCar<*sizeArrCar; counterCar++){
            //         if((*arrCar)[counterCar]==NULL&&(*arrCar)[counterCar]){
            //             createTransport()
            //         }
            //     }
                
            // }


        }   
    }
}


void updateDisplayEngines(SDL_Renderer *mainRenderer, SDLBackground *background,Engine ***arrEngine, MetroLine ***arrMetroLine, MetroStation ***arrMetroStation,unsigned short sizeArrEngine, unsigned short sizeArrMetroLine, int sizeArrMetroStation, unsigned short metroLineThickness ){

    for(unsigned short counterEngine=0;counterEngine<sizeArrEngine; counterEngine++){

        if((*arrEngine)[counterEngine]!=NULL){
            
            SDL_RenderCopy(mainRenderer, background->texture, &(*arrEngine)[counterEngine]->rect, &(*arrEngine)[counterEngine]->rect);
            controlTransportIntersection(mainRenderer,&(*arrEngine)[counterEngine],arrMetroStation,sizeArrMetroStation,arrMetroLine,sizeArrMetroLine);
            defineNewEngineOrientation(&(*arrEngine)[counterEngine]);
            defineNewEnginePosition(&(*arrEngine)[counterEngine]); 
            defineNewEngineDirection( &(*arrEngine)[counterEngine],metroLineThickness);
            // printf(" texture BID : %p\n",&(*arrEngine)[counterEngine]->texture)
            copyTransportTexture(mainRenderer,&(*arrEngine)[counterEngine]);

            // SDL_RenderCopyEx(mainRenderer, (*arrEngine)[counterEngine]->texture,NULL, &(*arrEngine)[counterEngine]->rect,90,NULL,SDL_FLIP_HORIZONTAL);

            // switch(arrEngine[counterEngine]->orientation){
            //     case _BOTTOM_TOP_ : 
                
            // }

        }
    }
}

void controlTransportIntersection(SDL_Renderer *mainRenderer,Engine **engine, MetroStation ***arrMetroStation,int sizeArrMetroStation, MetroLine ***arrMetroLine, int sizeArrMetroLine){

    for(unsigned short counterMetroLine=0;counterMetroLine<sizeArrMetroLine; counterMetroLine++){

        for(int counterMetroSegment=0; counterMetroSegment<(*arrMetroLine)[counterMetroLine]->sizeArrSegment;counterMetroSegment++){

            SDL_Rect absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
            SDL_Rect absolutePathPointToDstPointRect=absoluteRectPositionInRect(&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

            if(SDL_HasIntersection(&(*engine)->rect,&absoluteSrcPointToPathPointRect)||SDL_HasIntersection(&(*engine)->rect,&absolutePathPointToDstPointRect)){
                updateDisplayMetroSegment(mainRenderer, (*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment], (*arrMetroLine)[counterMetroLine]);
                updateColorMetroStation(mainRenderer,(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation);
                updateColorMetroStation(mainRenderer,(*arrMetroLine)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation);

            }
        }
    }

    for(unsigned short counterMetroStation=0;counterMetroStation<sizeArrMetroStation; counterMetroStation++){

        if((*arrMetroStation)[counterMetroStation]->display&&SDL_HasIntersection(&(*engine)->rect,&(*arrMetroStation)[counterMetroStation]->rect)){
            updateColorMetroStation(mainRenderer, (*arrMetroStation)[counterMetroStation]);
        }
    }
}


void copyTransportTexture(SDL_Renderer *mainRenderer, Engine **engine){

    switch ((*engine)->orientation){
        case _LEFT_RIGHT_:
            SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,90,NULL,SDL_FLIP_HORIZONTAL);
        break;
        case _RIGHT_LEFT_:
            SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,-90,NULL,SDL_FLIP_HORIZONTAL);
        break;
        case _BOTTOM_TOP_:
            SDL_RenderCopy(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect);
        break;
        case _TOP_BOTTOM_:
        SDL_RenderCopyEx(mainRenderer,(*engine)->texture,NULL,&(*engine)->rect,-180,NULL,SDL_FLIP_HORIZONTAL);           
        break;
    }


}
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

Direction controlDirectionPosition(Engine **engine,unsigned short metroLineThickness){

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



void defineNewEngineDirection(Engine **engine,unsigned short metroLineThickness){

    Direction lastDirection;
    
    if((lastDirection=controlDirectionPosition(engine,metroLineThickness))!=-1){

        SDL_Point precedentPoint;
         if((*engine)->direction==_FORWARD_){
            
            if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->nextSegment!=NULL){
                precedentPoint=(*engine)->dstPoint;
                definePositionAndOrientationEngine(engine, &precedentPoint, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->nextSegment!=NULL){
                (*engine)->currentMetroSegment=(*engine)->currentMetroSegment->nextSegment;
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine, &precedentPoint, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
            }
            else if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){
                precedentPoint=(*engine)->srcPoint;
                definePositionAndOrientationEngine(engine,&precedentPoint, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);

            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){
                (*engine)->direction=_FORWARD_;
                definePositionAndOrientationEngine(engine, NULL, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
            }
            
        }
        else if((*engine)->direction==_BACKWARD_){
            if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment!=NULL){
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine,NULL, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment!=NULL){
                (*engine)->currentMetroSegment=(*engine)->currentMetroSegment->precedentSegment;
                precedentPoint=(*engine)->pathPoint;
                definePositionAndOrientationEngine(engine,&precedentPoint, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
            }
            else if(lastDirection!=(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){
                precedentPoint=(*engine)->dstPoint;
                definePositionAndOrientationEngine(engine,&precedentPoint, &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->srcPointInRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect ,&(*engine)->currentMetroSegment->srcPointToPathPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);

            }
            else if(lastDirection==(*engine)->direction&&(*engine)->currentMetroSegment->precedentSegment==NULL&&(*engine)->currentMetroSegment->nextSegment==NULL){
                (*engine)->direction=_FORWARD_;
                definePositionAndOrientationEngine(engine, NULL, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect, &(*engine)->currentMetroSegment->dstPointInRect,&(*engine)->currentMetroSegment->srcPointToPathPointRect ,&(*engine)->currentMetroSegment->pathPointToDstPointRect,  &(*engine)->currentMetroSegment->rect,metroLineThickness);
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
                // centerRectOnPoint(&(*engine)->rect,&(*engine)->pathPoint,_X_);
                // printf("pathPoint.Y:%d\n"(*engine)->rect.y-1+(*engine)->rect.h/2);
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


    // if((*engine)->orientation==_TOP_BOTTOM_ || (*engine)->orientation==_BOTTOM_TOP_ ){
    //     (*engine)->rect.y=(*engine)->srcPoint.y;
    //     centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_X_);
    // }
    // else{
    //     (*engine)->rect.x=(*engine)->srcPoint.x;
    //     centerRectOnPoint(&(*engine)->rect,&(*engine)->srcPoint,_Y_);
    // }
}

// void defineNewPositionEngine(Engine *engine){


//     // SDL_Point absoluteDstPoint = absolutePointPositionInRect(&engine->currentMetroSegment->dstPointInRect,
//     if(engine->rect.x<engine->currentMetroSegment->dstStation->rect.x&&engine->orientation==_LEFT_RIGHT_){
//         engine->rect.x++;
//     }
// }


Car *getLastCar(Engine **currentEngine, Car **currentCar, unsigned short *carCounter){

    Car *tmpCar=NULL;

    *carCounter=0;
    if((*currentEngine)!=NULL&&(*currentEngine)->precedentCar!=NULL){
        tmpCar=(*currentEngine)->precedentCar;
        *carCounter++;
    }
    if((*currentCar)!=NULL&&(*currentCar)->precedentCar!=NULL){
        tmpCar=(*currentCar)->precedentCar;
        *carCounter++;
    }
    while(tmpCar->precedentCar!=NULL){
        tmpCar=tmpCar->precedentCar;
        *carCounter++;
    }
    return tmpCar;
}



Engine* getLightestEngineOnLine(MetroLine ***metroLine, Engine ***arrEngine, unsigned short sizeArrEngine){

    unsigned short lightestEngine[2]={0};
    unsigned short counterAttachedCars=0;
    unsigned short carCounter=0;

    for(unsigned short counterEngine=0;counterEngine<sizeArrEngine;counterEngine++){

        if((*arrEngine)[counterEngine]!=NULL&&(*arrEngine)[counterEngine]->metroLine==(*metroLine)){
            if((*arrEngine)[counterEngine]->precedentCar!=NULL){
                getLastCar(&(*arrEngine)[counterEngine],NULL,&carCounter);
            }

            else{
                return (*arrEngine)[counterEngine];
            }
            if(lightestEngine[1]>carCounter){
                lightestEngine[0]=counterEngine;
                lightestEngine[1]=carCounter;
            }
        }
    }
}

void createTransport(SDL_Renderer *mainRenderer,Car **car, Engine **engine, MetroLine **metroLine, unsigned short transportSize,unsigned short sizeArrPassenger, TransportType transportType, unsigned short metroLineThickness){


    switch(transportType){

        case _CAR_:
            createCar(engine,car, metroLine,transportSize,sizeArrPassenger);
        break;

        case _ENGINE_:
            createEngine(mainRenderer,engine,metroLine,transportSize,metroLineThickness);
        break;

    }
}

void createEngine(SDL_Renderer *mainRenderer, Engine **engine,MetroLine **metroLine, unsigned short transportSize, unsigned short metroLineThickness){

    if((*engine)==NULL){
        (*engine)=malloc(sizeof(Engine));
    }   

    if((*metroLine)->arrMetroSegment[0]!=NULL){
        (*engine)->currentMetroSegment=(*metroLine)->arrMetroSegment[0];
        (*engine)->precedentCar=NULL;
        (*engine)->rect=SDLChangeRect(0,0,transportSize,transportSize);

        definePositionAndOrientationEngine(engine,NULL, &(*engine)->currentMetroSegment->srcPointInRect, &(*engine)->currentMetroSegment->pathPointInRect,  &(*engine)->currentMetroSegment->dstPointInRect, &(*engine)->currentMetroSegment->srcPointToPathPointRect,&(*engine)->currentMetroSegment->pathPointToDstPointRect, &(*engine)->currentMetroSegment->rect,metroLineThickness);
        (*engine)->color=(*metroLine)->color;
        (*engine)->insideColor=SDLChangeRGBColor((*metroLine)->color.r+20,(*metroLine)->color.g+20,(*metroLine)->color.b+20,(*metroLine)->color.a);
        (*engine)->surface=SDL_CreateRGBSurfaceWithFormat(0,(*engine)->rect.w,(*engine)->rect.h,32,SDL_PIXELFORMAT_RGBA8888);
        drawGeometricShapeInGeometricShape((*engine)->surface,&(*engine)->rect,
        SDL_MapRGBA((*engine)->surface->format,(*engine)->color.r,(*engine)->color.g,(*engine)->color.b,(*engine)->color.a),
        SDL_MapRGBA((*engine)->surface->format,(*engine)->insideColor.r,(*engine)->insideColor.g,(*engine)->insideColor.b,(*engine)->insideColor.a),_TRIANGLE_,4,_BOTTOM_TOP_);
        (*engine)->texture=SDL_CreateTextureFromSurface(mainRenderer,(*engine)->surface);
        SDL_SetTextureBlendMode((*engine)->texture,SDL_BLENDMODE_BLEND);
        (*engine)->display=0;
        (*engine)->direction=_FORWARD_;
    } 
}


void definePositionAndOrientationEngine(Engine **engine,SDL_Point *precedentPathPoint, SDL_Point *relativeSrcPoint,SDL_Point *relativePathPoint, SDL_Point *relativeDstPoint, SDL_Rect *relativeSrcRect, SDL_Rect *relativeDstRect, SDL_Rect *parentRect, unsigned short metroLineThickness){

    SDL_Point tmpPrecedentPathPoint;
    if(precedentPathPoint!=NULL){
        tmpPrecedentPathPoint=*precedentPathPoint;
    }
    SDL_Point tmpSrcPoint=*relativeSrcPoint;
    SDL_Point tmpDstPoint=*relativePathPoint;

    setPointsPositionInRect(&tmpSrcPoint,&tmpDstPoint,relativeSrcRect,parentRect, metroLineThickness/2);
    (*engine)->srcPoint=tmpSrcPoint;
    (*engine)->pathPoint=tmpDstPoint;
    tmpSrcPoint=*relativePathPoint;
    tmpDstPoint=*relativeDstPoint;

    setPointsPositionInRect(&tmpSrcPoint,&tmpDstPoint,relativeDstRect,parentRect, metroLineThickness/2);
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

void createCar(Engine **engine,Car **car,MetroLine **metroLine, unsigned short transportSize, unsigned short sizeArrPassenger){

    if(*car==NULL){
        (*car)=malloc(sizeof(Car));
    }   

    if((*engine)!=NULL){
        if((*engine)->precedentCar==NULL){
            (*engine)->precedentCar=(*car);
            (*car)->engine=(*engine);
            (*car)->orientation=(*car)->engine->orientation;
            setRectBehindRectWithOrientation(&(*car)->rect,&(*car)->engine->rect,(*car)->orientation);
        }
        if((*engine)->precedentCar!=NULL){
            Car *nextCar=(*engine)->precedentCar;
            while(nextCar->precedentCar!=NULL){
                nextCar=nextCar->precedentCar;
            }
            (*car)->nextCar=nextCar;
            (*car)->engine=NULL;
            nextCar->precedentCar=(*car);
            (*car)->orientation=(*car)->nextCar->orientation;
            setRectBehindRectWithOrientation(&(*car)->rect,&(*car)->nextCar,(*car)->orientation);
        }
        (*car)->precedentCar=NULL;   
        (*car)->surface=SDL_CreateRGBSurfaceWithFormat(0,transportSize,transportSize,32,SDL_PIXELFORMAT_RGBA8888);
        (*car)->color=(*metroLine)->color;
        (*car)->insideColor=SDLChangeRGBColor((*metroLine)->color.r+20,(*metroLine)->color.g+20,(*metroLine)->color.b+20,(*metroLine)->color.a);
        (*car)->display=0;
        (*car)->arrPassenger=malloc(sizeof(Passenger*)*sizeArrPassenger);
        for(unsigned short counterPassenger=0;counterPassenger<sizeArrPassenger;counterPassenger++){
            (*car)->arrPassenger[counterPassenger]=malloc(sizeof(Passenger));
        }
    }

    
}
