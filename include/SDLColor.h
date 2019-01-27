#ifndef SDLCOLOR
#define SDLCOLOR 

#include <SDL.h>



Uint32 getpixel(SDL_Surface *surface, int x, int y);
SDL_Color SDLChangeRGBColor(int r, int g, int b , int a );
short SDLCompareColor(SDL_Color *firstColor, SDL_Color *secondColor);
void returnRandomColor(SDL_Color **arrColors, unsigned short sizeArrColor);

// short SDLControlColorOverflow(SDL_Color *precedentColor,SDL_Color *overflawColor, int r, int g, int b, int a );
// SDL_Color SDLChangeRGBColorOverflawControl(SDL_Color *precedentColor, SDL_Color *overfalwColor,int r, int g, int b , int a );
int setOverflawColorComponent(int precedentComponent);
short searchColorInSurface(SDL_Color *searchedColor, SDL_Rect *targetRect, SDL_Surface *surface, int accuracy);
short replaceColorInSurface(SDL_Color *searchedColor,SDL_Color *replaceColor, SDL_Rect *targetRect, SDL_Surface *surface );

#endif
