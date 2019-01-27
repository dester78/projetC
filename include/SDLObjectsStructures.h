#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include<SDLConfigStructures.h>

#include <SDL.h>
#include <SDLColor.h>
#include <mysql.h>
#include <SDL_ttf.h>
#include <fileManager.h>

 
typedef enum GeometricShape {_CIRCLE_, _SQUARE_, _TRIANGLE_} GeometricShape;
typedef enum ContainerPosition {_LEFT_,_CENTER_,_RIGHT_}ContainerPosition;
typedef enum LevelName {_PARIS_} LevelName;
typedef enum MenuLevel {_MENU_,_LEVEL_} MenuLevel;
typedef enum ButtonName {_LOCO_,_RAILCAR_,_PLAY_,_PAUSE_,_FASTER_}ButtonName;
typedef enum Axe {_X_,_Y_} Axe;
typedef enum TriangleOrientation {_BOTTOM_TOP_,_LEFT_RIGHT_} TriangleOrientation;


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


typedef struct SDLContainer{

    unsigned short sizeArrayButtons;
    unsigned short sizeArrayText;

    SDLButtons **arrayButtons;
    SDLText **arrayText;

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;


typedef struct SDLGUI{

    SDLContainer *container;
    SDLContainer *leftContainer;
    SDLContainer *rightContainer;

    
}SDLGUI;

typedef struct Passenger{
    
    GeometricShape metroStationWant;
    

}Passenger;

typedef struct MetroStation{

    
    short display;
    short selected;

    unsigned short sizeArrPassenger;
    unsigned short sizeArrLinkedMetroSegment;
    unsigned short passengersSatisfaction;

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Point centerPoint;

    GeometricShape geometricShape;
    struct MetroStation **arrOtherMetroStations;
    struct MetroSegment **arrLinkedMetroSegment;
    struct Passenger **arrPassenger;

    SDL_Color insideColor;
    SDL_Color color;
    SDL_Color srcStationColor;
    SDL_Color dstStationColor;

}MetroStation;

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


typedef struct MetroLine{

    unsigned short sizeArrSegment;
    MetroSegment **arrMetroSegment;  
    MetroStation *srcMetroStation;
    SDL_Color color;

}MetroLine;

typedef struct Engine{

    
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;

    MetroLine *metroLine;
    struct Car *firstCar;

}Engine;


typedef struct Car{

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;

    unsigned short sizeArrPassenger;

    Passenger **arrPassenger;
    Engine engine;
    struct Car *nextCar;
    struct Car *beforeCar;

}Car;


typedef struct SDLBackground{

    SDL_Surface *surface;
    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

    unsigned short sizeMetroStation;
    unsigned short metroLineThickness;
    unsigned short sizeArrMetroLinesColor; 
    unsigned short sizeArrMetroStations;
    unsigned short sizeArrMetroLines;
    unsigned short sizeArrLoco;
    unsigned short sizeArrRailCar;
    unsigned short countUnlockMetroLine;
    unsigned short countMetroStation;


    SDL_Color *arrMetroLinesColor;
    MetroStation **arrMetroStations;
    MetroLine **arrMetroLines;

    MetroStation *selectedStation;
    MetroLine *selectedMetroLine;
    
}SDLBackground;


typedef struct SDLLevel{

    unsigned short difficulty;
    unsigned short metroStationApparitionFrequency;
    double satisfactionFactor;
    unsigned int cycleCounter;
    unsigned int cycleDuration;
    unsigned int cycleProgression;

    unsigned int passengersCount;

    LevelName levelName;

    SDLBackground *background;

}SDLLevel;

typedef struct SDLTimer{

    int currentTime;
    int pastTime;
    int clickTime;
}SDLTimer;


typedef struct SDLEnvironment{

    SDL_Renderer *mainRenderer;
    SDL_Window *mainWindow;
    SDL_Event event;

    SDLLevel *level;
    SDLTimer *timer;
    SDLBackground *background;
    SDLGUI *gui;  

}SDLEnvironment;

SDLEnvironment *initSDLEnvironment( SDL_Window *mainWindow,SDL_Renderer *mainRenderer);

SDLGUI *initGUIHostMenu(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement,MYSQL *dbConnection);
SDLGUI *initGUILevel(SDL_Window  *mainWindow, SDLConfig *SDLConfigElement);
SDLBackground *initBackgroundHostMenu(SDL_Window *mainWindow);
SDLTimer *initTimer();

// void initBackgroundHostMenu(SDL_Window *mainWindow,SDLBackground *backgroundHostMenu);
SDLContainer *initContainer(SDL_Window *mainWindow,ContainerPosition,unsigned short sizeArrayButtons);
short initButtonsHostMenu( SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, unsigned short sizeArrayButtons, short connectionState);
short initButtonSideContainerLevel(SDLContainer *container, ContainerPosition containerPosition,  char *fontPath, SDLBackground *backgroundLevel);
void initMetroStation(MetroStation *metroStation, unsigned short geometricShape, SDL_Rect *rect, SDL_Color *color, SDL_Color *insideColor, SDL_Color *srcStationColor, SDL_Color *dstStationColor );
void initMetroLine(MetroLine *metroLine,unsigned short width,  SDL_Color color);




SDLLevel *initGameLevel(LevelName levelName,char *backgroundIMGPath, unsigned short difficulty,File *metroLineColorFile,SDL_Rect *borderContainer);
SDLBackground *initLevelBackground(char *backgroundIMGPath,  File *metroLineColorFile, LevelName levelName, SDL_Rect *borderContainer);

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


#endif