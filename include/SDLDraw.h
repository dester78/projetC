#ifndef SDLDRAW
#define SDLDRAW

#include <SDL.h>


//Renvoie une structure SDLColor
SDL_Color SDLChangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a );

//Alogithme de Bresenham permet de tracer des cercles en utilisant seulement des nombres entiers, modifie les pixels présent dans le tableau de pixel "pixels"
void drawCircle(Uint32 **pixels, int cx, int cy, int rayon,int wTexture, int hTexture, Uint32 pixelColor);

//Créer un cercle remplit d'une succession de rectangle de 1 pixel de hauteur et de n pixels de largeur
void drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color);

//Créer un rectangle de taille variable  
void drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect);

// Vérifie si un pixel n'est pas positionné en dehors des coordonnées wSurface et hSurface et lui affecte une couleur donnée
void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wTexture, int hTexture, Uint32 pixelColor);

#endif