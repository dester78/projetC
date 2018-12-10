#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <errno.h>

#include <SDLConfigStructures.h>
#include <SDLObjects.h>
#include <SDLMain.h>
#include <structures.h>
#include <fileManager.h>
#include <dbManager.h>



#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <mysql.h>

int main(int argc, char **argv) {
     
    
    MYSQL dbConnection;
    SDL_Window  *mainWindow;
    SDL_Renderer *mainRenderer;
    
    int lastRow=0;
    char **arrayParameters;

    SDLConfig SDLConfigElement;
    DbConfig dbConfigElement;
    Files **arrayFiles;

    
    arrayFiles=malloc(sizeof(Files*));
  
    // arrayFiles[0]=returnFileElement("errorLog.txt","a+");
    arrayFiles[0]=returnFileElement("popTube.cfg","r+");
    // printf("%d",)
    // arrayFiles[1].filePointer=malloc(sizeof(FILE*));

    //if((arrayFiles[0].filePointer=openFluxFile(arrayFiles[0].fullName,arrayFiles[0].openMode))!=NULL){

        if((arrayFiles[0]->filePointer=openFile(arrayFiles[0]->fullName,arrayFiles[0]->openMode))!=NULL){
            returnFileParameters(arrayFiles[0]->filePointer,&lastRow,&arrayParameters); 

        }        

        else{
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;    
        }   
   // }

    if(initDbConfig(&dbConfigElement,arrayParameters,lastRow)!=-1){
        

        if(initSDLConfig(&SDLConfigElement,arrayParameters,lastRow)){

            if(createMysqlConnection(&dbConfigElement,&dbConnection)){
            
 
            }

            else{
                
            }
        }
    }

    
    

    if (SDL_Init( SDLConfigElement.init->initFlag ) != 0 ){
        fprintf(stderr,"Echec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return 0;
    }
    else if(TTF_Init()==-1) {
        fprintf(stderr,"Echec de l'initialisation de l'extension SDL_ttf (%s)\n",TTF_GetError());
        return 0;
    }
    else{
        if((mainWindow=SDLCreateMainWindow(SDLConfigElement.window))!=NULL){
            if((mainRenderer=SDLCreateMainRenderer(mainWindow,SDLConfigElement.renderer->rendererFlag))!=NULL){

                while(SDLMainMenuLoop(
                mainWindow,mainRenderer,
                &SDLConfigElement,
                &dbConfigElement,
                &dbConnection,
                arrayFiles) != 0){

                }
            }
        }  
    }
    
    freeDbConfigElement(&dbConfigElement);
    
    freeSDLConfigElement(&SDLConfigElement);
    
    freeFileElement(arrayFiles[0]);
    
    // freeFileElement(arrayFiles[1]);
    // perror(createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__));
    free(arrayFiles);
    freeCharArray(&arrayParameters,lastRow);
    mysql_close(&dbConnection);
    TTF_Quit();
    SDL_Quit();
    mysql_library_end();

  

    return 0;

}
