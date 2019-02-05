#ifndef SDLCONFIGSTRUCTURES
#define SDLCONFIGSTRUCTURES


typedef struct SDLWindowConfig{

    unsigned int windowFlag;
    int windowHeight;
    int windowWidth;

}SDLWindowConfig;

typedef struct SDLInitConfig{

    unsigned int initFlag;

}SDLInitConfig;

typedef struct SDLRendererConfig{

    unsigned int rendererFlag;

}SDLRendererConfig;

typedef struct TTFConfig{

    char *fontDirectory;
    char *fontMenu;

}TTFConfig;

typedef struct IMGConfig{

    char *IMGDirectory;
    char *parisMap;
    
}IMGConfig;


typedef struct SDLConfig{

    
    SDLWindowConfig *window;
    SDLInitConfig *init;
    SDLRendererConfig *renderer;
    TTFConfig *ttf;
    IMGConfig *img;
     

}SDLConfig;

/*
 * ─── FONCTIONS D'INITIALISATION DE STRUCTURES ────────────────────────────────────
 */

//Initialise la structure de configuration globale utilisé pour la librairie SDL
short initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );

//Initialise la structure de configuration dédiée aux fenêtres générées par la SDL
short initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );

//Initialise la structure de configuration dédiée aux options de lancement de la bibliothèque SDL
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );

//Iitialise la structure de configuration dédiée au moteur de rendu
void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters,int lastRow );

//Initialise la structure de configuration dédiée à la bibliothèque SDL_TTF
short initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow );

//Initialise la structure de configuration dédiée à l'utilisation d'images
short initIMGConfig(IMGConfig *IMGConfigElement, char **arrayParameters,int lastRow , int windowWidth, int windowHeight);


/*
 * ─── FONCTIONS DE LIBERATION D'ALLOCATION ────────────────────────────────────
 */

//Libère la structure de configuration global et ses enfants
void freeSDLConfigElement(SDLConfig *SDLConfigElement );


#endif