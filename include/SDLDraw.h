#ifndef SDLDRAW
#define SDLDRAW

#include <SDL.h>
#include <SDLObjectsStructures.h>


//Alogithme de Bresenham permet de tracer des cercles en utilisant seulement des nombres entiers, modifie les pixels présent dans le tableau de pixel "pixels"
void drawCircle(Uint32 **pixels, int cx, int cy, int rayon,int wTexture, int hTexture, Uint32 pixelColor);

//Créer un cercle remplit d'une succession de rectangle de 1 pixel de hauteur et de n pixels de largeur
short drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color);

//Créer un rectangle de taille variable  
short drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect);

//Créer un triangle rempli et renvoie sa hauteur
short drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color, Orientation orientation );

//Premet de créer une forme géométrice en fonction l'énumération GeometricShape passé en paramètre et d'une énumération Orientation passé en paramètre, ce processus est repété deux fois, une fois pour dessiner les bords et une autre fois pour dessiner l'intérieur de la forme.
short drawGeometricShapeInGeometricShape(SDL_Surface *surface,SDL_Rect *rect,  Uint32 color, Uint32 insideColor, GeometricShape geometricShape, unsigned short centeringFactor, Orientation orientation);

// Vérifie si un pixel n'est pas positionné en dehors des coordonnées wSurface et hSurface et lui affecte une couleur donnée
void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wTexture, int hTexture, Uint32 pixelColor);


#endif
