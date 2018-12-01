#ifndef STRUCTURES
#define STRUCTURES
#include <SDL.h>
#include <stdio.h>

typedef struct Files{

    char *fullName;
    char  openMode[4];
    FILE *filePointer;

}Files;


typedef struct DbConfig{

    char* host;
    char* user;
    char* passwd;
    char* db;


}DbConfig;

typedef struct SDLConfig{

    
    struct SDLWindowConfig *window;
    struct SDLInitConfig *init;
    
    
}SDLConfig;


typedef struct SDLWindowConfig{

    long unsigned windowFlag;

}SDLWindowConfig;

typedef struct SDLInitConfig{

    long unsigned initFlag;

}SDLInitConfig;

typedef struct SDLButtons{



}SDLButtons;




int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
Files returnFileElement(char *fullName, char* openMode);

void freeDbConfigElement(DbConfig *dbConfigElement );
void freeSDLConfigElement(SDLConfig *SDLConfigElement );
void freeFileElement(Files fileElement);


#endif 