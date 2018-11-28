#ifndef FILEMANAGER
#define FILEMANAGER
#include <structures.h>
#include <stdio.h>



FILE *openFile(char *fileName, char *openMode);
char **returnFileParameters(FILE *configFile,int *arrayRowChar, int *lastRow);
int *countFileRowChar(FILE *file, int *lastRow);
void deleteLineFeed( char **row);
void deleteEndSpace(char **row);

void freeArrayParameter(char** arrayParameter, int lastRow);



#endif