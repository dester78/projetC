#ifndef SDLCONFIGSTRUCTURES
#define SDLCONFIGSTRUCTURES


typedef struct SDLConfig{

    
    struct SDLWindowConfig *window;
    struct SDLInitConfig *init;
    struct SDLRendererConfig *renderer;
    struct TTFConfig *ttf;

}SDLConfig;


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


int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters,int lastRow );
void initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow );



void freeSDLConfigElement(SDLConfig *SDLConfigElement );


#endif