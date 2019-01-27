#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>

typedef struct File{

    char *fullName;
    char  openMode[4];
    FILE *filePointer;

}File;

typedef struct FileIndex{

    File *err;
    File *config;
    File *metroLineColor;

}FileIndex;


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
FileIndex * initFileIndex();



File *returnFileElement(char *fullName, char* openMode);

//Fonctions de liberation d'allocations de structures
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeFileIndex(FileIndex *fileIndex);
void freeFileElement(File *fileElement);

#endif 