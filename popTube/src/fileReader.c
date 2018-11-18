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


void initDbConfig(FILE *configFile, DbConfig *newDbConfig){

    int lastRow;
    int *arrayRowChar;
    char *fileRow;
    char searchChar[2];

    arrayRowChar=countFileRowChar(configFile,&lastRow);

    for(int counterRow=0;counterRow<lastRow;counterRow++){

        fileRow=malloc(sizeof(char)*arrayRowChar[counterRow]);

        if(fileRow!=NULL){

            fgets(fileRow,arrayRowChar[counterRow],configFile);
            deleteEndRow(fileRow);
            strncpy(searchChar,fileRow,1);
    
            // if(strncmp(fileRow,"host=",strlen("host=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).host = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("host=")));
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
            // printf("%d %d %s",counterRow,arrayRowChar[counterRow],fileRow);
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

        while(bufferChar!=EOF){

            bufferChar=fgetc(file);
            counterChar++;

            if(bufferChar=='\n'||bufferChar==EOF){

                
                arrayRowChar=realloc(arrayRowChar,sizeof(int)*(counterRow+1));
                arrayRowChar[counterRow]=counterChar+1;
                counterRow++;
            }

        }
    }
    
    fseek(file,0,SEEK_SET);
    *lastRow=counterRow;
    
    return arrayRowChar;

}

void deleteEndRow(char *row){

char *bufferRow;
int sizeRow;

sizeRow=strlen(row);

    if(strcmp((row+strlen(row)-1),"\n")==0){

        bufferRow=malloc(sizeof(char)*(strlen(row)));
        strncpy(bufferRow,row,(sizeRow-1));
        printf("%d",sizeof(row));
        printf("%d",sizeof(bufferRow));
        free(row);
        (*row)=malloc(sizeof(char)*(sizeRow-1));
        // printf("%s",bufferRow);

        strcpy(row,bufferRow);
        printf("%s",row);
        free(bufferRow);
        
        

    }
    

}







