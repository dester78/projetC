#ifndef FILERADER
#define FILEREADER
#include <structures.h>
#include <stdio.h>



FILE *openFile(char *fileName, char *openMode);
void initDbConfig(FILE *configFile,DbConfig *newDbConfig);
int *countFileRowChar(FILE *file, int *lastRow);
void deleteEndRow(char *row);



#endif