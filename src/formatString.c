#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <formatString.h>
#include <fileManager.h>


void deleteLineFeed( char **row ){

int sizeRow;

sizeRow=strlen(*row);
    if((*row)[sizeRow-1]=='\n' && (*row)[sizeRow-1]!=EOF ){
        (*row)[sizeRow-1]='\0';
    }
}

void deleteEndSpace(char **row ){

int counterChar;
int counterSpace=0;
int sizeRow;
sizeRow=strlen(*row);

    counterChar=sizeRow-1;

    while((*row)[counterChar-counterSpace]==' '){
        (*row)[counterChar-counterSpace]='\0';
        counterSpace++;
    }
}

void formatFullPath(char ** fullPathString){

    int sizeString;

    sizeString=strlen(*fullPathString);

    if(strchr(*fullPathString,':')!=NULL){

        if((*fullPathString)[sizeString-1]!='\\'){
            (*fullPathString)[sizeString]='\\';
            (*fullPathString)[sizeString+1]='\0';
        }
    }

    else{
        fprintf(stderr,"Le chemin %s n'est pas un chemin valide",*fullPathString);
    }
}

