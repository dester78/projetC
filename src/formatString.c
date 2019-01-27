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

void extractWindowDimensionsFromString(char *string, int *dimension){

    char stringDimension[5];
    unsigned char  counterCharNumber=0;
    
    for(unsigned char counterChar=0; counterChar<strlen(string);counterChar++){

        if(string[counterChar]>=48&&string[counterChar]<=57){
            counterCharNumber++;
        }
        else if((string[counterChar]<48||string[counterChar]>57)&&counterCharNumber!=0){
            
            strncpy(stringDimension,string+(counterChar-counterCharNumber),counterCharNumber);
            stringDimension[4]='\0';

            counterCharNumber=0;

            if(dimension[0]==0){
                dimension[0]=atoi(stringDimension);//Stock la largeur
            }
            else{
                dimension[1]=atoi(stringDimension);//Stock la hauteur
            }
        }
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

