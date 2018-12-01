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
    SDL_Window* mainWindow;
    
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



//     int status =  EXIT_FAILURE;

//     SDL_Event event; 

//     MYSQL *mysql;
//     /* Initialisation bibliotheque mysql */
//     if (mysql_library_init(0, NULL, NULL) == 0)
//     {
//         /* Initialisation du pointeur MYSQL */
//         mysql = mysql_init(NULL);
//         if (mysql != NULL)
//         {
//             fprintf(stdout, "[OK] mysql_init\n");
 
//             /* Connexion au serveur mysql */
//             if (mysql_real_connect(mysql, "localhost", "root", "root", "sys", 0, NULL, 0) != NULL)
//             {
//                 fprintf(stdout, "[OK] mysql_real_connect\n");
//             }
//             else
//             {
//                 fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(mysql));
//             }
 
//             /* Fermeture de la connexion / Liberation memoire mysql */
//             mysql_close(mysql);
//             mysql = NULL;
//         }
//         else
//         {
//             perror("mysql_init");
//         }
 
//         /* Fermeture de la bibliotheque */
//         mysql_library_end();
//     }
//     else
//     {
//         fprintf(stderr, "[ERR] mysql_library_init\n");
//     }
 
     
//     // Initialisation + vérification de la SDL : VIDEO.
//     i
    
// quit:
//     // Quitter SDL.
//     SDL_Quit();
     
//     return status;