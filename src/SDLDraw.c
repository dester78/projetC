#include <SDL.h>
#include <SDLDraw.h>



SDL_Color SDLChangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a ){

    SDL_Color RGBColor;

    RGBColor.r=r;
    RGBColor.g=g;
    RGBColor.b=b;
    RGBColor.a=a;

    return RGBColor;
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

        // printf("\n%p\n",surface);
        // printf("xCenter : %d\n",xCenter);
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

