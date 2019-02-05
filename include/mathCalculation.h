#ifndef MATHCALCULATION
#define MATHCALCULATION

#include <math.h>

#include <SDL.h>

//
// ─── FONCTIONS DE CALCULS MATHEMATIQUES ───────────────────────────────────────────
//

//Calcul la distance euclidienne entre deux points
int distanceBetweenTwoPoint(SDL_Point *firstPoint, SDL_Point *secondPoint);

//Convertie un radian en degré
double radToDeg(double rad);

//Renvoie un nombre aléatoire compris entre une valeur minimal et maximale
int randInRange(int lowerValue, int higherValue);

//Renvoie le diamètre d'un cercle cirsconscrit dans un rectangle
int diamCircumscribeCircleOnRect(int length, int width);

#endif