#ifndef FILERADER
#define FILEREADER
#include <structures.h>
#include <stdio.h>



FILE *openFile(char *fileName, char *openMode);
void returnFileParameters(FILE *configFile,int *arrayRowChar, char ***arrayParameters, int lastRow);
int *countFileRowChar(FILE *file, int *lastRow);
void deleteEndRow( char **row);



#endif