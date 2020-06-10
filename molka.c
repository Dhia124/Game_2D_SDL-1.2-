#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<string.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include"header.h"


void hero_movment(perso_hero *hero, SDL_Event ev, fond_ecran *x_background)
{

    switch (ev.type)
    {

    case SDL_KEYDOWN:
        switch (ev.key.keysym.sym)
        {

        case SDLK_RIGHT:
            
            hero->cord.x ++ ; 
            x_background->camera.x ++ ; 

            break;

        case SDLK_LEFT:

            hero->cord.x -- ; 
            x_background->camera.x -- ;
            
            break;

        case SDLK_UP:

            if ( hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;
                while (hero->initial_altitude.y - hero->cord.y < 150)
                {
                  
                    hero->cord.y -= 5;
                    hero->cord.x += 3;

                    x_background ->camera.x ++ ; 
                }
            }

            hero->first_entry_jump = 0;
            hero->cord_origin_axis.x = hero->cord.x + x_background->camera.x;

            break;
        }

        break;

    case SDL_KEYUP:

        switch (ev.key.keysym.sym)
        {
            break;

        case SDLK_UP:

            hero->first_entry_jump = 1;

            break;

        }

        break;
    }

}

