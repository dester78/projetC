#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileReader.h>
#include <string.h>


FILE *openFile(char *fileName, char *openMode){

    FILE *file;
    if(fileName!=NULL && openMode!=NULL){

        file=fopen(fileName,openMode);
        return file;
    }

    return NULL;

}


void returnFileParamaters(FILE *configFile,int *arrayRowChar, int lastRow){

    char *fileRow; 
    int counterFileRow;
    char commentChar[2];
    int counterParameters=0;
    char **arrayParameters;
    
    arrayParameters=malloc(sizeof(char*));

    for(counterFileRow=0;counterFileRow<lastRow;counterFileRow++){

        fileRow=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));

        if(fileRow!=NULL){

            fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);
            deleteEndRow(&fileRow);
            strncpy(commentChar,fileRow,1);

            if(commentChar[0]!='#'){
                counterParameters++;
                *arrayParameters=realloc(*arrayParameters,sizeof(char*)*counterParameters);
                arrayParameters[counterParameters]=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));
                strcpy(arrayParameters[counterParameters],fileRow);
                printf("%s",arrayParameters[counterParameters]);
            }
            
    
            // if(strncmp(fileRow,"host=",strlen("host=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).host = malloc(sizeof(char) * (arrayRowChar[counterFileRow] - strlen("host=")));
            //     strcpy((*newDbConfig).host,(fileRow+strlen("host=")));

            // }

            // else if(strncmp(fileRow,"user=",strlen("user=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).user = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("user=")));
            //     strcpy((*newDbConfig).user,(fileRow+strlen("user=")));

            // }

            // else if(strncmp(fileRow,"passwd=",strlen("passwd=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).passwd = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("passwd=")));
            //     strcpy((*newDbConfig).passwd,(fileRow+strlen("passwd=")));

            // }

            // else if(strncmp(fileRow,"db=",strlen("db=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).db = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("db=")));
            //     strcpy((*newDbConfig).db,(fileRow+strlen("db=")));

            // }
            
            // printf("caractere : %c",searchChar[0]);
            // printf("%d : %d : %s",counterRow,arrayRowChar[counterRow],fileRow);
            //printf("<<<<<<<<<<nbchar:%d nbrow: %d row: %s sizeRow: %d :>>>>>>>>>>>",arrayRowChar[counterRow], counterRow, fileRow,strlen(fileRow));
            free(fileRow);
        
        }
        
    }

    free(arrayRowChar);
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

void deleteEndRow( char **row){

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









