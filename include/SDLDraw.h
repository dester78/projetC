#ifndef SDLDRAW
#define SDLDRAW

#include <SDL.h>


//Renvoie une structure SDL_Color
SDL_Color SDLChangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a );

//Renvoie une structure SDL_Rect
SDL_Rect SDLChangeRect(int x , int y , int w , int h);

//Alogithme de Bresenham permet de tracer des cercles en utilisant seulement des nombres entiers, modifie les pixels présent dans le tableau de pixel "pixels"
void drawCircle(Uint32 **pixels, int cx, int cy, int rayon,int wTexture, int hTexture, Uint32 pixelColor);

//Créer un cercle remplit d'une succession de rectangle de 1 pixel de hauteur et de n pixels de largeur
void drawFillCircle(SDL_Surface **surface, int xCenter, int yCenter, int radius, Uint32 color);

//Créer un rectangle de taille variable  
void drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect);

//Créer un triangle rempli et renvoie sa hauteur
int drawFillTriangle(SDL_Surface **surface, int xLeftRoot, int yLeftRoot, int wRoot, Uint32 color ); 

// Vérifie si un pixel n'est pas positionné en dehors des coordonnées wSurface et hSurface et lui affecte une couleur donnée
void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wTexture, int hTexture, Uint32 pixelColor);

//Fonction qui renvoie 1 si le foregroundRect a des coordonnées en commun avec le backgroundRect et modifie le overlapRect pour récupérer les coordonnées de chevauchement
unsigned short createOverlapRect(SDL_Rect *foregroundRect, SDL_Rect *backgroundRect, SDL_Rect *overlapRect); 

//Fonction qui permet de modifier pixel par pixel la couleur des zones de chevauchement de deux surfaces, précis mais à utiliser seulement sur des petites surfaces
void changeOverlapColorSurfaces(SDL_Rect *foreGroundRect, SDL_Surface **backGroundSurface, SDL_Rect *backGroundRect, Uint32 overlapColor);

//Modifie un SDL_Rect afin d'y tracer une ligne à l'intérieur par la suite, le point de départ de la ligne et son arrivée sont renseignés
void createLineRect(SDL_Rect *srcRect, SDL_Rect *dstRect, SDL_Rect *lineRect, SDL_Point *srcPoint, SDL_Point *dstPoint);
#endif