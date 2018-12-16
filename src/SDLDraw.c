#include <SDL.h>
#include <SDLDraw.h>
#include <stdio.h>


SDL_Color SDLChangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a ){

    SDL_Color RGBColor;

    RGBColor.r=r;
    RGBColor.g=g;
    RGBColor.b=b;
    RGBColor.a=a;

    return RGBColor;
}

SDL_Rect SDLChangeRect(int x , int y , int w , int h){

    SDL_Rect newRect; 

    newRect.x=x;
    newRect.y=y;
    newRect.w=w;
    newRect.h=h;

    return newRect;
}


void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wSurface, int hSurface, Uint32 pixelColor){

  if (xPixel >= 0 && xPixel < wSurface && yPixel >= 0 && yPixel < hSurface){
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
 
int drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color ){

    int counterLine;
    
    counterLine = 0;
    
    wRoot = wRoot % 2 == 0 ? wRoot+1 : wRoot;//Vérifie que la base du triangle est bien un nombre impaire

    while(counterLine!=(wRoot/2 + 1 )){

        drawVariableRect(surface, xLeftRoot+counterLine, yLeftRoot-counterLine, wRoot-(counterLine*2),1, color);
        counterLine++;
    }

    return counterLine;

}


void changeOverlapColorSurfaces(SDL_Rect *foreGroundRect, SDL_Surface **backGroundSurface, SDL_Rect *backGroundRect, Uint32 overlapColor){

    Uint32 *backGroundPixels;
    Uint32 pixel;
    
    if(SDL_LockSurface(*backGroundSurface)!=0){
        printf("bug");
    }

    backGroundPixels = (*backGroundSurface)->pixels;

    for(size_t yCounterForeground = foreGroundRect->y ; yCounterForeground<(size_t)foreGroundRect->y + foreGroundRect->h ; yCounterForeground++ ){
        for(size_t xCounterForeground = foreGroundRect->x ; xCounterForeground<(size_t)foreGroundRect->x + foreGroundRect->w ; xCounterForeground++){
            
            for(size_t yCounterBackground = backGroundRect->y ; yCounterBackground <(size_t) backGroundRect->y + backGroundRect->h ; yCounterBackground++ ){
                for(size_t xCounterBackground = backGroundRect->x ; xCounterBackground <(size_t) backGroundRect->x + backGroundRect->w ; xCounterBackground++){

                    if(yCounterForeground == yCounterBackground &&  xCounterForeground == xCounterBackground){

                        pixel=(yCounterBackground-backGroundRect->y) * (*backGroundSurface)->w + xCounterBackground-backGroundRect->x;
                        backGroundPixels[pixel]=overlapColor;
                    }
                }
            }
        }
    }    	
    SDL_UnlockSurface(*backGroundSurface);
}

//Fonction qui renvoie 1 si le foregroundRect a des coordonnées en commun avec le backgroundRect et modifie le overlapRect pour récupérer les coordonnées de chevauchement
unsigned short createOverlapRect(SDL_Rect *foregroundRect, SDL_Rect *backgroundRect, SDL_Rect *overlapRect){

    unsigned int xCounter ,yCounter;
    unsigned short overlapRisk=0;

    overlapRect->w=0;
    overlapRect->h=0;

    if((backgroundRect->x >= foregroundRect->x && backgroundRect->x + backgroundRect->w <= foregroundRect->x + foregroundRect->w) || (backgroundRect->x >= foregroundRect->x && backgroundRect->x <= foregroundRect->w + foregroundRect->x && backgroundRect->x + backgroundRect->w >=  foregroundRect->x + foregroundRect->w ) || (backgroundRect->x <= foregroundRect->x && backgroundRect->x + backgroundRect->w >= foregroundRect->x && backgroundRect->x + backgroundRect->w <=  foregroundRect->x + foregroundRect->w)){

        if(backgroundRect->y >= foregroundRect->y && backgroundRect->y + backgroundRect->h <= foregroundRect->y + foregroundRect->h  ){
                overlapRect->y=0;
                overlapRect->h=backgroundRect->h;
                overlapRisk=1;
        }

        else if(backgroundRect->y >= foregroundRect->y && backgroundRect->y <= foregroundRect->h + foregroundRect->y && backgroundRect->y + backgroundRect->h >=  foregroundRect->y + foregroundRect->h  ){

            for(yCounter = 0 ; backgroundRect->y + yCounter <= foregroundRect->y + foregroundRect->h && yCounter < backgroundRect->h ; yCounter++)

            overlapRect->y=0;
            overlapRect->h=yCounter;
            overlapRisk=1;
        }

        else if(backgroundRect->y <= foregroundRect->y && backgroundRect->y + backgroundRect->h >= foregroundRect->y && backgroundRect->y + backgroundRect->h <=  foregroundRect->y + foregroundRect->h){

            for(yCounter = 0; backgroundRect->y + yCounter <=  foregroundRect->y && yCounter < backgroundRect->h  ; yCounter++)
            overlapRect->y=yCounter;
            overlapRect->h=backgroundRect->h - yCounter;
            overlapRisk=1;
        }
    }

    if((backgroundRect->y >= foregroundRect->y && backgroundRect->y + backgroundRect->h <= foregroundRect->y + foregroundRect->h) || (backgroundRect->y >= foregroundRect->y && backgroundRect->y <= foregroundRect->h + foregroundRect->y && backgroundRect->y + backgroundRect->h >=  foregroundRect->y + foregroundRect->h) || (backgroundRect->y <= foregroundRect->y && backgroundRect->y + backgroundRect->h >= foregroundRect->y && backgroundRect->y + backgroundRect->h <=  foregroundRect->y + foregroundRect->h) ){
        
        if(backgroundRect->x >= foregroundRect->x && backgroundRect->x + backgroundRect->w <= foregroundRect->x + foregroundRect->w  ){
                overlapRect->x=0;
                overlapRect->w=backgroundRect->w;
                overlapRisk=1;
        }

        else if(backgroundRect->x >= foregroundRect->x && backgroundRect->x <= foregroundRect->w + foregroundRect->x && backgroundRect->x + backgroundRect->w >=  foregroundRect->x + foregroundRect->w  ){

            for(xCounter = 0 ; backgroundRect->x + xCounter <= foregroundRect->x + foregroundRect->w && xCounter < backgroundRect->w ; xCounter++)

            overlapRect->x=0;
            overlapRect->w=xCounter;
            overlapRisk=1;
        }

        else if(backgroundRect->x <= foregroundRect->x && backgroundRect->x + backgroundRect->w >= foregroundRect->x && backgroundRect->x + backgroundRect->w <=  foregroundRect->x + foregroundRect->w){

            for(xCounter = 0; backgroundRect->x + xCounter <=  foregroundRect->x && xCounter < backgroundRect->w  ; xCounter++)
            overlapRect->x=xCounter;
            overlapRect->w=backgroundRect->w - xCounter;
            overlapRisk=1;
        }
    }
    
    return overlapRisk;
}

