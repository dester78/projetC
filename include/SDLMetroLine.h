#ifndef METROLINE
#define METROLINE

#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>
#include <SDLMetroLine.h>


#include<SDL.h>

// void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine);
// void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness);

// void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine);
// void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect);
// void avoidOverlapPathRectMetroSegment(SDL_Point *currentPathPoint,SDL_Point *currentPathRect, SDL_Rect *currentParentRect, SDL_Point *otherPathRect, SDL_Rect *otherParentRect);

// void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape);

// void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool);


void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine);
void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness);
void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine);
void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect);
void avoidOverlapPathRectMetroSegment(SDL_Point *currentPathPoint,SDL_Rect *currentPathRect, SDL_Rect *currentParentRect, SDL_Point *otherPathRect, SDL_Rect *otherParentRect);
void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape);
void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool);
void SDLCreateMetroSegmentMenu(SDLBackground *backgroundMenu);
short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations);
short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine);
void SDLCreateMetroLineMenu(SDLBackground *backgroundMenu);

void deleteSegment(SDL_Renderer *mainRenderer, SDLBackground *background,MetroSegment ***arrMetroSegment, MetroSegment **currentMetroSegment, unsigned short *sizeArrMetroSegment);
void manageMetroSegmentLevel(SDL_Renderer *mainRenderer, SDLBackground *background, MetroLine **metroLine, MetroStation **arrMetroStations, MetroSegment **currentMetroSegment, int sizeArrMetroStation, short counterMetroLine, short metroLineThickness,short addDeleteBool);


short controNewSegment(MetroSegment *metroSegment, MetroStation *srcStation , MetroStation *dstStation);
void createGeometryMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, MetroStation * srcStation, MetroStation *dstStation, short counterMetroLine, short metroLineThickness);

MetroSegment *addNewSegment(MetroSegment ***arrMetroSegment, MetroStation **srcStation , MetroStation **dstStation, unsigned short *sizeArrMetroSegment );


void metroLineEventManagerLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *container, MetroLine **arrMetroLines , MetroStation **arrMetroStations,  int sizeArrMetroLine,int sizeArrMetroStations, unsigned short metroLineThickness, SDL_Point *mousePoint, short selectBool, ContainerPosition containerPosition);

// short addSegmentEnd(MetroSegment *metroSegment, MetroStation *srcStation , MetroStation *dstStation);
// short addSegmentBeginning(MetroSegment *metroSegment, MetroStation *srcStation , MetroStation *dstStation);
void reorderMetroSegmentsLastToFirst(MetroSegment ***arrMetroSegment, unsigned short sizeArrSegment);
void reorderSrcAndDestStations(MetroSegment **currentMetroSegment, MetroStation **srcMetroStation, MetroStation **dstMetroStation, unsigned short order);

#endif 