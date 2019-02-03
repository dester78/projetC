#ifndef SDLRECTPOINT
#define SDLRECTPOINT

#include <SDLObjectsStructures.h>
#include <SDL.h>

//Fonction permettant de générer un SDL_Rect
SDL_Rect SDLChangeRect(int x , int y , int w , int h);
//Fonction permettant de générer un SDL_Point
SDL_Point createPointXY(int x , int y);

//Fonction permettant d'obtenir une position relative d'un SDL_Point par rapport à son SDL_Rect parent
SDL_Point relativePointPositionInRect(SDL_Point *absolutePoint, SDL_Rect *frameRect);
//Fonction permettant d'obtenir une position absolue d'un SDL_Point par rapport à son SDL_Rect parent
SDL_Point absolutePointPositionInRect(SDL_Point *relativePoint, SDL_Rect *frameRect);

//Fonction permettant d'obtenir une position relative d'un SDL_Rect par rapport à son SDL_Rect parent
SDL_Rect relativeRectPositionInRect(SDL_Rect *absoluteRect, SDL_Rect *frameRect);
//Fonction permettant d'obtenir une position absolue d'un SDL_Rect par rapport à son SDL_Rect parent
SDL_Rect absoluteRectPositionInRect(SDL_Rect *relativeRect, SDL_Rect *frameRect);

void centerRectOnRect(SDL_Rect *targetRect, SDL_Rect *centeredRect, Axe axe);
void centerPointOnRect(SDL_Rect *targetRect, SDL_Point *centeredPoint, Axe axe);
//Fonction vérifiant si un SDL_Point se trouve dans un SDL_Rect
int hasIntersectPointRect(SDL_Point *point, SDL_Rect *rect);

//Fonction permettant de créer un SDL_Rect englobant deux SDL_Rect, elle détermine aussi un point source et un point destination à partir des angles opposés du SDL_Rect ainsi créé
void createRectBetweenTwoRect(SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Rect *finalRect, SDL_Point *srcPoint, SDL_Point *dstPoint);
//Fonction permettant de créer un SDL_Rect englobant deux SDL_Point, elle détermine aussi un point source et un point destination à partir des angles opposés du SDL_Rect ainsi créé
void createRectBetweenTwoPoint(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *finalRect, SDL_Point *finalSrcPoint, SDL_Point *finalDstPoint);

void centerRectOnPoint(SDL_Rect *centeredRect, SDL_Point *targetPoint, Axe axe);


//Fonction permettant de définir l'orientation d'un élément en fonction d'un point source et d'un  point destination
Orientation defineOrientation(SDL_Point *currentPoint, SDL_Point *nextPoint);

//Fonction permettant de définir la position d'un SDL_Rect en fonction d'une orientation donnée afin que ce dernier se trouve derrière le SDL_Rect suivant
void setRectBehindRectWithOrientation(SDL_Rect *currentRect, SDL_Rect *nextRect, Orientation orientation);

//Fonction permmetant de générer un SDL_Rect ayant pour largeur et position en x la largeur et position en x du SDL_Rect enfant 
//et pour hauteur et position en y la hauteur et la position en y du SDL_Rect parent. 
SDL_Rect verticalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect);
//Fonction permmetant de générer un SDL_Rect ayant pour heuteur et position en y la hauteur et position en y du SDL_Rect enfant 
//et pour largeur et position en x la largeur et la position en x du SDL_Rect parent. 
SDL_Rect horizontalRectInParentRect(SDL_Rect *rect, SDL_Rect *parentRect);

// void setPointsPositionInRect(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, int translation);
void setPointsPositionInRect(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *childRect, SDL_Rect *parentRect, int translation);

// void setPointPositionInRect(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, int translation);

//Fonction calculant la position d'un élément dans un SDL_Rect parent en fonction des autres éléments présent dans le SDL_Rect parent, ainsi que son ordre de placement et son axe X ou Y.
void marginAuto(SDL_Rect *parentRect, SDL_Rect *childrenRect, unsigned short childrenPosition, unsigned short childrenCount,  Axe axe );



// void resizeRect(SDL_Rect *rect, int newScale);

#endif