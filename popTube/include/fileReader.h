#ifndef FILERADER
#define FILEREADER
#include <structures.h>
#include <stdio.h>



FILE *openFile(char *fileName, char *openMode);
void returnFileParamaters(FILE *configFile,int *arrayRowChar, int lastRow);
int *countFileRowChar(FILE *file, int *lastRow);
void deleteEndRow( char **row);



#endif