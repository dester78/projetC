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

    if((fileIndex=initFileIndex())==NULL){
        createErrorReport("Erreur lors de la creation d'un index de fichier",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    if((fileIndex->err->filePointer=openFluxFile(fileIndex->err->fullName,fileIndex->err->openMode))==NULL){
        createErrorReport("Echec lors de la redirection de sortie d'erreur",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;            
    }    

    if((fileIndex->config->filePointer=openFile(fileIndex->config->fullName,fileIndex->config->openMode))==NULL){
        createErrorReport("Echec lors de l'ouverture d'un fichier de configuration",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;            
    }        
    
    if(returnConfigFileParameters(fileIndex->config->filePointer,&lastRow,&arrayParameters)==0){
        createErrorReport("Echec lors de la lecture des parametres d'un fichier de configuration",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
    }
    
    if(fclose(fileIndex->config->filePointer)==EOF){
        createErrorReport("Echec lors de la fermeture d'un fichier de configuration",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;     
    }
    fileIndex->config->filePointer=NULL;
    
    if(initDbConfig(&dbConfigElement,arrayParameters,lastRow)==-1){
        createErrorReport("Echec lors de l'initialisation de la configuration de base de donnee'",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
    }

    if(initSDLConfig(&SDLConfigElement,arrayParameters,lastRow)==0){
        createErrorReport("Echec lors de l'initialisation de la configuration SDL'",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
    }

    if(createMysqlConnection(&dbConfigElement,&dbConnection)==0){
        createErrorReport("Echec lors de la connexion a la base de donnee",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
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

        if((mainWindow=SDLCreateMainWindow(SDLConfigElement.window))==NULL){
            createErrorReport("Echec lors de la creation de la fenetre principale",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }

        if(initIMGConfig(SDLConfigElement.img,arrayParameters,lastRow,SDLConfigElement.window->windowWidth,SDLConfigElement.window->windowWidth)==0){
            createErrorReport("Echec lors de l'initialisation de la configuration d'image",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }


        if((mainRenderer=SDLCreateMainRenderer(mainWindow,SDLConfigElement.renderer->rendererFlag))==NULL){
            createErrorReport("Echec lors de la creation du moteur de rendu principal",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }

        SDLLoop=SDLMainMenuLoop(mainWindow,mainRenderer,&SDLConfigElement,&dbConfigElement,&dbConnection,fileIndex);
        SDL_DestroyWindow(mainWindow);
        SDL_DestroyRenderer(mainRenderer);  
    }
        

    
    freeDbConfigElement(&dbConfigElement);  
    freeSDLConfigElement(&SDLConfigElement);   
    freeFileIndex(fileIndex);

    free(fileIndex);

    freeCharArray(&arrayParameters,lastRow);
    mysql_close(&dbConnection);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    mysql_library_end();
  
    return 0;
}
