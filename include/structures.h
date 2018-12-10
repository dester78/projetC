#ifndef STRUCTURES
#define STRUCTURES

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
    char* playerLogin;
    char* playerPasswd;


}DbConfig;



//Fonctions d'initialisation de structures : 
int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );


Files *returnFileElement(char *fullName, char* openMode);

//Fonctions de liberation d'allocations de structures
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeFileElement(Files *fileElement);

#endif 