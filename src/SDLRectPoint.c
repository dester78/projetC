
#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>

#include <SDL.h>


void marginAuto(SDL_Rect *parentRect, SDL_Rect *childrenRect, unsigned short childrenPosition, unsigned short childrenCount,  Axe axe ){

    if(childrenCount>0){
        if(axe==_X_){
            childrenRect->x=( (parentRect->w/childrenCount) * (childrenPosition ) +  ((parentRect->w/childrenCount)/2)) - childrenRect->w/2 + parentRect->x;

        }

        else if(axe==_Y_){
            childrenRect->y=( (parentRect->h/childrenCount) * (childrenPosition ) +  ((parentRect->h/childrenCount)/2)) - childrenRect->h/2 + parentRect->y;

        }
    }

    else{
        if(axe==_X_){
            childrenRect->x=parentRect->w  - parentRect->w/2  - childrenRect->w/2 + parentRect->x;
        }

        else if(axe==_Y_){
            childrenRect->y=parentRect->h  - parentRect->h/2  - childrenRect->h/2 + parentRect->y;
        }
    }
    
}

void resizeRect(SDL_Rect *rect, int newScale){

    rect->x-= newScale;
    rect->y-= newScale;
    rect->w+= newScale/2;
    rect->h+= newScale/2;
}

SDL_Point createPointXY(int x , int y){

    SDL_Point tmpPoint;

    tmpPoint.x=x;
    tmpPoint.y=y;

    return tmpPoint;
}

SDL_Rect SDLChangeRect(int x , int y , int w , int h){

    SDL_Rect newRect; 

    newRect.x=x;
    newRect.y=y;
    newRect.w=w;
    newRect.h=h;

    return newRect;
}

int hasIntersectPointRect(SDL_Point *point, SDL_Rect *rect){

    if(point->x >= rect->x && point->x <= rect->w + rect->x && point->y >= rect->y && point->y <= rect->h + rect->y){
        return 1;
    }

    return 0;

}

SDL_Rect verticalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect){

    SDL_Rect tmpRect;

    tmpRect.x=rect->x;
    tmpRect.w=rect->w;
    tmpRect.y=parentRect->y;
    tmpRect.h=parentRect->h;

    return tmpRect;

}

SDL_Rect horizontalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect){

    SDL_Rect tmpRect;

    tmpRect.y=rect->y;
    tmpRect.h=rect->h;
    tmpRect.x=parentRect->x;
    tmpRect.w=parentRect->w;

    return tmpRect;

}


SDL_Point absolutePointPositionInRect(SDL_Point *relativePoint, SDL_Rect *frameRect){

    SDL_Point absolutePoint;

    absolutePoint.x=relativePoint->x+frameRect->x;
    absolutePoint.y=relativePoint->y+frameRect->y;

    return absolutePoint;
}

SDL_Point relativePointPositionInRect(SDL_Point *absolutePoint, SDL_Rect *frameRect){

    SDL_Point relativePoint;

    relativePoint.x=absolutePoint->x-frameRect->x;
    relativePoint.y=absolutePoint->y-frameRect->y;

    return relativePoint;

}

SDL_Rect relativeRectPositionInRect(SDL_Rect *absoluteRect, SDL_Rect *frameRect){

    SDL_Rect relativeRect;

    relativeRect.x=absoluteRect->x-frameRect->x;
    relativeRect.y=absoluteRect->y-frameRect->y;
    relativeRect.h=absoluteRect->h;
    relativeRect.w=absoluteRect->w;


    return relativeRect;

}

SDL_Rect absoluteRectPositionInRect(SDL_Rect *relativeRect, SDL_Rect *frameRect){

    SDL_Rect absoluteRect;

    absoluteRect.x=relativeRect->x+frameRect->x;
    absoluteRect.y=relativeRect->y+frameRect->y;
    absoluteRect.w=relativeRect->w;
    absoluteRect.h=relativeRect->h;

    return absoluteRect;
}

void createRectBetweenTwoRect(SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Rect *finalRect, SDL_Point *srcPoint, SDL_Point *dstPoint){

    SDL_Point tmpSrcPoint, tmpDstPoint;

    if(srcRect->x < dstRect->x){
        finalRect->x=srcRect->x;
        finalRect->w=dstRect->x+dstRect->w-srcRect->x;
        tmpSrcPoint.x=0;
        tmpDstPoint.x=finalRect->w;
    }

    else{
        finalRect->x=dstRect->x;
        finalRect->w=srcRect->x+srcRect->w-dstRect->x;
        tmpDstPoint.x=0;
        tmpSrcPoint.x=finalRect->w;        
    }

    if(srcRect->y < dstRect->y){
        finalRect->y=srcRect->y;
        finalRect->h=dstRect->y+dstRect->h-srcRect->y;
        tmpSrcPoint.y=0;
        tmpDstPoint.y=finalRect->h;
    }

    else{
        finalRect->y=dstRect->y;
        finalRect->h=srcRect->y+srcRect->h-dstRect->y;
        tmpDstPoint.y=0;
        tmpSrcPoint.y=finalRect->h;        
    }

    if(srcPoint!=NULL){
        *srcPoint=tmpSrcPoint;
    }

    if(dstPoint!=NULL){
        *dstPoint=tmpDstPoint;
    }

}

void createRectBetweenTwoPoint(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *finalRect, SDL_Point *finalSrcPoint, SDL_Point *finalDstPoint){

    SDL_Point tmpSrcPoint, tmpDstPoint;

    if(srcPoint->x < dstPoint->x){
        finalRect->x=srcPoint->x;
        finalRect->w=dstPoint->x-srcPoint->x;
        tmpSrcPoint.x=0;
        tmpDstPoint.x=finalRect->w;
    }

    else{
        finalRect->x=dstPoint->x;
        finalRect->w=srcPoint->x-dstPoint->x;
        tmpDstPoint.x=0;
        tmpSrcPoint.x=finalRect->w;        
    }

    if(srcPoint->y < dstPoint->y){
        finalRect->y=srcPoint->y;
        finalRect->h=dstPoint->y-srcPoint->y;
        tmpSrcPoint.y=0;
        tmpDstPoint.y=finalRect->h;
    }

    else{
        finalRect->y=dstPoint->y;
        finalRect->h=srcPoint->y-dstPoint->y;
        tmpDstPoint.y=0;
        tmpSrcPoint.y=finalRect->h;        
    }

    if(finalSrcPoint!=NULL){
        *finalSrcPoint=tmpSrcPoint;
    }

    if(finalDstPoint!=NULL){
        *finalDstPoint=tmpDstPoint;
    }


}
