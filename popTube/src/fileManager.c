#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileManager.h>
#include <string.h>


FILE *openFile(char *fileName, char *openMode){

    FILE *file;
    if(fileName!=NULL && openMode!=NULL){

        file=fopen(fileName,openMode);
        return file;
    }

    return NULL;

}


void returnFileParameters(FILE *configFile,int *arrayRowChar, char ***arrayParameters, int lastRow){

    char *fileRow; 
    int counterFileRow;
    char commentChar[2];
    int counterParameters=0;

    *arrayParameters=malloc(sizeof(char**));

    if(*arrayParameters!=NULL){

        for(counterFileRow=0;counterFileRow<lastRow;counterFileRow++){

            if(arrayRowChar[counterFileRow]>1){
                fileRow=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));

                if(fileRow!=NULL){

                fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);

                    deleteLineFeed(&fileRow);
                    strncpy(commentChar,fileRow,1);

                    if(commentChar[0]!='#'){
                        
                        deleteEndSpace(&fileRow);
                        *arrayParameters=realloc(*arrayParameters,(sizeof(char**)*(counterParameters+1)));

                        if(*arrayParameters!=NULL){

                            *(*arrayParameters+counterParameters)=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));

                            if(*(*arrayParameters+counterParameters)!=NULL){

                                strcpy(*(*arrayParameters+counterParameters),fileRow);
                                counterParameters++;
                            }
                        }                
                    }
                }
                free(fileRow);
            }

            else if((counterFileRow+1)<lastRow){
                fseek(configFile,arrayRowChar[counterFileRow]+1,SEEK_CUR);
            }
        }       
    }
    
    *(*arrayParameters+counterParameters)=malloc(sizeof(char)*2);

    if(*(*arrayParameters+counterParameters)!=NULL){

        *(*arrayParameters+counterParameters)="\0";
    }
}

int *countFileRowChar(FILE *file, int *lastRow){

    int counterRow=0; 
    int *arrayRowChar;
    char bufferChar;
    int counterChar=0;

    fseek(file,0,SEEK_SET);
    arrayRowChar=malloc(sizeof(int));
    
    if(arrayRowChar!=NULL){

        while(counterChar!=-1){

            bufferChar=fgetc(file);
            counterChar++;

            if(bufferChar=='\n'||bufferChar==EOF){

                arrayRowChar=realloc(arrayRowChar,sizeof(int)*(counterRow+1));
                arrayRowChar[counterRow]=counterChar;
                counterChar=0;

                if(bufferChar==EOF){
                    counterChar=-1;
                }
                counterRow++;
            }
        }
    }
    
    fseek(file,0,SEEK_SET);
    *lastRow=counterRow;
    
    return arrayRowChar;

}

void deleteLineFeed( char **row){

char *bufferRow;
int counterChar;
int sizeRow;

sizeRow=strlen(*row);

    if(*(*row+sizeRow-1)=='\n'){

        bufferRow=malloc(sizeof(char)*(sizeRow+1));
        strcpy(bufferRow,*row);

        free(row);
        *row=malloc(sizeof(char)*(sizeRow));

        for(counterChar=0;counterChar<sizeRow-1;counterChar++){
            *(*row+counterChar)=bufferRow[counterChar];
        }

        *(*row+counterChar)='\0';
        free(bufferRow);
    }
}

void deleteEndSpace(char **row){

char *bufferRow;
int counterChar;
int counterSpace=0;
int sizeRow;

sizeRow=strlen(*row);

    bufferRow=malloc(sizeof(char)*(sizeRow+1));
    strcpy(bufferRow,*row);
    free(row);
    
    if(bufferRow[sizeRow-1]==' '){
    
        counterChar=sizeRow-1;
        while(bufferRow[counterChar-counterSpace]==' '){
            counterSpace++;
        }
    }

    *row=malloc(sizeof(char)*(sizeRow-counterSpace));

    for(counterChar=0;counterChar<(sizeRow-counterSpace);counterChar++){
        *(*row+counterChar)=bufferRow[counterChar];
    }

    *(*row+counterChar)='\0';;
    free(bufferRow);
}







