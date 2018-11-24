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

 
    // *arrayParameters=malloc(sizeof(char**));
    //  printf("%d",lastRow);

    // if(*arrayParameters!=NULL){

        for(counterFileRow=0;counterFileRow<lastRow;counterFileRow++){

            // printf("%d\n",arrayRowChar[counterFileRow]);
            printf("counter row%d\n",counterFileRow);
            printf("counterchar %d",arrayRowChar[counterFileRow]);
             

        
                fileRow=malloc(sizeof(char*)*(arrayRowChar[counterFileRow]+1));


                if(fileRow!=NULL){

                    printf("firstMalloc");

                fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);
                printf("row : %s",fileRow);
                   
                    strncpy(commentChar,fileRow,1);

                    if(commentChar[0]!='#'){
                        
                        printf("%d",counterParameters);
                        deleteLineFeed(&fileRow);
                        deleteEndSpace(&fileRow);
                        *arrayParameters=realloc(*arrayParameters,(sizeof(char**)*(counterParameters+1)));
                        // printf("%d",*arrayParameters);

                        if(*arrayParameters!=NULL){

                            printf("realoc");

                            *(*arrayParameters+counterParameters)=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));
                            
                            if(*(*arrayParameters+counterParameters)!=NULL){

                                printf("lastMalloc");
                                strcpy(*(*arrayParameters+counterParameters),fileRow);
                                // printf("%s",*(*arrayParameters+counterParameters));
                                
            
                            }

                            
                        }  

                        counterParameters++;              
                    }
                    free(fileRow);
                    printf("freeOK");
                }
                
                
           
        }       
    // }
    
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
            // printf("%c",bufferChar);
            counterChar++;

            if(bufferChar=='\n'||bufferChar==EOF){

                if(counterChar==1){
                    counterChar++;
                }

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
        if(bufferRow!=NULL){

            strcpy(bufferRow,*row);
            free(row);

            *row=malloc(sizeof(char)*(sizeRow));

            if(*row!=NULL){

                for(counterChar=0;counterChar<sizeRow-1;counterChar++){
                    *(*row+counterChar)=bufferRow[counterChar];
                }

            *(*row+counterChar)='\0';
            }

            
            free(bufferRow);

        }
    }
}

void deleteEndSpace(char **row){

char *bufferRow;
int counterChar;
int counterSpace=0;
int sizeRow;

sizeRow=strlen(*row);

    bufferRow=malloc(sizeof(char)*(sizeRow+1));
    
    
    if(bufferRow!=NULL){

        strcpy(bufferRow,*row);
        if(bufferRow[sizeRow-1]==' '){
    
            free(row);
            counterChar=sizeRow-1;
            while(bufferRow[counterChar-counterSpace]==' '){
                counterSpace++;
            }

            *row=malloc(sizeof(char)*(sizeRow-counterSpace));

            if(*row!=NULL){

                for(counterChar=0;counterChar<(sizeRow-counterSpace);counterChar++){

                    *(*row+counterChar)=bufferRow[counterChar];
                }

                *(*row+counterChar)='\0';
                
            }
        }

        free(bufferRow);
    }
    
    
}







