
#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>
#include <SDLMetroLine.h>

#include<SDL.h>

void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine){


    // for(unsigned short overlapCounter=0;overlapCounter<2;overlapCounter++){
        currentMetroSegment->pathPointInRect.x=currentMetroSegment->srcPointInRect.x;
        currentMetroSegment->pathPointInRect.y=currentMetroSegment->dstPointInRect.y;

        if(precedentMetroSegment!=NULL){

            avoidOverlapPathPointMetroSegment(
                &currentMetroSegment->pathPointInRect,
                &currentMetroSegment->rect,
                &precedentMetroSegment->pathPointInRect,
                &precedentMetroSegment->rect    );      
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
    // }     
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

void avoidOverlapPathRectMetroSegment(SDL_Point *currentPathPoint,SDL_Point *currentPathRect, SDL_Rect *currentParentRect, SDL_Point *otherPathRect, SDL_Rect *otherParentRect){

    SDL_Rect tmpCurrentPathRect, tmpOtherPathRect;
    
    tmpCurrentPathRect=absoluteRectPositionInRect(currentPathRect,currentParentRect);
    tmpOtherPathRect=absoluteRectPositionInRect(otherPathRect,otherParentRect);

    if(SDL_HasIntersection(&tmpCurrentPathRect,&tmpOtherPathRect)){

        currentPathPoint->x = currentPathPoint->x==0 ? currentParentRect->w : 0; 
        currentPathPoint->y = currentPathPoint->y==0 ? currentParentRect->h : 0; 
    }
}

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

    
    // if(metroStation->sizeArrLinkedMetroSegment==0){
    //     metroStation->arrLinkedMetroSegment=malloc(sizeof(MetroSegment*));
    //     metroStation->sizeArrLinkedMetroSegment++;
    // }
    // else{
    //     metroStation->sizeArrLinkedMetroSegment++;
    //     metroStation->arrLinkedMetroSegment=realloc(metroStation->arrLinkedMetroSegment,metroStation->sizeArrLinkedMetroSegment*sizeof(MetroSegment*));
    // }

    // metroStation->arrLinkedMetroSegment[metroStation->sizeArrLinkedMetroSegment-1]=metroSegment;

    if(srcDstBool){
        metroSegment->srcStation=metroStation;
    }
    else{
        metroSegment->dstStation=metroStation;
    }
        
}
