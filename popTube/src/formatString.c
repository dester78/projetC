#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <formatString.h>
#include <fileManager.h>


void deleteLineFeed( char **row ){

char *bufferRow;
int counterChar;
int sizeRow;

sizeRow=strlen(*row);

    if(*(*row+sizeRow-1)=='\n'&& *(*row+sizeRow)!=EOF){

        if((bufferRow=malloc(sizeof(char)*(sizeRow+1)))!=NULL){

            strcpy(bufferRow,*row);
            free(*row);

            if((*row=malloc(sizeof(char)*(sizeRow)))!=NULL){

                for(counterChar=0;counterChar<sizeRow-1;counterChar++){
                    *(*row+counterChar)=bufferRow[counterChar];
                }
                *(*row+counterChar)='\0';
            }

            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
            
            free(bufferRow);
            bufferRow=NULL;
        }
        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
    }
}

void deleteEndSpace(char **row ){

char *bufferRow;
int counterChar;
int counterSpace=0;
int sizeRow;

sizeRow=strlen(*row);
    
    if((bufferRow=malloc(sizeof(char)*(sizeRow+1)))!=NULL){

        strcpy(bufferRow,*row);
        free(*row);
        counterChar=sizeRow-1;
        while(bufferRow[counterChar-counterSpace]==' '){
            counterSpace++;
        }

        if((*row=malloc(sizeof(char)*(sizeRow-counterSpace)))!=NULL){

            for(counterChar=0;counterChar<(sizeRow-counterSpace);counterChar++){

                *(*row+counterChar)=bufferRow[counterChar];
            }
            *(*row+counterChar)='\0';
        }

        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}

        free(bufferRow);
        bufferRow=NULL;
    }
    else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
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

