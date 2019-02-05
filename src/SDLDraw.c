
#include <stdio.h>
#include <stdlib.h>

#include <SDLObjectsStructures.h>
#include <SDLDraw.h>

#include <SDL.h>

void drawCircle(Uint32 **pixels,int xCenter, int yCenter, int radius,int wSurface, int hSurface, Uint32 pixelColor){

  int diameter, y, x;

 
  diameter = 3 - (2 * radius);
  x = 0;
  y = radius;

  while (y >= x) {
    
    
    controlPixelPosition(&(*pixels)[(xCenter + x) * wSurface + (yCenter + y)],xCenter + x, yCenter + y,wSurface,hSurface, pixelColor);//Premier quart de cercle
    controlPixelPosition(&(*pixels)[(xCenter + y) * wSurface + (yCenter + x)],xCenter + y, yCenter + x,wSurface,hSurface, pixelColor);
    controlPixelPosition(&(*pixels)[(xCenter - x) * wSurface + (yCenter + y)],xCenter - x, yCenter + y,wSurface,hSurface, pixelColor);//Deuxième quart de cercle
    controlPixelPosition(&(*pixels)[(xCenter - y) * wSurface + (yCenter + x)],xCenter - y, yCenter + x,wSurface,hSurface, pixelColor);
    controlPixelPosition(&(*pixels)[(xCenter + x) * wSurface + (yCenter - y)],xCenter + x, yCenter - y,wSurface,hSurface, pixelColor);//Troisième quart de cercle
    controlPixelPosition(&(*pixels)[(xCenter + y) * wSurface + (yCenter - x)],xCenter + y, yCenter - x,wSurface,hSurface, pixelColor);
    controlPixelPosition(&(*pixels)[(xCenter - x) * wSurface + (yCenter - y)],xCenter - x, yCenter - y,wSurface,hSurface, pixelColor);//Quatrième quart de cercle
    controlPixelPosition(&(*pixels)[(xCenter - y) * wSurface + (yCenter - x)],xCenter - y, yCenter - x,wSurface,hSurface, pixelColor);
 
    if (diameter < 0)
      diameter = diameter + (4 * x) + 6;
    else {
      diameter = diameter + 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}

short drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color){

    int diameter, y, x;
    
    diameter = 3 - (2 * radius);
    x = 0;
    y = radius;

    while (y >= x) {

        if(drawVariableRect(surface, xCenter - x, yCenter - y, 2 * x + 1,1, color)==0||drawVariableRect(surface, xCenter - x, yCenter + y, 2 * x + 1,1, color)==0||drawVariableRect(surface, xCenter - y, yCenter - x, 2 * y + 1,1, color)==0||drawVariableRect(surface, xCenter - y, yCenter + x, 2 * y + 1,1, color)==0){
            createErrorReport("Echec lors du remplissage d'un rectangle de taille variable",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    
        if (diameter < 0){
            diameter = diameter + (4 * x) + 6;
        }

        else {
            diameter = diameter + 4 * (x - y) + 10;
            y--;
        }
    
        x++;
    }
    return 1;
}


short drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect){

    SDL_Rect rect;

    rect.x = xRect;
    rect.y = yRect;
    rect.w = wRect;
    rect.h = hRect;

    if(SDL_FillRect(*surface, &rect, colorRect)!=0){
        fprintf(stderr,"Echec lors du remplissage d'un rectangle dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    return 1;
}
 

short drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color, Orientation orientation ){

    int counterLine=0;
    
    wRoot = wRoot % 2 == 0 ? wRoot+1 : wRoot;//Vérifie que la base du triangle est bien un nombre impaire

    while(counterLine!=(wRoot/2 + 1 )){

        if(orientation==_LEFT_RIGHT_){
            if(drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-wRoot+counterLine, 1,wRoot-(counterLine*2), color)==0|| drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-wRoot+counterLine,1, wRoot-(counterLine*2), color)==0){
                createErrorReport("Echec lors du remplissage d'un rectangle de taille variable",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
        else if(orientation==_BOTTOM_TOP_){
            if(drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-counterLine*2-1, wRoot-(counterLine*2),1, color)==0||drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-counterLine*2, wRoot-(counterLine*2),1, color)==0){
                createErrorReport("Echec lors du remplissage d'un rectangle de taille variable",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
        counterLine++;
    }
    return 1;
}


short drawGeometricShapeInGeometricShape(SDL_Surface *surface,SDL_Rect *rect,  Uint32 color, Uint32 insideColor, GeometricShape geometricShape, unsigned short centeringFactor, Orientation orientation){

    SDL_Rect tmpRect;

    tmpRect=*rect;
    for(unsigned short shiftCounter=0; shiftCounter<2; shiftCounter++){

        tmpRect.h=tmpRect.h-shiftCounter*rect->h/centeringFactor;
        tmpRect.w=tmpRect.w-shiftCounter*rect->w/centeringFactor;

        color=shiftCounter==0?color:insideColor;

        switch(geometricShape){

        case 0 : 
            if(drawFillCircle(&surface,tmpRect.w/2+(shiftCounter*rect->w/centeringFactor)/2,tmpRect.h/2+(shiftCounter*rect->h/centeringFactor)/2,tmpRect.w/2,color)==0){
                createErrorReport("Echec lors de la création d'un cercle rempli",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        break;

        case 1 :
            if(drawVariableRect(&surface,(shiftCounter*rect->w/centeringFactor)/2,(shiftCounter*rect->w/centeringFactor)/2,tmpRect.w,tmpRect.h,color)==0){
                createErrorReport("Echec lors de la création d'un rectangle rempli",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        break;

        case 2 :
            if(drawFillTriangle(&surface,(shiftCounter*rect->w/centeringFactor)/2,tmpRect.h+(shiftCounter*rect->h/centeringFactor)/2,tmpRect.w,color, orientation)==0){
                createErrorReport("Echec lors de la création d'un triangle rempli",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        break;
        }
    }
    return 1;
}

void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wSurface, int hSurface, Uint32 pixelColor){

  if (xPixel >= 0 && xPixel <= wSurface && yPixel >= 0 && yPixel <= hSurface){
      *pixel=pixelColor;
  } 
}


















