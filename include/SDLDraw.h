#ifndef SDLDRAW
#define SDLDRAW

#include <SDL.h>
#include <SDLObjectsStructures.h>


 void drawGeometricShapeInGeometricShape(SDL_Surface *surface,SDL_Rect *rect,  Uint32 color, Uint32 insideColor, GeometricShape geometricShape, unsigned short centeringFactor, TriangleOrientation triangleOrientation);
//Alogithme de Bresenham permet de tracer des cercles en utilisant seulement des nombres entiers, modifie les pixels présent dans le tableau de pixel "pixels"
void drawCircle(Uint32 **pixels, int cx, int cy, int rayon,int wTexture, int hTexture, Uint32 pixelColor);

//Créer un cercle remplit d'une succession de rectangle de 1 pixel de hauteur et de n pixels de largeur
void drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color);

//Créer un rectangle de taille variable  
void drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect);

//Créer un triangle rempli et renvoie sa hauteur
int drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color, TriangleOrientation );


// Vérifie si un pixel n'est pas positionné en dehors des coordonnées wSurface et hSurface et lui affecte une couleur donnée
void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wTexture, int hTexture, Uint32 pixelColor);

//Fonction qui permet de modifier pixel par pixel la couleur des zones de chevauchement de deux surfaces, précis mais à utiliser seulement sur des petites surfaces
void changeOverlapColorSurfaces(SDL_Rect *foreGroundRect, SDL_Surface *backgroundSurface, SDL_Rect *backGroundRect, Uint32 overlapColor);

void drawTimeButton(SDL_Surface *surface,SDL_Rect *rect,  SDL_Color *color,  ButtonName  buttonName);
#endif
