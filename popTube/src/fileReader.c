#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileReader.h>


FILE *openFile(char *fileName, char *openMode){

    FILE *file;
    if(fileName!=NULL && openMode!=NULL){

        file=fopen(fileName,openMode);
        return file;
    }

    return NULL;

}


void initDbConfig(FILE *configFile){

    int lastRow;
    int *arrayRowChar;
    char *fileRow;

    arrayRowChar=countFileRowChar(configFile,&lastRow);

    for(int counterRow=0;counterRow<lastRow;counterRow++){

        fileRow=malloc(sizeof(char)*arrayRowChar[counterRow]);

        if(fileRow!=NULL){
            fgets(fileRow,arrayRowChar[counterRow],configFile);
            printf("%d %d %s",counterRow,arrayRowChar[counterRow],fileRow);
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