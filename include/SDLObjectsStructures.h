#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include<SDLConfigStructures.h>

#include <SDL.h>
#include <SDLColor.h>
#include <mysql.h>
#include <SDL_ttf.h>
#include <fileManager.h>

//Enumération utilisée principalement pour dessiner des formes géométriques
typedef enum GeometricShape {_CIRCLE_, _SQUARE_, _TRIANGLE_} GeometricShape;
//Enumération utilisée pour différencier la position des conteneurs dans la fenêtre du jeu
typedef enum ContainerPosition {_LEFT_,_CENTER_,_RIGHT_}ContainerPosition;
//Enumération utilisée pour différencier les différents niveaux du jeu
typedef enum LevelName {_PARIS_} LevelName;
//Enumération utilisée pour indiquer dans quel mode se trouve le jeu 
typedef enum MenuLevel {_MENU_,_LEVEL_} MenuLevel;
//Enumération utilisée pour différencier les boutons ayant pour source des images
typedef enum ButtonName {_ENGINE_BTN_,_CAR_BTN_,_PLAY_,_PAUSE_,_FASTER_}ButtonName;
//Enumération utilisée pour différencier les modes de transport du jeu
typedef enum TransportType {_ENGINE_,_CAR_}TransportType;
//Enumération utilisée pour symboliser des axes dans l'affichage des éléments de la fenêtre du jeu
typedef enum Axe {_X_,_Y_} Axe;
//Enumération utilisée pour indiquer l'orientation d'un élément dans la fenêtre du jeu
typedef enum Orientation {_BOTTOM_TOP_,_TOP_BOTTOM_,_LEFT_RIGHT_,_RIGHT_LEFT_} Orientation;

typedef enum Direction {_FORWARD_,_BACKWARD_}Direction;

//Structure représentant un élément de type texte, ces derniers se basent sur SDL_TTF pour l'affichage de texte possédant une police de caractère donnée
typedef struct SDLText{

    SDL_Surface *surface;
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Color color; 
    SDL_Rect rect;

    unsigned short sizeFont;
    char *fontPath;
    char *content;
}SDLText;

//Structure représentant un bouton plusieurs états sont disponibles et influent directement sur la façon dont ces boutons seront affichés
typedef struct SDLButtons{

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Surface *backgroundSurface;
    SDL_Texture *backgroundTexture;  
    struct MetroLine *metroLine;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color savedColor;
    SDL_Color insideColor;
    ButtonName buttonName;

    unsigned short hover;
    unsigned short selected;
    unsigned short display;
    SDLText *text;
    
}SDLButtons;

//Structure principalement utilisée pour organiser le contenu dans la fenêtre de jeu
typedef struct SDLContainer{

    unsigned short sizeArrayButtons;
    unsigned short sizeArrayText;

    SDLButtons **arrayButtons;
    SDLText **arrayText;

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;

//Structure mère pour l'affichage du texte et des boutons dans le jeu
typedef struct SDLGUI{

    SDLContainer *container;
    SDLContainer *leftContainer;
    SDLContainer *rightContainer;

    
}SDLGUI;

//Structure représentant un passager et ses stations de destinations
typedef struct Passenger{
    
    SDL_Surface *surface;
    SDL_Texture *texture;
    GeometricShape metroStationWant;  
}Passenger;

//Structure représentant une station de métro, cette dernière dispose de deux états affiché ou non, sélectionnée ou non et peut dans certain cas disposer d'un tableau recensant les stations les plus proches de sa position ainsi que les passagers présent dans cette dernière
typedef struct MetroStation{

    short display;
    short selected;

    unsigned short sizeArrPassenger;
    unsigned short passengersSatisfaction;

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Point centerPoint;

    GeometricShape geometricShape;
    struct MetroStation **arrOtherMetroStations;
    struct Passenger **arrPassenger;

    SDL_Color insideColor;
    SDL_Color color;
    SDL_Color srcStationColor;
    SDL_Color dstStationColor;

}MetroStation;

//Structure représentant une liaison entre deux stations, cette dernière est obligatoirement rattachée à une ligne de métro
typedef struct MetroSegment{

    short display;

    SDL_Point srcPointInRect;
    SDL_Point dstPointInRect;
    SDL_Point pathPointInRect;
    
    SDL_Rect srcPointToPathPointRect;
    SDL_Rect pathPointToDstPointRect;

    MetroStation *srcStation;
    MetroStation *dstStation;
    struct MetroSegment *nextSegment;
    struct MetroSegment *precedentSegment;
    
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect rect; 
    
}MetroSegment;

//Structure représentant une ligne de métro elle est composé de 0 ou plusieurs segments et a sa propre couleur
typedef struct MetroLine{

    unsigned short sizeArrSegment;
    MetroSegment **arrMetroSegment;  
    MetroStation *srcMetroStation;
    SDL_Color color;

}MetroLine;

//Structure représentant un moteur, le moteur peut ou pas avoir des voitures rattachée et sert de référence pour toutes ses voitures rattachées. En effet son orientation et son mouvement impactera directement ses voitures rattachées
typedef struct Engine{

    
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Point srcPoint;
    SDL_Point pathPoint;
    SDL_Point dstPoint;
    SDL_Color insideColor;
    SDL_Color color;
    Direction direction;
    Orientation orientation;

    unsigned short display;

    MetroSegment *currentMetroSegment;
    MetroLine *metroLine;
    struct Car *precedentCar;

}Engine;

//Structure représentant une voiture elle peut contenir des passagers si les arrêts de son moteur son en accord avec les besoins de ses passagers et est obligatoirement rattachée à un moteur
typedef struct Car{

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Color insideColor;
    SDL_Color color;
    SDL_Rect rect;

    unsigned short sizeArrPassenger;
    unsigned short display;

    Orientation orientation;

    Passenger **arrPassenger;
    Engine *engine;
    struct Car *nextCar;
    struct Car *precedentCar;

}Car;

//Structure représentant le background elle possède de nombreuses informations sur les éléments au coeur du gameplay
typedef struct SDLBackground{

    SDL_Surface *surface;
    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

    unsigned short sizeMetroStation;
    unsigned short sizeTransport;
    unsigned short metroLineThickness;
    unsigned short sizeArrMetroLinesColor; 
    unsigned short sizeArrMetroStations;
    unsigned short sizeArrMetroLines;
    unsigned short sizeArrEngine;
    unsigned short sizeArrCar;
    unsigned short countUnlockMetroLine;
    unsigned short countMetroStation;


    SDL_Color *arrMetroLinesColor;
    MetroStation **arrMetroStations;
    MetroLine **arrMetroLines;
    Car **arrCar;
    Engine **arrEngine;

    MetroStation *selectedStation;
    MetroLine *selectedMetroLine;
    
}SDLBackground;

//Structure unique à chaque niveau et regroupe des informations nécessaires au gameplay 
typedef struct SDLLevel{

    unsigned short difficulty;
    double satisfactionFactor;
    unsigned int cycleCounter;
    unsigned int cycleDuration;
    unsigned int cycleProgression;

    unsigned int passengersCount;

    LevelName levelName;

    SDLBackground *background;

}SDLLevel;

//Structure regroupant des informations temporelles afin de gérer les évenements générés par l'utilisateur et les délais de raffraichissement de la fenêtre de jeu
typedef struct SDLTimer{

    int refreshCurrentTime;
    int refreshPastTime;
    int userEventCurrentTime;
    int userEventPastTime;
    int addMetroStationCurrentTime;
    int addMetroStationPastTime;
    int clickTime;
    int refreshFrequency;
    int metroStationApparitionFrequency;
}SDLTimer;

//Structure regroupant tout l'environnement du jeu sa composition varie selon le contexte menu ou niveau
typedef struct SDLEnvironment{

    SDL_Renderer *mainRenderer;
    SDL_Window *mainWindow;
    SDL_Event event;

    SDLLevel *level;
    SDLTimer *timer;
    SDLBackground *background;
    SDLGUI *gui;  

}SDLEnvironment;

//Fonctions d'initialisation de structures
SDLEnvironment *initSDLEnvironment( SDL_Window *mainWindow,SDL_Renderer *mainRenderer);
SDLGUI *initGUIHostMenu(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement,MYSQL *dbConnection);
SDLGUI *initGUILevel(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement);
SDLBackground *initBackgroundHostMenu(SDL_Window *mainWindow);
SDLTimer *initTimer(int refreshFrequency);
SDLContainer *initContainer(SDL_Window *mainWindow,ContainerPosition,unsigned short sizeArrayButtons);
short initButtonsHostMenu( SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, unsigned short sizeArrayButtons, short connectionState);
short initButtonSideContainerLevel(SDLContainer *container, ContainerPosition containerPosition,  char *fontPath, SDLBackground *backgroundLevel);
void initMetroStation(MetroStation *metroStation, unsigned short geometricShape, SDL_Rect *rect, SDL_Color *color, SDL_Color *insideColor, SDL_Color *srcStationColor, SDL_Color *dstStationColor );
void initMetroLine(MetroLine *metroLine,unsigned short width,  SDL_Color color);
SDLLevel *initGameLevel(SDLTimer *timer, LevelName levelName,char *backgroundIMGPath, unsigned short difficulty,File *metroLineColorFile,SDL_Rect *borderContainer);
SDLBackground *initLevelBackground(  char *backgroundIMGPath, File *metroLineColorFile, LevelName levelName, SDL_Rect *borderContainer, unsigned short sizeArrCar, unsigned short sizeArrEngine, unsigned short sizeArrMetroStation, unsigned short sizeMetroStation, unsigned short sizeTransport );


//Fonctions de libération mémoire des structures
void freeSDLLevel(SDLLevel *level);
void freeSDLContainer(SDLContainer *container);
void freeSDLButton(SDLButtons *sdlButtonElement);
void freeSDLText(SDLText *sdlTextElement);
void freeBackground(SDLBackground *background);
void freeMetroLine(MetroLine *metroLine);
void freeMetroSegment(MetroSegment *metroSegment);
void freeMetroStation(MetroStation *metroStation);
void freeSDLGUI(SDLGUI *gui);
void freeSDLEnvironment(SDLEnvironment *environment);




// void initBackgroundHostMenu(SDL_Window *mainWindow,SDLBackground *backgroundHostMenu);
// SDLBackground *initLevelBackground(char *backgroundIMGPath,  File *metroLineColorFile, LevelName levelName, SDL_Rect *borderContainer);
#endif