#ifndef SDLRECTPOINT
#define SDLRECTPOINT

#include <SDLObjectsStructures.h>
#include <SDL.h>

SDL_Rect SDLChangeRect(int x , int y , int w , int h);
SDL_Point absolutePointPositionInRect(SDL_Point *relativePoint, SDL_Rect *frameRect);
SDL_Point relativePointPositionInRect(SDL_Point *absolutePoint, SDL_Rect *frameRect);
SDL_Rect relativeRectPositionInRect(SDL_Rect *absoluteRect, SDL_Rect *frameRect);
SDL_Rect absoluteRectPositionInRect(SDL_Rect *relativeRect, SDL_Rect *frameRect);

SDL_Point createPointXY(int x , int y);
int hasIntersectPointRect(SDL_Point *point, SDL_Rect *rect);

void createRectBetweenTwoRect(SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Rect *finalRect, SDL_Point *srcPoint, SDL_Point *dstPoint);

void createRectBetweenTwoPoint(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *finalRect, SDL_Point *finalSrcPoint, SDL_Point *finalDstPoint);

SDL_Rect verticalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect);
SDL_Rect horizontalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect);
void resizeRect(SDL_Rect *rect, int newScale);

void marginAuto(SDL_Rect *parentRect, SDL_Rect *childrenRect, unsigned short childrenPosition, unsigned short childrenCount,  Axe axe );


#endif