#ifndef STRUCTURES
#define STRUCTURES
#include <SDL.h>


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




void initDbConfig(DbConfig *dbConfigElement, char ***arrayParameters);
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char ***arrayParameters);
void initSDLInitConfig(SDLInitConfig *initConfigElement, char ***arrayParameters);
void initSDLConfig(SDLConfig *SDLConfigElement,char ***arrayParameters);


#endif 