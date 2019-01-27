#ifndef METROLINE
#define METROLINE

#include <SDLObjectsStructures.h>

#include<SDL.h>

void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine);
void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness);

void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine);
void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect);
void avoidOverlapPathRectMetroSegment(SDL_Point *currentPathPoint,SDL_Point *currentPathRect, SDL_Rect *currentParentRect, SDL_Point *otherPathRect, SDL_Rect *otherParentRect);

void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape);

void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool);


#endif 