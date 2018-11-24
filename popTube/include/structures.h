#ifndef STRUCTURES
#define STRUCTURES
#include <SDL2/SDL.h>


typedef struct DbConfig{

    char* host;
    char* user;
    char* passwd;
    char* db;


}DbConfig;

typedef struct SDLConfig{

    
    struct SDLVideoConfig *video;
    
    
}SDLConfig;


typedef struct SDLVideoConfig{

    long unsigned windowFlag;

}SDLVideoConfig;




void initDbConfig(DbConfig *dbConfigElement, char ***arrayParameters);
void initSDLVideoConfig(SDLVideoConfig *videoConfigElement, char ***arrayParameters);
void deleteEndSpace(char **row);

#endif 