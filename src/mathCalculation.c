#include <math.h>
#include <stdlib.h>

#include <mathCalculation.h>

#include <SDL.h>


int distanceBetweenTwoPoint(SDL_Point *firstPoint, SDL_Point *secondPoint){

    return (int)sqrt((pow((firstPoint->x-secondPoint->x),2.0)+(pow((firstPoint->y-secondPoint->y),2.0))));
}

double radToDeg(double rad){

    return rad/M_PI*180;
}

int randInRange(int lowerValue, int higherValue){

    int randValue;
    randValue=(rand()%higherValue)+lowerValue;

    while(randValue>higherValue||randValue<lowerValue){
        randValue=(rand()%higherValue)+lowerValue;
    }

    return randValue;
}

int diamCircumscribeCircleOnRect(int length, int width){

    return sqrt(pow(length,2)+pow(width,2));

}

