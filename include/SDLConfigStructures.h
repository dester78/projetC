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


int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters,int lastRow );
void initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow );
void initIMGConfig(IMGConfig *IMGConfigElement, char **arrayParameters,int lastRow , int windowWidth, int windowHeight);



void freeSDLConfigElement(SDLConfig *SDLConfigElement );


#endif