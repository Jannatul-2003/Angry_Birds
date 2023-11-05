#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "SDLFunctions.h"

int main()
{

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to laod media!\n");
        }
        else
        {

            SDL_Rect stretch;
            stretch.x = 0;
            stretch.y = 0;
            stretch.h = SCREEN_HEIGHT;
            stretch.w = SCREEN_WIDTH;

            SDL_Rect opt;
            opt.x = 0;
            opt.y = 0;
            opt.h = 100;
            opt.w = 100;

            SDL_BlitScaled(surfaces[loading_screen_1], NULL, gSurface, &stretch);
            SDL_UpdateWindowSurface(gWindow);

            SDL_Event e;
            bool quit = false, LoadingScreen = true, AfterLoadingScreen = false;

            while (!quit)
            {

                while (SDL_PollEvent(&e))
                {

                    if (e.type == SDL_QUIT)
                        quit = true;
                    else if (e.type == SDL_KEYDOWN)
                    {
                        if (LoadingScreen && !AfterLoadingScreen)
                        {
                            if (e.key.keysym.sym == SDLK_RETURN)
                            {
                                SDL_BlitScaled(surfaces[loading_screen_2], NULL, gSurface, &stretch);
                            }
                        }
                        else
                        {
                            if (e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                quit = true;
                            }
                        }
                    }
                    else if (e.type == SDL_KEYUP)
                    {
                        if (e.key.keysym.sym == SDLK_RETURN)
                        {
                            LoadingScreen = false;
                            AfterLoadingScreen = true;
                            SDL_BlitScaled(surfaces[main_menu_background], NULL, gSurface, &stretch);
                        }
                    }
                }

                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}
