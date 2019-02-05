#ifndef TRANSPORT
#define TRANSPORT

#include <stdio.h>

#include <SDLColor.h>
#include <SDLMetroLine.h>
#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>
#include <mathCalculation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLDraw.h>

#include <SDL.h>

//
// ─── FONCTIONS EVENEMENTIELS ─────────────────────────────────────────────────────
//

//Fonction gérant les différents événements liés aux actions menées par les utilisateurs sur les éléments de type voiture ou moteur (ajout, suppression)
short transportEventManager(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *leftContainer, SDLContainer *rightContainer, MetroLine ***arrMetroLines , Car ***arrCar, Engine ***arrEngine,int sizeArrMetroLine,unsigned short *sizeArrCar, unsigned short *sizeArrEngine, unsigned short transportSize,  SDL_Point *mousePoint, short selectBool);

//
// ─── FONCTIONS D'AFFICHAGE ───────────────────────────────────────────────────────
//


//Met à jour l'affichage des locomotives en prenant en compte leur orientation et les élements etant chevauchés par ces dernières
short updateDisplayEngines(SDL_Renderer *mainRenderer, SDLBackground *background,Engine ***arrEngine, MetroLine ***arrMetroLine, MetroStation ***arrMetroStation,unsigned short sizeArrEngine, unsigned short sizeArrMetroLine, int sizeArrMetroStation  );


//Copie une texture de locomotive en prenant en compte son orientation et en appliquant une rotation de cette dernière si besoin
short copyTransportTexture(SDL_Renderer *mainRenderer, Engine **engine);

//Fonction permettant de créer une voiture, de l'affecter à un moteur ou de l'affecter à une autre voiture si le moteur en possède déja. Sa position est déterminée en fonction de l'élement auquel elle est rattachée ainsi qu'à la direction de cette élément.
// void createCar(Engine **engine,Car **car,MetroLine **metroLine, unsigned short transportSize, unsigned short sizeArrPassenger);
short controlTransportIntersection(SDL_Renderer *mainRenderer,Engine **engine, MetroStation ***arrMetroStation,int sizeArrMetroStation, MetroLine ***arrMetroLine, int sizeArrMetroLine);


//
// ─── FONCTIONS DE GESTION DE POSITION ET DE DEPLACEMENT ─────────────────────────
//

//Recalcul la position d'une locomotive en fonction de son orientation 
void defineNewEnginePosition(Engine **engine);


//Détermine la direction d'une locomotive en fonction des pointeurs suivant et précedent de la liste chainée de segment auquel elle est rattachée
void controlDirectionPointer(Engine **engine);

//Fonction qui détermine une nouvelle direction d'une locomotive en fonction de sa présence sur un point source ou destination, change de direction lorsque ces points source ou destination se trouvent en bout de ligne.
Direction controlDirectionPosition(Engine **engine);

//Détermine l'orientation d'une locomotive en fonction de sa station destination et de sa position vis à vis d'elle, ce changement d'orientation se déclenche quand la locomotive passe par un point de passage
void defineNewEngineOrientation(Engine **engine);

// Engine* getLightestEngineOnLine(MetroLine **metroLine, Engine ***arrEngine, unsigned short sizeArrEngine);
void defineNewEngineDirection(Engine **engine);

//Fonction permettant de déterminer les points source, passage et destination en valeur absolue et de recalculer l'orientation d'une locomotive en fonction de ces changement
void definePositionAndOrientationEngine(Engine **engine,SDL_Point *precedentPathPoint, SDL_Point *relativeSrcPoint,SDL_Point *relativePathPoint, SDL_Point *relativeDstPoint, SDL_Rect *relativeSrcRect, SDL_Rect *relativeDstRect, SDL_Rect *parentRect);


//
// ─── FONCTIONS DE CREATION ──────────────────────────────────────────────────────
//

 //Fonction permettant de créer soit un moteur soit une voiture. 
short createTransport(SDL_Renderer *mainRenderer,Car **car, Engine **engine, MetroLine **metroLine, unsigned short transportSize,unsigned short sizeArrPassenger, TransportType transportType);

//Fonction permettant de créer un moteur, de lui attribuer une position de départ sur la première station de métro d'une ligne de métro et de déterminer sa direction en fonction de son prochain point de passage. 
short createEngine(SDL_Renderer *mainRenderer,Engine **engine,MetroLine **metroLine, unsigned short transportSize);



//
// ─── FONCTIONS EN CONSTRUCTION ──────────────────────────────────────────────────
//

// Car *getLastCar(Engine **currentEngine, Car **currentCar, unsigned short *carCounter);


#endif 