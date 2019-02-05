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

/*
 * ─── FONCTIONS D'INITIALISATION DE STRUCTURES ────────────────────────────────────
 */
//Initialisation de la structure de configuration de base de donnée    
short initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );

//Initialisation de la structure index de fichier
FileIndex * initFileIndex();

//Créer un élément fichier 
File *returnFileElement(char *fullName, char* openMode);

/*
 * ─── FONCTIONS DE LIBERATION D'ALLOCATION ────────────────────────────────────────
 */
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeFileIndex(FileIndex *fileIndex);
void freeFileElement(File *fileElement);

#endif 