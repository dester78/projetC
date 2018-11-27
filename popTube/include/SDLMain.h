#ifndef SDLMAIN
#define SDLMAIN


    SDL_Window *SDLCreateMainWindow(SDLConfig *SDLConfigElement);
    SDL_Surface *SDLCreateHostMenu(SDL_Window* mainWindow);
    void SDLMainLoop(SDL_Window* mainWindow);
    void SDLGetDisplayModes(SDL_DisplayMode *displayMode);


#endif