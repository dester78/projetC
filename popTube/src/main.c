#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <errno.h>

#include <fileManager.h>
#include <structures.h> 
#include <dbManager.h>
#include <SDLMain.h>


#include <SDL.h>
// #include <SDL_ttf.h>
#include <mysql.h>

int main(int argc, char **argv) {
     
    
    MYSQL dbConnection;
    SDL_Window  *mainWindow;
    
    int lastRow;
    int *arrayRowChar;
    char **arrayParameters;

    SDLConfig SDLConfigElement;
    DbConfig dbConfigElement;
    Files *arrayFiles;

    
    arrayFiles=malloc(sizeof(Files));
  
    arrayFiles[0]=returnFileElement("errorLog.txt","a+");
    arrayFiles[1]=returnFileElement("popTube.cfg","r+");
    arrayFiles[0].filePointer=malloc(sizeof(FILE*));
    arrayFiles[1].filePointer=malloc(sizeof(FILE*));

    if((arrayFiles[0].filePointer=openFluxFile(arrayFiles[0].fullName,arrayFiles[0].openMode))!=NULL){

        if((arrayFiles[1].filePointer=openFile(arrayFiles[1].fullName,arrayFiles[1].openMode))!=NULL){

            arrayRowChar=countFileRowChar(arrayFiles[1].filePointer,&lastRow);
            arrayParameters=returnFileParameters(arrayFiles[1].filePointer,arrayRowChar ,&lastRow); 
        }        

        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}   
    }

         
    if(initDbConfig(&dbConfigElement,arrayParameters,lastRow)){

        if(initSDLConfig(&SDLConfigElement,arrayParameters,lastRow)){

            if(createMysqlConnection(&dbConfigElement,&dbConnection)){
            
 
            }

            else{
                
            }
        }
    }
    

    if (SDL_Init( SDLConfigElement.init->initFlag ) != 0 ){

        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
    }

    else{

        if((mainWindow=SDLCreateMainWindow(SDLConfigElement.window->windowFlag))!=NULL){

            while(SDLMainLoop(
                mainWindow,
                &SDLConfigElement,
                &dbConfigElement,
                &dbConnection,
                arrayFiles) != 0){

                }
   
        }  
    }

    freeDbConfigElement(&dbConfigElement);
    freeSDLConfigElement(&SDLConfigElement);
    freeFileElement(arrayFiles[0]);
    // freeFileElement(arrayFiles[1]);
    // perror(createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__));
    free(arrayFiles);
    freeArrayParameter(arrayParameters,lastRow);
    
    free(arrayParameters);


    mysql_close(&dbConnection);
    SDL_Quit();
    mysql_library_end();

    return 0;

}
