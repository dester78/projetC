
#include <stdio.h>
#include <stdlib.h>

#include <SDLDraw.h>

#include <SDL.h>



SDL_Color SDLChangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a ){

    SDL_Color RGBColor;

    RGBColor.r=r;
    RGBColor.g=g;
    RGBColor.b=b;
    RGBColor.a=a;

    return RGBColor;
}

short SDLCompareColor(SDL_Color *firstColor, SDL_Color *secondColor){

    if(firstColor->r==secondColor->r&&firstColor->g==secondColor->g&&firstColor->b==secondColor->b&&firstColor->a==secondColor->a){
        return 1;
    }
    return 0;
}

SDL_Rect SDLChangeRect(int x , int y , int w , int h){

    SDL_Rect newRect; 

    newRect.x=x;
    newRect.y=y;
    newRect.w=w;
    newRect.h=h;

    return newRect;
}

void returnRandomColor(SDL_Color **arrColors, unsigned short sizeArrColor){

    SDL_Color tmpColor;
    

    for(unsigned short counterColor=0; counterColor < sizeArrColor; counterColor++ ){

        short unikColor=1;
        switch((rand()%sizeArrColor)+1){

            case 1 :
                tmpColor=SDLChangeRGBColor(35,63,68,255);
            break; 

            case 2 : 
                tmpColor=SDLChangeRGBColor(165,93,8,255);
            break; 

            case 3 : 
                tmpColor=SDLChangeRGBColor(143,17,91,255);
            break; 

            default : 
                tmpColor=SDLChangeRGBColor((rand()%255)+1,(rand()%255)+1,(rand()%255)+1,255);
            break;
        }

        if(SDLCompareColor(&(*arrColors)[counterColor],&tmpColor)==0){

            for(short counterColorBis=counterColor-1; counterColorBis>=0 ; counterColorBis-- ){
                
                if(SDLCompareColor(&(*arrColors)[counterColorBis],&tmpColor)){
                    unikColor=0;
                    break;
                }
            }
            if(unikColor){
                (*arrColors)[counterColor]=SDLChangeRGBColor(143,17,91,255);
            }
        } 
    }
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

    int xCounter ,yCounter;
    unsigned short overlapRisk=0;
    SDL_Rect tmpRect;

    tmpRect.w=0;
    tmpRect.h=0;

    if((backgroundRect->x >= foregroundRect->x && backgroundRect->x + backgroundRect->w <= foregroundRect->x + foregroundRect->w) || (backgroundRect->y > foregroundRect->y && backgroundRect->y < foregroundRect->h + foregroundRect->y) || (backgroundRect->y < foregroundRect->y && backgroundRect->y + backgroundRect->h > foregroundRect->y)){

        
        if(backgroundRect->y >= foregroundRect->y && backgroundRect->y + backgroundRect->h <= foregroundRect->y + foregroundRect->h ){
            tmpRect.y=0;
            tmpRect.h=backgroundRect->h;
            overlapRisk=1;
        }

        else if(backgroundRect->y > foregroundRect->y && backgroundRect->y < foregroundRect->h + foregroundRect->y){

            for(yCounter = 0 ; backgroundRect->y + yCounter <foregroundRect->y + foregroundRect->h && yCounter <backgroundRect->h ; yCounter++){}
            tmpRect.y=0;
            tmpRect.h=yCounter;
            overlapRisk=1;
        }

        else if(backgroundRect->y < foregroundRect->y && backgroundRect->y + backgroundRect->h > foregroundRect->y){

            for(yCounter = 0; backgroundRect->y + yCounter <  foregroundRect->y && yCounter < backgroundRect->h  ; yCounter++){}
            tmpRect.y=yCounter;
            tmpRect.h=backgroundRect->h - yCounter + 1;
            overlapRisk=1;
        }
    }

    if((backgroundRect->y >= foregroundRect->y && backgroundRect->y + backgroundRect->h <= foregroundRect->y + foregroundRect->h) || (backgroundRect->x > foregroundRect->x && backgroundRect->x < foregroundRect->w + foregroundRect->x ) ||(backgroundRect->x < foregroundRect->x && backgroundRect->x + backgroundRect->w > foregroundRect->x )){
        
        if(backgroundRect->x > foregroundRect->x && backgroundRect->x + backgroundRect->w <= foregroundRect->x + foregroundRect->w){
            tmpRect.x=0;
            tmpRect.w=backgroundRect->w;
            overlapRisk=1;
        }

        else if(backgroundRect->x > foregroundRect->x && backgroundRect->x < foregroundRect->w + foregroundRect->x ){

            for(xCounter = 0 ; backgroundRect->x + xCounter < foregroundRect->x + foregroundRect->w && xCounter < backgroundRect->w ; xCounter++){}
            tmpRect.x=0;
            tmpRect.w=xCounter;
            overlapRisk=1;
        }

        else if(backgroundRect->x < foregroundRect->x && backgroundRect->x + backgroundRect->w > foregroundRect->x ){

            for(xCounter = 0; backgroundRect->x + xCounter <  foregroundRect->x && xCounter < backgroundRect->w  ; xCounter++){}
            tmpRect.x=xCounter;
            tmpRect.w=backgroundRect->w - xCounter+1;
            overlapRisk=1;
        }
    }
    if(overlapRect!=NULL){
        *overlapRect=tmpRect;
    }
    
    return overlapRisk;
}


void createLineRect(SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Rect *lineRect, SDL_Point *srcPoint, SDL_Point *dstPoint){

    if(srcRect->x < dstRect->x){

        lineRect->x=srcRect->x + srcRect->w / 2; 
        lineRect->w=(dstRect->x + dstRect->w / 2) - (srcRect->x + srcRect->w / 2);
        dstPoint->x=lineRect->w;
        srcPoint->x=0;
    }

    if(srcRect->x > dstRect->x){
        lineRect->x = dstRect->x + dstRect->w / 2; 
        lineRect->w = (srcRect->x + srcRect->w / 2) - (dstRect->x + dstRect->w/2);
        srcPoint->x = lineRect->w;
        dstPoint->x = 0;
    }

    if(srcRect->y < dstRect->y){

        lineRect->x=srcRect->y + srcRect->h / 2; 
        lineRect->h=(dstRect->y+ dstRect->h / 2) - (srcRect->y + srcRect->h / 2);
        dstPoint->x=lineRect->h;
        srcPoint->x=0;
    }

    if(srcRect->y> dstRect->y){
        lineRect->y= dstRect->y+ dstRect->h / 2; 
        lineRect->h = (srcRect->y+ srcRect->h / 2) - (dstRect->y+ dstRect->h/2);
        srcPoint->y= lineRect->h;
        dstPoint->y= 0;
    }
}
