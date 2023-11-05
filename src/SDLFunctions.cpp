#include "SDLFunctions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;
SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL, *gPNGSurface = NULL;
SDL_Surface *surfaces[total] = {NULL};


bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Angry Birds", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("SDL Window could not be created! SDL Error %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            int IMG_Flag = IMG_INIT_PNG, second = IMG_INIT_JPG;
            if (!(IMG_Init(IMG_Flag) & IMG_Flag))
            {
                printf("SDL Image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
                success = false;
            }
            else if (!(IMG_Init(second) & second))
            {
                printf("SDL JPG could not initialize! SDL Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                gSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}
bool loadMedia()
{
    bool success = true;

    surfaces[loading_screen_1] = loadSurface("images/Loading1.jpg");
    if (surfaces[loading_screen_1] == NULL)
    {
        printf("Failed to load loading screen 1!\n");
        success = false;
    }

    surfaces[loading_screen_2] = loadSurface("images/Loading2.jpg");
    if (surfaces[loading_screen_2] == NULL)
    {
        printf("Failed to load loading screen 2!\n");
        success = false;
    }

    surfaces[main_menu_background] = loadSurface("images/main_menu.jpg");
    if (surfaces[main_menu_background] == NULL)
    {
        printf("Failed to load image: Main menu!\n");
        success = false;
    }

    return success;
}

SDL_Surface *loadSurface(std::string path)
{
    SDL_Surface *normalSurface = IMG_Load(path.c_str()), *optimizedSurface = NULL;

    if (normalSurface == NULL)
    {
        printf("Unable to laod image %s. SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(normalSurface, gSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image%s. SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
        }

        SDL_FreeSurface(normalSurface);
    }

    return optimizedSurface;
}

void close()
{
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    for(int i = 0; i<total; i++)
    {
        SDL_FreeSurface(surfaces[i]);
        surfaces[i] = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}
