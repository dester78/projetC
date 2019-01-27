
#include <stdio.h>
#include <stdlib.h>

#include <SDLObjectsStructures.h>
#include <SDLDraw.h>

#include <SDL.h>


void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wSurface, int hSurface, Uint32 pixelColor){

  if (xPixel >= 0 && xPixel <= wSurface && yPixel >= 0 && yPixel <= hSurface){
      *pixel=pixelColor;
  } 
}


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



void drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color){

    int diameter, y, x;
    
    diameter = 3 - (2 * radius);
    x = 0;
    y = radius;

    while (y >= x) {

        drawVariableRect(surface, xCenter - x, yCenter - y, 2 * x + 1,1, color);
        drawVariableRect(surface, xCenter - x, yCenter + y, 2 * x + 1,1, color);
        drawVariableRect(surface, xCenter - y, yCenter - x, 2 * y + 1,1, color);
        drawVariableRect(surface, xCenter - y, yCenter + x, 2 * y + 1,1, color);
    
        if (diameter < 0){
            diameter = diameter + (4 * x) + 6;
        }

        else {
            diameter = diameter + 4 * (x - y) + 10;
            y--;
        }
    
        x++;
    }
}


void drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect){

    SDL_Rect rect;

    rect.x = xRect;
    rect.y = yRect;
    rect.w = wRect;
    rect.h = hRect;

    SDL_FillRect(*surface, &rect, colorRect);
}
 
int drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color, TriangleOrientation triangleOrientation ){

    int counterLine=0;
    
    wRoot = wRoot % 2 == 0 ? wRoot+1 : wRoot;//Vérifie que la base du triangle est bien un nombre impaire

    while(counterLine!=(wRoot/2 + 1 )){

        if(triangleOrientation==_LEFT_RIGHT_){
            drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-wRoot+counterLine, 1,wRoot-(counterLine*2), color);
            drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-wRoot+counterLine,1, wRoot-(counterLine*2), color);
        }
        else if(triangleOrientation==_BOTTOM_TOP_){
            drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-counterLine*2-1, wRoot-(counterLine*2),1, color);
            drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-counterLine*2, wRoot-(counterLine*2),1, color);
        }
        counterLine++;
    }
    return counterLine;
}


void drawGeometricShapeInGeometricShape(SDL_Surface *surface,SDL_Rect *rect,  Uint32 color, Uint32 insideColor, GeometricShape geometricShape, unsigned short centeringFactor, TriangleOrientation triangleOrientation){

    SDL_Rect tmpRect;

    tmpRect=*rect;
    for(unsigned short shiftCounter=0; shiftCounter<2; shiftCounter++){

        tmpRect.h=tmpRect.h-shiftCounter*rect->h/centeringFactor;
        tmpRect.w=tmpRect.w-shiftCounter*rect->w/centeringFactor;

        color=shiftCounter==0?color:insideColor;

        switch(geometricShape){

        case 0 : 
            drawFillCircle(&surface,tmpRect.w/2+(shiftCounter*rect->w/centeringFactor)/2,tmpRect.h/2+(shiftCounter*rect->h/centeringFactor)/2,tmpRect.w/2,color);
        break;

        case 1 :
            drawVariableRect(&surface,(shiftCounter*rect->w/centeringFactor)/2,(shiftCounter*rect->w/centeringFactor)/2,tmpRect.w,tmpRect.h,color);
        break;

        case 2 :
            drawFillTriangle(&surface,(shiftCounter*rect->w/centeringFactor)/2,tmpRect.h+(shiftCounter*rect->h/centeringFactor)/2,tmpRect.w,color, triangleOrientation);
        break;
        }
    }
    
}

// void drawTimeButton(SDL_Surface *surface,SDL_Rect *rect,  SDL_Color *color,  ButtonName  buttonName){

//     Uint32 tmpColor=SDL_MapRGBA(surface->format,color->r,color->g,color->b,color->a);
//     printf("rect.x : %d , rect.y: %d , rect.w: %d rect.h:%d\n",rect->x,rect->y,rect->w,rect->h);

//     printf("PAS PLAY");
//     switch(buttonName){

//         case _PLAY_:
//         printf("PLAYYYYY");
//         printf("\nrect->w : %d rect->y:%d,rect->w:%d,rect->h:%d\n",rect->x,rect->y,rect->w,rect->h);
//             drawFillTriangle(&surface,rect->w/2.25,rect->h/1.15,rect->w/1.25,tmpColor, _LEFT_RIGHT_);
//         break;
//     }
// }


// void changeOverlapColorSurfaces(SDL_Rect *foreGroundRect, SDL_Surface *backgroundSurface, SDL_Rect *backGroundRect, Uint32 overlapColor){

//     Uint32 *backGroundPixels;
//     Uint32 pixel;
    
//     if(SDL_LockSurface(backGroundSurface)!=0){
//         printf("bug");
//     }

//     backGroundPixels = backGroundSurface->pixels;

//     for(size_t yCounterForeground = foreGroundRect->y ; yCounterForeground<(size_t)foreGroundRect->y + foreGroundRect->h ; yCounterForeground++ ){
//         for(size_t xCounterForeground = foreGroundRect->x ; xCounterForeground<(size_t)foreGroundRect->x + foreGroundRect->w ; xCounterForeground++){
            
//             for(size_t yCounterBackground = backGroundRect->y ; yCounterBackground <(size_t) backGroundRect->y + backGroundRect->h ; yCounterBackground++ ){
//                 for(size_t xCounterBackground = backGroundRect->x ; xCounterBackground <(size_t) backGroundRect->x + backGroundRect->w ; xCounterBackground++){

//                     if(yCounterForeground == yCounterBackground &&  xCounterForeground == xCounterBackground){

//                         pixel=(yCounterBackground-backGroundRect->y) * (*backGroundSurface)->w + xCounterBackground-backGroundRect->x;
//                         backGroundPixels[pixel]=overlapColor;
//                     }
//                 }
//             }
//         }
//     }    	
//     SDL_UnlockSurface(*backGroundSurface);
// }








