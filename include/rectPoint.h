#ifndef RECTPOINT
#define RECTPOINT

#include <SDLObjectsStructures.h>

#include <SDL.h>

SDL_Rect SDLChangeRect(int x , int y , int w , int h);

SDL_Point absolutePointPositionInRect(SDL_Point *relativePoint, SDL_Rect *frameRect);
SDL_Point relativePointPositionInRect(SDL_Point *absolutePoint, SDL_Rect *frameRect);
SDL_Rect relativeRectPositionInRect(SDL_Rect *absoluteRect, SDL_Rect *frameRect);
SDL_Rect absoluteRectPositionInRect(SDL_Rect *relativeRect, SDL_Rect *frameRect);

#endif