#ifndef METROLINE
#define METROLINE

#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>
#include <SDLMetroLine.h>


#include<SDL.h>

//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//

//Gere les evenements generes par les utilisateurs concernant des lignes de metro
short metroLineEventManagerLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *container, MetroLine **arrMetroLines , MetroStation **arrMetroStations, Engine ***arrEngine, int sizeArrMetroLine,int sizeArrMetroStations,int sizeArrEngine, unsigned short metroLineThickness, SDL_Point *mousePoint, short selectBool, ContainerPosition containerPosition);

//Ajout et suppression de segment en fonction des lignes de métros et stations sélectionnées par l'utilisateur 
short manageMetroSegmentLevel(SDL_Renderer *mainRenderer, SDLBackground *background, MetroLine **metroLine, MetroStation **arrMetroStations, Engine ***arrEngine, MetroSegment **currentMetroSegment, int sizeArrMetroStation, int sizeArrEngine,short counterMetroLine, short metroLineThickness,short addDeleteBool);

//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//

//Met à jour l'affichage des lignes de métro dans un niveau
short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations);

//Met à jour l'affiche du segment, créer une texture si le segment n'en possède pas sinon copie directement sa texture dans le rendu
short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine);


short updateDisplayMetroLineMenu(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons);

//
// ─── FONCTIONS DE GESTION DE POSITION  ─────────────────────────
//

//Créer les deux SDL_Rect qui composent la partie visible d'uun segment
void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine);

//Place les points source et destination dans leurs stations de métro en prenant garde à ce que ces points ne chevauchent pas des points d'autres lignes de métro. Leurs positions sont déterminées par l'ordre de leur ligne dans le tableau de ligne de métro.
void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness);

//Règle les width et height d'un SDL_Rect de segment en fonction de l'épaisseur de ligne de métro
void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine);

//Règle l'emplacement d'un point de passage de segment en fonction de son segment précédent pour améliorer la lisibité de la ligne de métro
void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect);

//Règle l'emplacement d'un point d'extrémité de segment dans une station de métro, utilisé principalement pour les stations de forme triangle
void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape);

//Création des éléments géométriques nécessaires à l'affichage d'un segment, position, taille et forme
void createGeometryMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, MetroStation * srcStation, MetroStation *dstStation, short counterMetroLine, short metroLineThickness);


//
// ─── FONCTIONS DE MANIPULATION DE POINTEURS DE SEGMENT ──────────────────────────
//

//Classe un tableau de segment en y ajoutant au début un nouvel élément 
void reorderMetroSegmentsLastToFirst(MetroSegment ***arrMetroSegment, unsigned short sizeArrSegment);

//Attribue à un segment une station source et destination en fonction des segments lui étant contigue
void reorderSrcAndDestStations(MetroSegment **currentMetroSegment, MetroStation **srcMetroStation, MetroStation **dstMetroStation, unsigned short order);

//Attribue à un segment une station de métro source et destination 
void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool);

//Supprime un segment et affiche une portion du background sur son ancien emplacement
short deleteSegment(SDL_Renderer *mainRenderer, SDLBackground *background,MetroSegment ***arrMetroSegment,MetroSegment **currentMetroSegment, unsigned short *sizeArrMetroSegment);

//Vérifie qu'une locomotive ne se trouve pas sur un segment suivant du segment courant
short controlEngineOnLine(Engine ***arrEngine, int sizeArrEngine,MetroSegment **currentMetroSegment);

//Ajoute un nouveau segment dans un tableau de segment et met à jour les liens d'une liste de segment contigues au nouveau segment
MetroSegment *addNewSegment(MetroSegment ***arrMetroSegment, MetroStation **srcStation , MetroStation **dstStation, unsigned short *sizeArrMetroSegment, short *addBool );

//Retourne 1 si la station est ajoutée en début de ligne, 2 pour une fin de ligne et 0 si la station est déja présente sur la ligne
short getSegmentWithOrder(MetroSegment ***arrMetroSegment,MetroStation **srcStation , MetroStation **dstStation, unsigned short sizeArrSegment);

//
// ─── FONCTIONS DE CREATION DE SEGMENTS ET LIGNES DE METRO ───────────────────────
//

//Créer pour chaque éléments d'un tableau de lignes de métro une ligne de métro et y affecte un tableau de segment alloué dynamiquement
short SDLCreateMetroLineMenu(SDLBackground *backgroundMenu);

//Parcours le tableau de lignes de métros et leurs tableaux de segments respéctifs afin d'y créer des segments, ce parcours est possible uniquement dans le cas d'une création automatique de segments
short SDLCreateMetroSegmentMenu(SDLBackground *backgroundMenu);




#endif 