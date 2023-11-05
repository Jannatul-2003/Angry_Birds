#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
extern int SCREEN_WIDTH,SCREEN_HEIGHT;
extern SDL_Window *gWindow ;
enum keys
{
    loading_screen_1,
    loading_screen_2,
    main_menu_background,
    current_surface,
    total
};

extern SDL_Surface *surfaces[total], *gSurface, *gPNGSurface;
bool init();
bool loadMedia();
SDL_Surface *loadSurface(std::string path);
void close();
#endif

