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
    short SDLLoop=0;
    char **arrayParameters;

    SDLConfig SDLConfigElement;
    DbConfig dbConfigElement;
    FileIndex *fileIndex;

    fileIndex=initFileIndex();

    
    // arrayFiles[0]=returnFileElement("errorLog.txt","a+");

    // printf("%d",)
    // arrayFiles[1].filePointer=malloc(sizeof(FILE*));

    //if((arrayFiles[0].filePointer=openFluxFile(arrayFiles[0].fullName,arrayFiles[0].openMode))!=NULL){
        
        if((fileIndex->config->filePointer=openFile(fileIndex->config->fullName,fileIndex->config->openMode))!=NULL){
            returnConfigFileParameters(fileIndex->config->filePointer,&lastRow,&arrayParameters); 
            fclose(fileIndex->config->filePointer);
            fileIndex->config->filePointer=NULL;
        }        

        else{
            printf("toto");
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
    if(TTF_Init()==-1) {
        fprintf(stderr,"Echec de l'initialisation de l'extension SDL_ttf (%s)\n",TTF_GetError());
        return 0;
    }

    if(IMG_Init(IMG_INIT_PNG)==0) {
        fprintf(stderr,"Echec de l'initialisation de l'extension SDL_Image (%s)\n",IMG_GetError());
        return 0;
    }

    while(SDLLoop!=-1){

        if((mainWindow=SDLCreateMainWindow(SDLConfigElement.window))!=NULL){

            initIMGConfig(SDLConfigElement.img,arrayParameters,lastRow,SDLConfigElement.window->windowWidth,SDLConfigElement.window->windowWidth);

            if((mainRenderer=SDLCreateMainRenderer(mainWindow,SDLConfigElement.renderer->rendererFlag))!=NULL){

                SDLLoop=SDLMainMenuLoop(mainWindow,mainRenderer,&SDLConfigElement,&dbConfigElement,&dbConnection,fileIndex);
                SDL_DestroyWindow(mainWindow);
                SDL_DestroyRenderer(mainRenderer);
            }
        }  
    }
        

    
    freeDbConfigElement(&dbConfigElement);  
    freeSDLConfigElement(&SDLConfigElement);   
    printf("avant free fileindex");

    freeFileIndex(fileIndex);
    printf("apre");
    
    // freeFileElement(arrayFiles[1]);
    // perror(createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__));
    free(fileIndex);
    freeCharArray(&arrayParameters,lastRow);
    mysql_close(&dbConnection);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    mysql_library_end();
  

    return 0;

}
