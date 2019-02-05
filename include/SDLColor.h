#ifndef SDLCOLOR
#define SDLCOLOR 

#include <SDL.h>


/*
 * ─── FONCTION DE MANIPULATION DE PIXELS ─────────────────────────────────────────
 */

    
//Fonction permettant d'accéder à un pixel en particulier en prenant en compte les différents formats de pixel disponible dans la bibliothèque SDL, cette fonction est tirée de la page http://sdl.beuc.net/sdl.wiki/Pixel_Access
Uint32 getpixel(SDL_Surface *surface, int x, int y);

//Fonction recherchant une couleur dans une surface si la couleur est trouvée la fonction renvoi 1, sinon 0, en cas d'erreur -1
short searchColorInSurface(SDL_Color *searchedColor, SDL_Rect *targetRect, SDL_Surface *surface, int accuracy);


/*
 * ─── FONCTION DE MANIPULATION DE COULEURS ───────────────────────────────────────
 */

    
//Fonction créant une couleur
SDL_Color SDLChangeRGBColor(int r, int g, int b , int a );

//Fonction comparant deux couleurs 
short SDLCompareColor(SDL_Color *firstColor, SDL_Color *secondColor);

//Fonction retournant une couleur aléatoire parmis une liste de couleur
void returnRandomColor(SDL_Color **arrColors, unsigned short sizeArrColor);

//Fonction renvoyant une valeur délimité par les valeurs MAX et MIN d'une couleur RGBA 0 => 255
int setOverflawColorComponent(int precedentComponent);


/*
 * ─── FONCTIONS NON UTILISEES ─────────────────────────────────────────────────────
 */

//Fonction remplacant une couleur cible par une couleur source dans une surface    
short replaceColorInSurface(SDL_Color *searchedColor,SDL_Color *replaceColor, SDL_Rect *targetRect, SDL_Surface *surface );

#endif
