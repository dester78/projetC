#ifndef MATHCALCULATION
#define MATHCALCULATION

#include <math.h>

#include <SDL.h>

int distanceBetweenTwoPoint(SDL_Point *firstPoint, SDL_Point *secondPoint);

double radToDeg(double rad);

int randInRange(int lowerValue, int higherValue);

int diamCircumscribeCircleOnRect(int length, int width);

#endif