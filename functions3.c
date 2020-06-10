/**
* @file functions3.c
* @author Gurzil Team
* @date jun 06, 2020
* @version 1.2
*/



#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_rotozoom.h>
#include <string.h>
#include "header.h"

// character movments
/**
* @brief To animate our hero .
* @param hero   Our hero
* @return Nothing
*/
void animation_hero(perso_hero *hero)
{
    if (hero->mvt == 1) // mvt to the right
    {
        hero->frame.x = 150;
        hero->frame.w = 150;
        hero->frame.h = 150;
        hero->frame.y = 0;
        if (hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
            //hero->mvt=0;
        }

        hero->frame.x = 0;

        hero->coeff_sprite++;
    }

    if (hero->mvt == 2) // mvt left
    {
        hero->frame.x = 150;
        hero->frame.y = 150 * 3;
        hero->frame.h = 150;
        hero->frame.w = 150;

        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
            //hero->mvt=0;
        }

        hero->frame.x = 0;

        hero->coeff_sprite++;
    }

    if (hero->mvt == 3 && hero->direction == 1) //mvt up right
    {
        hero->frame.x = 0;
        hero->frame.y = 300;
        hero->frame.w = 150;
        hero->frame.h = 150;

        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
            // hero->mvt=0;
        }

        hero->frame.x = 0;
        hero->coeff_sprite++;
    }

    if (hero->mvt == 3 && hero->direction == 0) //mvt up left
    {
        hero->frame.x = 0;
        hero->frame.y = 600;
        hero->frame.w = 150;
        hero->frame.h = 150;

        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
            // hero->mvt=0;
        }

        hero->frame.x = 0;
        hero->coeff_sprite++;
    }

    if (hero->mvt == 4 && hero->direction == 1) // mvt down
    {
        hero->frame.x = 150;
        hero->frame.y = 300;
        hero->frame.w = 150;
        hero->frame.h = 150;
        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
        }
    }

    if (hero->mvt == 4 && hero->direction == 0) // mvt down left
    {
        hero->frame.x = 150;
        hero->frame.y = 600;
        hero->frame.w = 150;
        hero->frame.h = 150;
        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
        }
    }

    if (hero->mvt == 0) // mvt stand still
    {
        hero->frame.x = 150;
        hero->frame.y = 150;
        hero->frame.w = 150;
        hero->frame.h = 150;

        if (hero->coeff_sprite == 4 || hero->coeff_sprite == 2)
        {
            hero->coeff_sprite = 0;
            hero->mvt = 0;
        }

        hero->frame.x = 150 * hero->coeff_sprite;

        hero->coeff_sprite++;
    }
}
/**
* @brief to do a collision with our ennemy .
* @param hero  Our hero
* @param ennemy Our  ennemy
* @return Nothing
*/
void collision_ennemy(perso_hero *hero, entite_secondaire *ennemy,fond_ecran *x_background)
{

    //limite_time = initial_time + 10000;

    if (hero->cord.x + hero->cord.w < ennemy->cord.x || hero->cord.x > ennemy->cord.x + ennemy->cord.w || hero->cord.y + hero->cord.h < ennemy->cord.y || hero->cord.y > ennemy->cord.y + ennemy->cord.h)
    {
        hero->collision_state = 3;
        hero->touch = 0;
    }
    else

    {
        if (hero->heart_image_frame.y != 300 && hero->touch == 0)
        {
            if (x_background->camera.x - 100 < 0 )
            {
                x_background->camera.x = 0 ;
            }
            else
            {
                x_background->camera.x -=100 ; 
            }
            
            
            hero->heart_image_frame.y += 75;
            hero->touch = 1;
            //printf("3ejja space\n");
            hero->cord.x-=100 ; 
            hero->cord.y+=50 ;
            hero->cord_mini_perso.x-=5 ;
            hero->cord_mini_perso.y+=7 ; 
            hero->cord.y+=50 ;

        }

        else if (hero->heart_image_frame.y == 300)
        {

            hero->death = 1;
        }
    }
}
/**
* @brief to do a collision with a coin .
* @param hero  Our hero
* @param tab1 Our  coin
* @return 0 ou 1 
*/
int collision_coin(perso_hero *hero, coin *tab1)
{
 
    //if (hero->cord.x+65==tab1->cord.x&&hero->cord.y+65==tab1->cord.y+65){
    // if ( hero->cord.x<tab1->cord.x || hero->cord.x > tab1->cord.x || hero->cord.y  < tab1->cord.y || hero->cord.y > tab1->cord.y   )
    if (hero->cord.x + hero->cord.w < tab1->cord_coin.x - 60 || hero->cord.x > tab1->cord_coin.x || hero->cord.y + hero->cord.h < tab1->cord_coin.y - 60 || hero->cord.y > tab1->cord_coin.y)

    {

        return 0;
    }
    else
    {

        if (tab1->stop == 0)
        {
            tab1->stop = 1;
             hero->score+=100;
            printf("%d\n",hero->score) ;
            return 1;
        }
        return 1;
    }
}
/**
* @brief to do a collision with an attack .
* @param hero  Our hero
* @param ennemy Our  ennemy
* @return Nothing
*/
void collision_attack(perso_hero *hero, entite_secondaire *ennemy)
{

    if ((!(hero->ball_cord.x + hero->ball_cord.w < ennemy->cord.x || hero->ball_cord.x > ennemy->cord.x + ennemy->cord.w)) && ((hero->ball_cord.y > ennemy->cord.y + ennemy->cord.h)))
    {

        hero->attack_state == 0;
        hero->coin = 1;
        ennemy->death = 1;
        //ennemy->health-=10;

        //printf("ennemy health : %d \n ",ennemy->health);
    }
}
/**
* @brief mouvement aleatoire d'entité secondaire .
* @param ent  Notre entité secondaire 
* @param X_min la borne inferieure
*@param X_max la borne superieur 
* @return Nothing
*/
void mvt_alea_entite_secondaire(entite_secondaire *ent, int X_min, int X_max)
{
    //ent->direction=1;
    /*int first_function_entry=1;
        int camera = 700 - X_max ; 
        
        ent->num = (rand() % (X_max - X_min + 1)) + X_min;
        ent->cord.x = ent->num - camera ; 
        if (first_function_entry==1 && ent->direction==1)
        {
            ent->direction=0;
        }
        else if (first_function_entry==1 && ent->direction==0)
        {
            ent->direction=1;
        }
        */

    if (ent->cord.x < X_max && ent->direction == 1)
    {
        ent->cord.x += 2;

        if (ent->cord.x == X_max)
        {
            ent->direction = 0;
        }
    }
    if (ent->cord.x > X_min && ent->direction == 0)
    {
        ent->cord.x -= 2;

        if (ent->cord.x == X_min)
        {
            ent->direction = 1;
        }
    }
}
/**
* @brief bliter notre mini map.
*@param position  la position du mini map 
* @return Nothing
*/
void blit_mini_map(SDL_Surface *screen, SDL_Surface *mini_perso, posf *position)
{
    SDL_Rect pos_mini;
    pos_mini.x = (int)position->x;
    pos_mini.y = (int)position->y;
    SDL_BlitSurface(mini_perso, NULL, screen, &pos_mini);

    SDL_Flip(screen);
}
/**
* @brief mouvement hero .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void hero_movment(perso_hero *hero, SDL_Event ev, fond_ecran *x_background, SDL_Surface *x_screen, entite_secondaire tab[], hajra tab_hajar[], coin tab_coin[])
{
    int destination = ev.motion.x;
    switch (ev.type)
    {

    case SDL_KEYDOWN:
        switch (ev.key.keysym.sym)
        {

        /*
        case SDLK_m : 

            if(hero->zoom < 2)
            {
                hero->zoom +=0.1 ; 
                
            }
            break ; 
        
        case SDLK_p : 
            
            if (hero->zoom > 0)
            {
                hero->zoom -=0.1 ; 
            }


            break ; 
        */

        case SDLK_SPACE:
            hero->acc += 0.1;

            if (hero->direction == 1)
            {
                hero->mvt = 1;
            }
            else
            {
                hero->mvt = 2;
            }

            break;

        case SDLK_RIGHT:
            //x_background->camera.x ++ ;
            if (x_background->camera.x + 1000 > 2740)
            {
                hero->cord.x += 1;
                hero->cord_mini_perso.x += 0.1;
            }
            else if (hero->cord.x < 400)
            {
                hero->cord.x++;
                hero->cord_mini_perso.x += 0.1;
            }

            else
            {
                x_background->camera.x += 2;
                hero->cord.x += 2;
                hero->cord_mini_perso.x += 0.15;
            }

            hero->direction = 1;

            hero->mvt = 1;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera.x;

            break;

        case SDLK_r:

            if (hero->attack_state == 0)
            {
                hero->attack = 1;
                hero->attack_state = 1;
            }

            break;

        case SDLK_LEFT:

            if (x_background->camera.x < 0)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else if (hero->cord.x - x_background->camera.x > 500)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else
            {
                x_background->camera.x -= 2;
                hero->cord.x -= 2;
                hero->cord_mini_perso.x -= 0.15;
                //printf("wassila \n");
            }

            hero->direction = 0;
            hero->mvt = 2;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera.x;

            break;

        case SDLK_UP:

            if (hero->direction == 1 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;
                while (hero->initial_altitude.y - hero->cord.y < 150)
                {

                    if (x_background->camera.x + 1000 > 2740)
                    {
                        hero->cord.x += 1;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else if (hero->cord.x < 400)
                    {
                        hero->cord.x++;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else
                    {
                        x_background->camera.x += 3;
                    }
                    //x_background->camera.x +=5;
                    //hero->cord.x +=5;
                    hero->cord.y -= 5;
                    hero->cord_mini_perso.y -= 0.3;
                    hero->mvt = 3;
                    hero->cord.x += 3;
                    hero->cord_mini_perso.x += 0.2;

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
                }
            }

            if (hero->direction == 0 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;

                while (hero->initial_altitude.y - hero->cord.y < 150)
                {
                    if (x_background->camera.x < 0)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else if (hero->cord.x > 500)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else
                    {
                        x_background->camera.x -= 2;
                    }
                    hero->cord_mini_perso.y -= 0.3;

                    hero->cord_mini_perso.x -= 0.2;
                    //x_background->camera.x -=5;
                    //hero->cord.x -=7;
                    hero->cord.y -= 9;
                    hero->cord.x -= 3;
                    hero->mvt = 3;
                    //rocks_fall (&hajjoura );

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
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

        


        case SDLK_ESCAPE:

            hero->pause = 1;
            hero->key_press_up_down = 0;

            break;

        

        case SDLK_SPACE:
            if (hero->speed > 0)
            {
                hero->acc -= 0.1;
            }

            break;

        case SDLK_UP:

            hero->first_entry_jump = 1;

            break;

        case SDLK_r:

            hero->attack_state = 0;

            break;

        case SDLK_RIGHT:

            break;

        case SDLK_LEFT:

            break;
        }

        break;

    case SDL_MOUSEBUTTONDOWN : 

        if (ev.motion.x > hero->cord.x )
        {
            hero->mvt = 1 ; 
            hero->direction = 1 ;
            if (hero->cord.x < destination ) 
            {
                if (x_background->camera.x + 1000 > 2740)
                {
                    hero->cord.x += 1;
                    hero->cord_mini_perso.x += 0.1;
                }
                else if (hero->cord.x < 400)
                {
                    hero->cord.x++;
                    hero->cord_mini_perso.x += 0.1;
                }

                else
                {
                    x_background->camera.x += 2;
                    hero->cord.x += 2;
                    hero->cord_mini_perso.x += 0.15;
                }
            }

        }

        if (ev.motion.x < hero->cord.x )
        {

            hero->mvt = 2 ; 
            hero->direction = 0 ; 
            if (hero->cord.x > destination ) 
            {
                if (x_background->camera.x < 0)
                {
                    hero->cord.x--;
                    hero->cord_mini_perso.x -= 0.1;
                }

                else if (hero->cord.x - x_background->camera.x > 500)
                {
                    hero->cord.x--;
                    hero->cord_mini_perso.x -= 0.1;
                }

                else
                {
                    x_background->camera.x -= 2;
                    hero->cord.x -= 2;
                    hero->cord_mini_perso.x -= 0.15;
                    //printf("wassila \n");
                }
            }

        }
        
        



        break ; 






    }

    hero->cord_origin_axis.x = x_background->camera.x + hero->cord.x;
}
/**
* @brief hero attack .
* @param hero  Notre hero
* @return Nothing
*/
void hero_attack(perso_hero *hero)
{
    //hero->cord_origin_axis
    if (hero->attack == 1)
    {

        hero->ball_cord.x = hero->cord.x + hero->cord.w;
        hero->ball_cord.y = hero->cord.y + 20;
        hero->attack = 0;
    }

    if (hero->attack_state == 1)
    {
        hero->ball_cord.x += 10;
    }
}
/**
* @brief animation for our ennemy.
*@param ennemy  Our ennemy
* @return Nothing
*/
void animation_entite_sec(entite_secondaire *ennemy)
{
    if (ennemy->direction == 1) // mvt to the right
    {
        ennemy->frame.x = 0;
        ennemy->frame.w = 150;
        ennemy->frame.h = 120;
        ennemy->frame.y = 0;
        if (ennemy->coef == 4)
        {
            ennemy->coef = 0;
            //hero->mvt=0;
        }

        ennemy->frame.x = ennemy->coef * 300;

        ennemy->coef++;
    }

    if (ennemy->direction == 0) // mvt to the right
    {
        ennemy->frame.x = 0;
        ennemy->frame.w = 150;
        ennemy->frame.h = 120;
        ennemy->frame.y = 150;
        if (ennemy->coef == 4)
        {
            ennemy->coef = 0;
            //hero->mvt=0;
        }

        ennemy->frame.x = ennemy->coef * 300;

        ennemy->coef++;
    }
}

/*
    void animation_coin(entite_secondaire *coin)
    {
        
            coin->frame.x=0;
            coin->frame.w=50;
            coin->frame.h=50;
            coin->frame.y=0;
            if (coin->coef==6)
            {
                coin->coef=0;
                //hero->mvt=0;
            }

            coin->frame.x=coin->coef *70 ; 
        
            coin->coef++;
    }
*/
/**
* @brief rock fall.
* @param x  Our rock
* @return Nothing
*/
void rocks_fall(hajra *x)
{
    if (x->fall_state == 1)
    {
        x->cord.y += 5;

        if (x->cord.y == 400)
        {
            x->cord.y = 0;
            x->fall_state = 0;
        }
    }
}
/**
* @brief collision hajjoura.
* @param hero  Notre hero
* @param X_backgound our background
*@param hajjoura  Our Rock
* @return Nothing
*/
void collision_hajjoura(perso_hero *hero, hajra *hajjoura, fond_ecran *x_background)
{
    int initial_time;
    int limite_time, current_time;

    // ( hero->cord_origin_axis.x+ hero->cord_origin_axis.w < ennemy->cord.x || hero->cord_origin_axis.x > ennemy->cord.x + ennemy->cord.w || hero->cord_origin_axis.y + hero->cord_origin_axis.h < ennemy->cord.y || hero->cord_origin_axis.y > ennemy->cord.y + ennemy->cord.h )

    if (hero->cord.x + hero->cord.w < hajjoura->cord.x - 60 || hero->cord.x > hajjoura->cord.x + hajjoura->cord.w || hero->cord.y + hero->cord.h < hajjoura->cord.y || hero->cord.y > hajjoura->cord.y + hajjoura->cord.h)
    //if ( hero->cord.x < hajjoura->cord.x || hero->cord.x > hajjoura->cord.x + hajjoura->cord.w || hero->cord.y + hero->cord.h < hajjoura->cord.y || hero->cord.y > hajjoura->cord.y + hajjoura->cord.h )
    {

        hero->collision_state = 3;
        hero->touch = 0;
        //printf("fammech  mass \n");
    }
    else

    {

        if (hero->heart_image_frame.y != 300 && hero->touch == 0)
        {
            hero->heart_image_frame.y += 75;
            hero->touch = 1;
            printf("3ejja \n");
            //SDL_Delay(500);
            //printf("%d  \n",hero->health);

            hero->cord.x -= 100;
            hero->cord_mini_perso.x -= 10;
            int diff = x_background->camera.x - 100;

            if (diff > 20)
            {
                x_background->camera.x = diff;
            }
            else
            {
                x_background->camera.x = 20;
            }
        }
        else if (hero->heart_image_frame.y == 300)
        {
            hero->death = 1;
        }

        //printf("famma mass \n");
    }
}
/**
* @brief everything .
* @param hero  Notre hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void everything(perso_hero *hero, SDL_Event ev, fond_ecran *background, SDL_Surface *screen, entite_secondaire tab[], hajra hajjoura[], SDL_Surface *black_background, coin tab_coin[])
{

   rocks_fall(&hajjoura[0]) ;
   collision_hajjoura(hero ,&hajjoura[0],background) ; 
   
   rocks_fall(&hajjoura[2]) ;
   collision_hajjoura(hero ,&hajjoura[2],background) ;

   rocks_fall(&hajjoura[1]) ;
   collision_hajjoura(hero ,&hajjoura[1],background) ;

    control_gestion_vie_score(hero, background);
    //hero_movment2(hero ,  ev);

    hero_movment(hero, ev, background, screen, tab, hajjoura, tab_coin);
    
    if (collision_coin(hero, &tab_coin[0]) == 1)
    {
        tab_coin[0].cycy = 10;
    }

    if (collision_coin(hero, &tab_coin[1]) == 1)
    {
        tab_coin[1].cycy = 10;
    }
    collision_surface(black_background, hero);
    hero_attack(hero);

    collision_tah(hero, background->backk, &background->camera);



    if (hero->speed > 0)
    {
        hero->acc = -0.001;
    }
    if (hero->speed < 0)
    {
        hero->acc = 0;
        hero->speed = 0;
    }
    hero_speed(hero, &background->camera, background->camera.x, background->dt);
   // hero_speed(hero,background->backk,background->camera.x,background->dt);

    //printf("%d  \n",hajjoura[0].cord.y );

    if (hero->cord.x < 600)
    {
        //hero_attack(hero );
        collision_ennemy(hero, &tab[0], background);
        mvt_alea_entite_secondaire(&tab[0], 200, 500);
        
    
        //collision_attack(hero, &tab[0]);
    }

    else if (hero->cord.x > 600 && hero->cord.x < 1000)
    {
        collision_ennemy(hero, &tab[1],background);
        mvt_alea_entite_secondaire(&tab[1], 700, 1000);
        
     
        collision_attack(hero, &tab[1]);
    }

    else if (hero->cord.x > 1300 && hero->cord.x < 1700)
    {
        collision_ennemy(hero, &tab[2],background);
        mvt_alea_entite_secondaire(&tab[2], 1400, 1700);
        

        collision_attack(hero, &tab[2]);
    }

    if (SDL_GetTicks() % 300 == 0)
    {
        hajjoura[0].fall_state = 1;
        hajjoura[1].fall_state = 1;
        hajjoura[2].fall_state = 1;
    }
     
    


}
/**
* @brief gestion vie et score .
* @param hero  Notre hero
* @param backgound our background
* @return Nothing
*/
void control_gestion_vie_score(perso_hero *hero, fond_ecran *background)
{
    if (hero->death == 1)
    {
        hero->heart_image_frame.y = 0;
        if (hero->score>=100) {
        hero->score -= 100;
        }
        background->camera.x = 0;
        hero->cord.x = 0;
        hero->cord.y = 0;
        hero->death = 0;
        hero->cord_origin_axis.x = 0;
        hero->cord_mini_perso.x=290; 
        hero->cord_mini_perso.y=465; 
    }
}
/**
* @brief speed hero .
* @param hero  Notre hero
* @param camera our camera
*@param dt   notre delta
* @return Nothing
*/
void hero_speed(perso_hero *hero, SDL_Rect *x_camera, int camera, double dt)
{
    hero->speed += 0.5 * hero->acc * dt;
              //  printf("%f \n",dt) ;
    
    if (hero->direction == 1)
    {
        if (camera < 1700)
        {
            x_camera->x += hero->speed * dt;
        }
        if (hero->cord.x < 2500)
        {
            hero->cord.x += hero->speed * dt;
            hero->cord_mini_perso.x += hero->speed * dt * 0.071;
        }
    }

    else
    {
        if (camera > 20)
        {
            x_camera->x -= hero->speed * dt;
        }

        if (hero->cord.x > 20)
        {
            hero->cord.x -= hero->speed * dt;
            hero->cord_mini_perso.x -= hero->speed * dt * 0.07;
        }
    }
}

//

//collisions
/**
* @brief collision tah .
* @param hero  Notre hero
* @return Nothing
*/
void collision_tah(perso_hero *hero, SDL_Surface *x_background, SDL_Rect *camera)
{
    if (hero->cord.y > 350)
    {   hero->heart_image_frame.y += 75;
        hero->cord.x = hero->cord.x - 100;
        camera->x -= 100;
        hero->cord.y = 0;
        hero->cord_mini_perso.x -= 5;
        hero->cord_mini_perso.y = 464;
        if (camera->x - 100 < 0 )
            {
                camera->x = 0 ;
            }
            else
            {
                camera->x -=100 ; 
            }
        //hero->health_ejja = hero->health_ejja - 1;
    }
}
/**
* @brief collision surface 2 .
* @param hero  Notre hero
*@param balck_background  our surface
* @return Nothing
*/
void collision_surface2(SDL_Surface *black_background, perso_hero *hero)
{

    SDL_Color x = GetPixel(black_background, hero->cord.x + 60 - 500, hero->cord.y + 150);

    //y=GetPixel(black_background,ev.motion.x,ev.motion.y);

    if (!(x.b == 0 && x.g == 0 && x.r == 0))
    {

        hero->cord.y += 5;
        hero->cord_mini_perso.y += 0.9;

        hero->mvt = 4;

        hero->first_entry_jump = 0;
    }
}
/**
* @brief collision surface  .
* @param hero  Notre hero
*@param balck_background  our surface
* @return Nothing
*/
void collision_surface(SDL_Surface *black_background, perso_hero *hero)
{

    SDL_Color x = GetPixel(black_background, hero->cord.x + 60, hero->cord.y + 150);

    //y=GetPixel(black_background,ev.motion.x,ev.motion.y);

    if (!(x.b == 0 && x.g == 0 && x.r == 0))
    {

        hero->cord.y += 5;
        hero->cord_mini_perso.y += 0.3;
        hero->mvt = 4;

        hero->first_entry_jump = 0;
    }
}
/**
* @brief GetPixel .
* @param x  position.x
*@param y position.y
*@param x_background  our surface
* @return color
*/
SDL_Color GetPixel(SDL_Surface *x_background, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    //Determine position
    char *pPosition = (char *)x_background->pixels;
    pPosition += (x_background->pitch * (y));
    pPosition += (x_background->format->BytesPerPixel * (x));
    memcpy(&col, pPosition, x_background->format->BytesPerPixel);
    //convertir color
    SDL_GetRGB(col, x_background->format, &color.r, &color.g, &color.b);
    return (color);
}

//

// save
/**
* @brief save hero.
* @param hero  Notre hero
*@param file_name[]  our save file
* @return Nothing
*/
    void save_hero(perso_hero *hero , char file_name[])
    {
        FILE *fp = NULL ; 
        
        fp = fopen(file_name,"wb");
        
        
        fwrite(hero, sizeof( perso_hero), 10, fp);

        
       fclose(fp);



    }
/**
* @brief save background .
* @param y  Notre backgound
*@param file_name[]  our save file
* @return Nothing
*/
    void save_back(fond_ecran *y,char file_name[])
    {
        FILE *fp = NULL ; 
        
        fp = fopen(file_name,"wb");
        
        
        fwrite(y, sizeof(fond_ecran ), 10, fp);
             
        
        fclose(fp);

    }
/**
* @brief load background .
* @param y  Notre background
*@param file_name[]  our load file
* @return Nothing
*/
    void load_back(fond_ecran *y, char file_name[])
    {
        FILE *fp = NULL ; 
        
        fp = fopen(file_name,"rb");
        
        fread(y, sizeof(fond_ecran ), 10, fp);
             
        fclose(fp);

    }
   /**
* @brief load hero.
* @param hero  Notre hero
*@param file_name[]  our save file
* @return Nothing
*/
    void load_hero(perso_hero *hero ,char file_name[])
    {
        FILE *fp = NULL ; 

        fp= fopen(file_name,"rb");


                
        fread(hero, sizeof( perso_hero), 10, fp);
        
        //fread(&y, sizeof( fond_ecran), 10, fp);
        
        fclose(fp);

    }
/**
* @brief save all.
* @param hero  Notre hero
*@param y our background
* @return Nothing
*/
    void save_all (perso_hero *hero, fond_ecran *y)
    {
        save_back(y,"back.bin");
        save_hero(hero , "hero.bin");
    }
/**
* @brief load all.
* @param hero  Notre hero
*@param y our background
* @return Nothing
*/
    void load_all (perso_hero *hero, fond_ecran *y)
    {

        load_back(y,"back.bin");
        load_hero(hero , "hero.bin");
    }


//

// init stage 1
/**
* @brief init stage 1.
* @param hero  Notre hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param frametime  Our frame
* @return Nothing
*/
void init_stage1(perso_hero *hero, entite_secondaire tab[], hajra hajjoura[], fond_ecran *background, SDL_Surface *black_background, int *frametime)
{
    *frametime = 0;
    // hero
    /*
    if(hero->load == 0 )
    {
        hero->cord.x = 50;
        hero->cord.y = 200;
        hero->cord.w = 32;
        hero->cord.h = 40;
        hero->score = 0;

        hero->frame.x = 150;
        hero->frame.w = 150;
        hero->frame.h = 150;
        hero->frame.y = 0;

        // background

        background->camera.x = 0;
        background->camera.y = 0;
        background->camera.h = 500;
        background->camera.w = 500;

        //
    }
    */
    
    
    hero->heart_image_cord.x = 0;
    hero->heart_image_cord.y = 0;

    hero->heart_image_frame.x = 0;
    hero->heart_image_frame.y = 0;
    hero->heart_image_frame.w = 300;
    hero->heart_image_frame.h = 50;

    hero->ball_cord.x = hero->cord.x;
    hero->ball_cord.y = hero->cord.y;

    hero->first_entry_jump = 1;

    hero->coeff_sprite = 0;
    hero->direction = 1;
    hero->attack_state = 0;
    hero->acc = 0;
    hero->speed = 0;
    hero->acc = 0;
    hero->speed = 0;

    hero->pause = 0;
    hero->cord_score.x = 500;
    hero->cord_score.y = 200;

    
    //

    // entit sec

    // bat 1

    tab[0].frame.x = 0;
    tab[0].frame.y = 0;
    tab[0].coef = 0;
    tab[0].cord.w = 110;
    tab[0].cord.h = 70;
    tab[0].death = 0;
    tab[0].cord.x = 200;
    tab[0].cord.y = 0;
    tab[0].direction = 1;

    // bat2

    tab[1].frame.x = 0;
    tab[1].frame.y = 0;
    tab[1].cord.w = 110;
    tab[1].cord.h = 70;
    tab[1].death = 0;
    tab[1].coef = 0;
    tab[1].cord.x = 800;
    tab[1].cord.y = 170;
    tab[1].direction = 1;

    //bat 3

    tab[2].frame.x = 0;
    tab[2].frame.y = 0;
    tab[2].cord.w = 110;
    tab[2].cord.h = 70;
    tab[2].death = 0;
    tab[2].coef = 0;
    tab[2].cord.x = 1500;
    tab[2].cord.y = 370;
    tab[2].direction = 1;

    // coin

    tab[3].coef = 0;
    tab[3].cord.w = 50;
    tab[3].cord.h = 50;
    tab[3].death = 0;
    tab[3].value = 200;
    tab[3].cord.x = 350;
    tab[3].cord.y = 270;

    // coin 2
    tab[4].coef = 0;
    tab[4].cord.w = 50;
    tab[4].cord.h = 50;
    tab[4].death = 0;
    tab[4].value = 200;
    tab[4].cord.x = 570;
    tab[4].cord.y = 270;

    // hajjoura

  //  hajjoura[0].cord.x = 470;
    hajjoura[0].cord.y = -50;
    hajjoura[0].cord.w = 80;
    hajjoura[0].cord.h = 120;

    //hajjoura[1].cord.x = 730;
    hajjoura[1].cord.y = -50;
    hajjoura[1].cord.w = 80;
    hajjoura[1].cord.h = 120;

   // hajjoura[2].cord.x = 2000;
    hajjoura[2].cord.y = -50;
    hajjoura[2].cord.w = 80;
    hajjoura[2].cord.h = 120;

    //

    
}

//

// initi stage 2
/**
* @brief init stage 2.
* @param hero  Notre hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param frametime  Our frame
* @return Nothing
*/
void init_stage2(perso_hero *hero, entite_secondaire tab[], hajra hajjoura[], fond_ecran *background, SDL_Surface *black_background, int *frametime)
{
    *frametime = 0;
    // hero
    
    if (hero->load == 1 )
    {
      //  printf("bazola \n");
        load_all(hero ,background);
               
    }

    else if(hero->load == 0  )
    {
            hero->cord.x = 50;
            hero->cord.y = 200;
            hero->cord.w = 32;
            hero->cord.h = 40;
          //  hero->score = 0;

            hero->frame.x = 150;
            hero->frame.w = 150;
            hero->frame.h = 150;
            hero->frame.y = 0;

            // background

            background->camera.x = 0;
            background->camera.y = 0;
            background->camera.h = 500;
            background->camera.w = 500;


            hero->heart_image_cord.x = 0;
            hero->heart_image_cord.y = 0;

            hero->heart_image_frame.x = 0;
            hero->heart_image_frame.y = 0;
            hero->heart_image_frame.w = 300;
            hero->heart_image_frame.h = 50;

            hero->ball_cord.x = hero->cord.x;
            hero->ball_cord.y = hero->cord.y;

            hero->first_entry_jump = 1;

            hero->coeff_sprite = 0;
            hero->direction = 1;
            hero->attack_state = 0;
            hero->acc = 0;
            hero->speed = 0;
            hero->acc = 0;
            hero->speed = 0;

            hero->pause = 0;
            hero->cord_score.x = 500;
            hero->cord_score.y = 200;

            
            //

            // entit sec

            // bat 1

            tab[0].frame.x = 0;
            tab[0].frame.y = 0;
            tab[0].coef = 0;
            tab[0].cord.w = 110;
            tab[0].cord.h = 70;
            tab[0].death = 0;
            tab[0].cord.x = 200;
            tab[0].cord.y = 0;
            tab[0].direction = 1;

            // bat2

            tab[1].frame.x = 0;
            tab[1].frame.y = 0;
            tab[1].cord.w = 110;
            tab[1].cord.h = 70;
            tab[1].death = 0;
            tab[1].coef = 0;
            tab[1].cord.x = 800;
            tab[1].cord.y = 170;
            tab[1].direction = 1;

            //bat 3

            tab[2].frame.x = 0;
            tab[2].frame.y = 0;
            tab[2].cord.w = 110;
            tab[2].cord.h = 70;
            tab[2].death = 0;
            tab[2].coef = 0;
            tab[2].cord.x = 1500;
            tab[2].cord.y = 370;
            tab[2].direction = 1;

            // coin

            tab[3].coef = 0;
            tab[3].cord.w = 50;
            tab[3].cord.h = 50;
            tab[3].death = 0;
            tab[3].value = 200;
            tab[3].cord.x = 350;
            tab[3].cord.y = 270;

            // coin 2
            tab[4].coef = 0;
            tab[4].cord.w = 50;
            tab[4].cord.h = 50;
            tab[4].death = 0;
            tab[4].value = 200;
            tab[4].cord.x = 570;
            tab[4].cord.y = 270;

            // hajjoura

           // hajjoura[0].cord.x = 470;
            hajjoura[0].cord.y = -50;
            hajjoura[0].cord.w = 80;
            hajjoura[0].cord.h = 120;

          //  hajjoura[1].cord.x = 730;
            hajjoura[1].cord.y = -50;
            hajjoura[1].cord.w = 80;
            hajjoura[1].cord.h = 120;

          //  hajjoura[2].cord.x = 2000;
            hajjoura[2].cord.y = -50;
            hajjoura[2].cord.w = 80;
            hajjoura[2].cord.h = 120;

            hero->cord_mini_perso.x=290; 
            hero->cord_mini_perso.y=474; 
    
    
    }
    
    
     
}
/**
* @brief mission 2.
* @param hero  Notre hero
* @param backgound our background
* @return Nothing
*/

void pause(SDL_Event ev , perso_hero *hero , SDL_Surface *screen,fond_ecran *background)
{
    
    switch (ev.type)
    {
    case SDL_MOUSEBUTTONUP:

        if ( ev.button.button ==SDL_BUTTON_LEFT && ev.motion.x > 300 && ev.motion.x < 430 && ev.motion.y > 190 && ev.motion.y < 230 )
        {
            hero->save_frame.x = 500 ; 
            save_all (hero, background);
        }
        
        else if (ev.button.button == SDL_BUTTON_LEFT &&  ev.motion.x > 506 && ev.motion.x < 620 && ev.motion.y > 190 && ev.motion.y < 230)
        {
            hero->save_frame.x = 1000 ; 
            hero->pause = 0 ; 
            hero->game = 5 ; 
        }

        else if (ev.button.button == SDL_BUTTON_LEFT && ev.motion.x > 444 && ev.motion.x < 490 && ev.motion.y > 260 && ev.motion.y < 313)
        {
            hero->save_frame.x = 1500 ; 
            hero->pause = 0 ;
            
        }

        else
        {
            hero->save_frame.x = 0 ;
        }
        
        break;

    }



    
      
    SDL_BlitSurface(hero->save,&hero->save_frame,screen,&hero->save_cord);
 //   printf("bazola \n");
    
    SDL_Flip(screen);


}

/**
* @brief mission 2.
* @param hero  Notre hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param frametime  Our frame
*@param tab_coin[]  Our coin
* @return Nothing
*/

void mission2(perso_hero *hero, SDL_Event ev, fond_ecran *background, SDL_Surface *screen, entite_secondaire tab[],
              hajra hajjoura[], SDL_Surface *black_background, int *frametime, coin tab_coin[])
{

                                            
  //  hero->pause = 0 ; 

    if (ev.type==SDL_KEYUP)
        {
            if (ev.key.keysym.sym == SDLK_ESCAPE)
            {
                hero->pause = 1 ; 
                //save_all (hero, background);

            }
            
        }
    printf("%d \n",hero->pause);
    if (hero->pause == 1 )
    {

        pause( ev , hero , screen,background);
        if (60 / (*frametime) == 1)
        {
            (*frametime) = 0;
        }


    }

    else if (hero->pause == 0 )
    {

        everything(hero, ev, background, screen, tab, hajjoura, black_background, tab_coin); //PROBLEM HAJOURRA PROBLEM MINI MAP PROBLEM (XY) ent sec PROBLEM Coin 

        if (60 / (*frametime) == 1)
        {
            (*frametime) = 0;
            animation_hero(hero);
            animation_entite_sec(&tab[0]);
            animation_entite_sec(&tab[1]);
            animation_entite_sec(&tab[2]);
            
            hero->mvt = 0;
        }
        

        
        
        refresh(*hero, tab, hajjoura, background, screen, tab_coin);

        
        //printf("yes \n");
    }
}

//

// tictactoe
/**
* @brief pos2.
* @param x   axe horizontale de notre matrice
* @param y  axe verticale de notre matrice
*@param mat[][3]  notre matrice
* @return tour
*/
int pos2(int x, int y, SDL_Surface *o, SDL_Surface *screen, int mat[][3])
{
    int tour = 1;
    SDL_Rect pos;

    if (x == 0 && y == 0)
    {
        mat[0][0] = 0;
        pos.x = 155;
        pos.y = 35;

        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    if (x == 0 && y == 1)
    {
        mat[0][1] = 0;

        pos.x = 255;
        pos.y = 35;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    if (x == 0 && y == 2)
    {
        mat[0][2] = 0;

        pos.x = 355;
        pos.y = 35;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    if (x == 1 && y == 0)
    {
        mat[1][0] = 0;

        pos.x = 155;
        pos.y = 135;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x == 1 && y == 1)
    {
        mat[1][1] = 0;

        pos.x = 255;
        pos.y = 140;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x == 1 && y == 2)
    {
        mat[1][2] = 0;

        pos.x = 355;
        pos.y = 150;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    if (x == 2 && y == 0)
    {
        mat[2][0] = 0;

        pos.x = 155;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x == 2 && y == 1)
    {
        mat[2][1] = 0;

        pos.x = 255;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x == 2 && y == 2)
    {
        mat[2][2] = 0;

        pos.x = 355;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    tour = 0;

    SDL_Flip(screen);
    return tour;
}
/**
* @brief pos.
* @param x   axe horizontale de notre matrice
* @param y  axe verticale de notre matrice
*@param mat[][3]  notre matrice
* @return tour
*/
int pos(int x, int y, SDL_Surface *o, SDL_Surface *screen, int mat[][3])
{
    int tour = 0;
    SDL_Rect pos;
    if (x > 150 && x < 220 && y < 100 && y > 30 && mat[0][0] == -1)
    {

        mat[0][0] = 1;

        pos.x = 155;
        pos.y = 35;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x > 253 && x < 320 && y < 100 && y > 30 && mat[0][1] == -1)
    {

        mat[0][1] = 1;

        pos.x = 255;
        pos.y = 35;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    if (x > 350 && x < 425 && y < 100 && y > 30 && mat[0][2] == -1)
    {

        mat[0][2] = 1;

        pos.x = 355;
        pos.y = 35;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }

    //

    if (x > 153 && x < 220 && y > 125 && y < 200 && mat[1][0] == -1)
    {

        mat[1][0] = 1;

        pos.x = 155;
        pos.y = 140;
        SDL_BlitSurface(o, NULL, screen, &pos);
        SDL_Flip(screen);
    }
    if (x > 250 && x < 323 && y > 125 && y < 200 && mat[1][1] == -1)
    {

        mat[1][1] = 1;

        pos.x = 255;
        pos.y = 140;
        SDL_BlitSurface(o, NULL, screen, &pos);
        SDL_Flip(screen);
    }
    if (x > 350 && x < 425 && y > 125 && y < 200 && mat[1][2] == -1)
    {

        mat[1][2] = 1;

        pos.x = 355;
        pos.y = 140;
        SDL_BlitSurface(o, NULL, screen, &pos);
        SDL_Flip(screen);
    }

    //

    if (x > 150 && x < 223 && y > 220 && y < 305 && mat[2][0] == -1)
    {

        mat[2][0] = 1;

        pos.x = 155;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
        SDL_Flip(screen);
    }
    if (x > 253 && x < 320 && y > 220 && y < 325 && mat[2][1] == -1)
    {

        mat[2][1] = 1;

        pos.x = 255;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
        SDL_Flip(screen);
    }
    if (x > 350 && x < 425 && y > 220 && y < 325 && mat[2][2] == -1)
    {

        mat[2][2] = 1;

        pos.x = 355;
        pos.y = 250;
        SDL_BlitSurface(o, NULL, screen, &pos);
    }
    SDL_Flip(screen);
    tour = 1;
    return tour;
}
/**
* @brief pos2.
*@param mat[][3]  notre matrice
* @return game_state
*/
int verif_game_loop(int mat[][3])
{
    int i, j;
    //int game_state=0;
    //int game_state=0;
    int game_state = 3;
    int count = 0;

    //game_state==1 so player has won
    //game_state==2 so computer won
    //game_state==3 so game is over
    //game_state==0 so nothing happened game is still going

    //verificaton horizantal et verticale

    for (i = 0; i < 3; i++)
    {
        //vert
        if (mat[i][0] == 1 && mat[i][1] == 1 && mat[i][2] == 1)
        {
            game_state = 1;
            printf("3ejja");

            return game_state;
        }

        //horiz
        if (mat[0][i] == 1 && mat[1][i] == 1 && mat[2][i] == 1)
        {
            game_state = 1;

            return game_state;
        }

        if (mat[i][0] == 0 && mat[i][1] == 0 && mat[i][2] == 0)
        {
            game_state = 2;

            return game_state;
        }

        if (mat[0][i] == 0 && mat[1][i] == 0 && mat[2][i] == 0)
        {
            game_state = 2;

            return game_state;
        }
    }

    //

    //verification axial

    if (mat[0][0] == 1 && mat[1][1] == 1 && mat[2][2] == 1)
    {
        game_state = 1;
        return game_state;

        printf("mabbrook");
    }

    if (mat[0][0] == 0 && mat[1][1] == 0 && mat[2][2] == 0)
    {
        game_state = 2;

        return game_state;
    }

    if (mat[0][2] == 1 && mat[1][1] == 1 && mat[2][0] == 1)
    {
        game_state = 1;
        return game_state;
        printf("mabbrook");
    }

    if (mat[0][2] == 0 && mat[1][1] == 0 && mat[2][0] == 0)
    {
        game_state = 2;

        return game_state;
    }

    //

    //verif end game

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (mat[i][j] != -1)
            {
                count++;
            }
        }
    }

    if (count != 9)
    {
        game_state = 0;
    }

    //

    return game_state;
}
/**
* @brief tictactoe(jouer contre l'ordinateur ).
* @param first_time    le 1er mouement 
* @param game_state  le statut de notre jeu
*@param mat[][3]  notre matrice
*@param tour le tour du perso 
*@param enigma_solved  la resultat du defi 

* @return Nothing
*/
void tictactoe(int *first_time, int *game_state, int mat[][3], int *tour, SDL_Surface *o_image,
               SDL_Surface *x_image, SDL_Surface *screen, SDL_Event ev, SDL_Surface *backgroundimage, SDL_Surface *texte_nothing, SDL_Surface *texte_enigma_solved,
               SDL_Surface *texte_loss, SDL_Rect textelPosition, int *enigma_solved)
{
    int x, y;
    if ((*first_time) != 0)
    {
        (*game_state) = verif_game_loop(mat);
    }
    else if ((*first_time) == 0)
    {
        SDL_BlitSurface(backgroundimage, NULL, screen, 0);
        SDL_Flip(screen);
    }

    printf("\n \n");

    printf("%d %d %d \n", mat[0][0], mat[0][1], mat[0][2]);
    printf("%d %d %d \n", mat[1][0], mat[1][1], mat[1][2]);
    printf("%d %d %d \n", mat[2][0], mat[2][1], mat[2][2]);
    printf("\n");

    //game_state=verif_game_loop(mat);
    if ((*tour) == 1 && (*game_state) == 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (mat[x][y] != -1);

        //printf("x=%d y=%d \n", x, y);
        (*tour) = pos2(x, y, o_image, screen, mat);
        (*first_time)++;
    }

    //game_state=verif_game_loop(mat);

    if (ev.type == SDL_MOUSEBUTTONDOWN && (*tour) == 0 && (*game_state) == 0)
    {
        x = ev.motion.x;
        y = ev.motion.y;
        (*first_time)++;

        (*tour) = pos(x, y, x_image, screen, mat);
    }

    if ((*game_state) == 3)
    {

        (*enigma_solved) = -1;
        SDL_BlitSurface(backgroundimage, NULL, screen, 0);
        SDL_BlitSurface(texte_nothing, NULL, screen, &textelPosition);
        SDL_Flip(screen);
    }

    // printf("%d \n",tour);
    if ((*game_state) == 1)
    {
        printf("joueru gange \n");
        (*enigma_solved) = 1;

        SDL_BlitSurface(backgroundimage, NULL, screen, 0);
        SDL_BlitSurface(texte_enigma_solved, NULL, screen, &textelPosition);
        SDL_Flip(screen);
    }

    if ((*game_state) == 2)
    {
        (*enigma_solved) = -1;
        printf("pc rba7 \n");
        SDL_BlitSurface(backgroundimage, NULL, screen, 0);
        SDL_BlitSurface(texte_loss, NULL, screen, &textelPosition);
        SDL_Flip(screen);
    }
}

//

// enigma plastic
/**
* @brief plastic (enigme sans fichier ).
* @param try   le 1er mouement 
* @param done  le statut de notre jeu
*@param tour le tour du perso 
*@param enigma_solved  la resultat du defi 
* @return Nothing
*/
void enigme_dhia(SDL_Event ev, int *try, SDL_Surface *background, SDL_Surface *screen, SDL_Surface *wrong_answer1,
                 SDL_Surface *wrong_answer2, SDL_Surface *wrong_answer3, SDL_Surface *right_answer, int *done, SDL_Rect posanswer,
                 int *enigma_solved, SDL_Surface *heart1, SDL_Surface *heart2, SDL_Surface *heart3)
{
    switch (ev.type)
    {
    case SDL_KEYDOWN:
        if (ev.key.keysym.sym == SDLK_a && (*try) != 0)
        {
            SDL_BlitSurface(background, NULL, screen, 0);
            SDL_BlitSurface(wrong_answer1, NULL, screen, &posanswer);
            printf("hey \n");
            (*try)--;
        }
        else if (ev.key.keysym.sym == SDLK_b && (*try) != 0)
        {
            SDL_BlitSurface(background, NULL, screen, 0);
            SDL_BlitSurface(wrong_answer2, NULL, screen, &posanswer);

            (*try)--;
        }
        else if (ev.key.keysym.sym == SDLK_c && (*try) != 0)
        {
            SDL_BlitSurface(background, NULL, screen, 0);
            SDL_BlitSurface(wrong_answer3, NULL, screen, &posanswer);

            (*try)--;
        }
        else if (ev.key.keysym.sym == SDLK_ESCAPE)
        {
            (*done) = 0;
        }
        else
        {
            SDL_BlitSurface(background, NULL, screen, 0);
            SDL_BlitSurface(right_answer, NULL, screen, &posanswer);
            (*done) = 0;
            (*enigma_solved) = 1;
        }

        break;
    }

    switch ((*try))
    {
    case 3:
        SDL_BlitSurface(heart1, NULL, screen, 0);

        break;

    case 2:
        SDL_BlitSurface(heart2, NULL, screen, 0);
        break;

    case 1:
        SDL_BlitSurface(heart3, NULL, screen, 0);
        break;

    case 0:
        printf("lost \n");
        (*enigma_solved) = -1;
        break;
    }

    SDL_Flip(screen);
}
/**
* @brief affichage du l'enigme plastic (enigme sans fichier ).
*@param enigma_solved  la resultat du defi 
* @return Nothing
*/
void initi_enigma_dhia(SDL_Surface *background, SDL_Surface *screen, SDL_Surface *initial,
                       SDL_Surface *heart1, SDL_Rect posanswer, int *enigma_solved)
{
    SDL_BlitSurface(background, NULL, screen, 0);
    SDL_BlitSurface(initial, NULL, screen, &posanswer);
    SDL_BlitSurface(heart1, NULL, screen, 0);
    (*enigma_solved) = 0;
    SDL_Flip(screen);
}

//

//  enigma SW
/**
* @brief Star Wars ( autre enigme ).
* @param  x  ship1
* @param pass ******
*@param x2  ship 2
*@param score  le score
* @return Nothing
*/
void blit_ennemy_ligne_1(SDL_Surface *screen, SDL_Surface *x_background, ship_enigme *x, int *pass, ship_enigme *x2, int *mort, int *score)
{

    x->cord.y = 30;

    if (!(x->cord.x < 50 || x->end == 1))
    {
        SDL_BlitSurface(x->image, NULL, screen, &x->cord);
        x->cord.x -= 100;
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && mort == 0)
        {

            *mort = 1;
        }
    }

    else
    {
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && *mort == 0)
        {

            *score = *score - 1;
        }
        *pass = 9;
        x->end = 1;
        x->cord.x = 1000;
    }
}
/**
* @brief Star Wars ( autre enigme ).
* @param  x  ship1
* @param pass ******
*@param x2  ship 2
*@param score  le score
* @return Nothing
*/
void blit_ennemy_ligne_2(SDL_Surface *screen, SDL_Surface *x_background, ship_enigme *x, int *pass, ship_enigme *x2, int *mort, int *score)
{
    x->cord.y = 180;

    int z = 0;
    if (!(x->cord.x < 50 || x->end == 1))
    {

        SDL_BlitSurface(x->image, NULL, screen, &x->cord);
        x->cord.x -= 100;
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && *mort == 0)
        {

            *score = *score - 1;
            *mort = 1;
        }
    }

    else
    {
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && *mort == 0)
        {

            *score = *score - 1;
        }
        *pass = 9;
        x->end = 1;
        x->cord.x = 1000;
    }
}
/**
* @brief Star Wars ( autre enigme ).
* @param  x  ship1
* @param pass ******
*@param x2  ship 2
*@param score  le score
* @return Nothing
*/
void blit_ennemy_ligne_3(SDL_Surface *screen, SDL_Surface *x_background, ship_enigme *x, int *pass, ship_enigme *x2, int *mort, int *score)
{
    x->cord.y = 330;
    SDL_Delay(50);
    if (!(x->cord.x < 50 || x->end == 1))
    {
        SDL_BlitSurface(x->image, NULL, screen, &x->cord);
        x->cord.x -= 100;
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && *mort == 0)
        {
            printf("3333333333333333\n");
            *score = *score - 1;
            ;
            *mort = 1;
        }
    }
    else
    {
        if (x2->cord.x == x->cord.x && x2->cord.y == x->cord.y && *mort == 0)
        {
            printf("3333333333333333\n");

            *score = *score - 1;
        }
        *pass = 9;
        x->end = 1;
        x->cord.x = 1000;
    }
}
/**
* @brief Star Wars ( autre enigme ).
* @param  x  ship1
* @param passe ******
*@param x2  ship 2
*@param score  le score
*@param choix ******
*@param mort ******
*@param mor1 ******
*@param mor2 ******
* @return Nothing
*/
void refresh_2(int *passe, SDL_Surface *screen, SDL_Surface *x_background, ship_enigme *x, int *choix, ship_enigme *x2, int *mort, int *score, int *mort1, int *mort2)
{

    int choix1 = 54;

    if (*passe == 9)
    {
        do
        {
            choix1 = rand() % 6;

        } while (*choix == choix1);

        *choix = choix1;
        *passe = *choix;
    }
    else
    {

        if (*passe == 0)
        {

            x->end = 0;
            *mort = 0;
            blit_ennemy_ligne_1(screen, x_background, x, &*passe, &*x2, &*mort, *&score);
            SDL_Flip(screen);
        }

        if (*passe == 5)
        {

            x->end = 0;
            //blit_ship_enigme_ligne_1(screen,x_background,x,&*passe);

            blit_ennemy_ligne_2(screen, x_background, x, &*passe, &*x2, &*mort, *&score);
            *mort1 = 0;

            blit_ennemy_ligne_3(screen, x_background, x, &*passe, &*x2, &*mort1, *&score);

            SDL_Flip(screen);
        }
        if (*passe == 1)
        {

            x->end = 0;
            *mort = 0;
            blit_ennemy_ligne_1(screen, x_background, x, &*passe, &*x2, &*mort2, *&score);
            *mort = 0;
            blit_ennemy_ligne_2(screen, x_background, x, &*passe, &*x2, &*mort, *&score);

            SDL_Flip(screen);
        }

        if (*passe == 2)
        {

            x->end = 0;
            //blit_ship_enigme_ligne_1(screen,x_background,x,&*passe);

            blit_ennemy_ligne_1(screen, x_background, x, &*passe, &*x2, &*mort2, *&score);
            *mort1 = 0;
            blit_ennemy_ligne_3(screen, x_background, x, &*passe, &*x2, &*mort1, *&score);

            SDL_Flip(screen);
        }
    }
    if (*passe == 3)
    {

        x->end = 0;
        blit_ennemy_ligne_2(screen, x_background, x, &*passe, &*x2, &*mort, *&score);
        SDL_Flip(screen);
    }

    if (*passe == 4)
    {

        x->end = 0;
        blit_ennemy_ligne_3(screen, x_background, x, &*passe, &*x2, &*mort1, *&score);
        SDL_Flip(screen);
    }
}
/**
* @brief Star Wars ( autre enigme ).
* @param direction changement du direction
*@param ship2  ship 2
*@param play  jouer
* @return Nothing
*/
void refresh_hero(SDL_Event ev, SDL_Surface *screen, SDL_Surface *background, ship_enigme *ship2, int *dericion, int *play)
{

    if (ev.type == SDL_KEYDOWN)
    {

        switch (ev.key.keysym.sym)
        {

        case (SDLK_UP):
            if (*dericion == 1 && *play == 1)
            {
                ship2->cord.x = 0;
                ship2->cord.y = 30;
                *dericion = 0;
                *play = 0;
            }
            if (*dericion == 2 && *play == 1)
            {
                ship2->cord.x = 0;
                ship2->cord.y = 180;
                *play = 0;
                *dericion = 1;
            }

            break;

        case (SDLK_DOWN):
            if (*dericion == 0 && *play == 1)
            {
                ship2->cord.x = 0;
                ship2->cord.y = 180;
                *dericion = 1;
                *play = 0;
            }
            if (*dericion == 1 && *play == 1)
            {
                ship2->cord.x = 0;
                ship2->cord.y = 330;
                *dericion = 2;
                *play = 0;
            }

            break;
        }
    }
    if (ev.type == SDL_KEYUP)
    {
        *play = 1;
    }

    SDL_BlitSurface(ship2->image, NULL, screen, &ship2->cord);

    SDL_Flip(screen);
}
/**
* @brief Star Wars ( autre enigme ).
* @param  frame_time_enigme_SW
* @param passe1 ******
*@param  frame_time_enigme_SW2
*@param  ship1
*@param  ship2
*@param  direction 
*@param  SW_enigma
*@param  c1
*@param  c2
*@param  c3
*@param play
*@param score  le score
*@param choix ******
*@param mort ******
*@param mor1 ******
*@param mor2 ******
* @return Nothing
*/
void enigme_star_wars(int *frame_time_enigme_SW, SDL_Surface *screen, int *frame_time_enigme_SW2, int *passe1, SDL_Surface *background,
                      ship_enigme *ship1, int *choix, ship_enigme *ship2, int *mort, int *score, int *mort1, int *mort2, SDL_Event ev, int *direction, int *play,
                      SDL_Surface *c1, SDL_Surface *c2, SDL_Surface *c3, int *SW_enigma)
{

    if (5000 / (*frame_time_enigme_SW) == 1)
    {
        (*frame_time_enigme_SW) = 0;
        SDL_BlitSurface(background, NULL, screen, NULL);
        refresh_2(passe1, screen, background, ship1, choix, ship2, mort, score, mort1, mort2);
        SDL_Flip(screen);
    }

    if (60 / (*frame_time_enigme_SW2) == 2)
    {
        (*frame_time_enigme_SW2) = 0;
        refresh_hero(ev, screen, background, ship2, direction, play);
        SDL_Flip(screen);
    }

    switch ((*score))
    {
    case 3:
        SDL_BlitSurface(c1, NULL, screen, NULL);
        break;

    case 2:
        SDL_BlitSurface(c2, NULL, screen, NULL);
        break;
    case 1:
        SDL_BlitSurface(c3, NULL, screen, NULL);
        break;
    case 0:
        *SW_enigma = 1;
        break;
    }
}

//

// enigma file
/**
* @brief equation ( enigme aleatoire par fichier  ).
* @param  x
* @param file_name[]
* @return Nothing
*/
void initi_enigma_rand(enigma *x, char file_name[])
{
    //strcat(x->question,"");
    strcpy(x->question, "file_enigma_questions.png");
    //printf("%s \n",x->question);
    strcpy(x->true_false, "true_false.png");
    strcpy(x->background, "ben.jpg");

    x->question_cord.x = 320;
    x->question_cord.y = 20;

    x->user_input = -1;

    x->question_frame.x = 0;
    x->question_frame.y = 0;
    x->question_frame.w = 360;
    x->question_frame.h = 430;

    x->true_false_frame.x = 0;
    x->true_false_frame.y = 0;
    x->true_false_frame.w = 360;
    x->true_false_frame.h = 430;

    FILE *fp = NULL;

    fp = fopen(file_name, "wb");
    fwrite(&x, sizeof(enigma), 1, fp);
    fclose(fp);
}
/**
* @brief equation ( enigme aleatoire par fichier  ).
* @param  x
* @param file_name[]
* @return Nothing
*/
void load_enigma_rand(enigma *x, char file_name[])
{
    FILE *fp = NULL;
    fp = fopen(file_name, "rb");
    fwrite(&x, sizeof(enigma), 1, fp);
    fclose(fp);
    int i = rand() % 4;
    x->question_frame.x = 360 * i;
    switch (i)
    {
    case 0:
        x->question_solve = 0;
        break;

    case 1:
        x->question_solve = 1;
        break;
    case 2:
        x->question_solve = 0;
        break;
    case 3:
        x->question_solve = 0;
        break;
    }
}
/**
* @brief equation ( enigme aleatoire par fichier  ).
* @param test
* @return Nothing

*/
void enigma_nu_3(SDL_Event ev, enigma *enigme_alea, SDL_Surface *background_file_enigma,
                 SDL_Surface *question, SDL_Surface *true_false, SDL_Surface *screen, int *test)
{
    if (ev.type == SDL_MOUSEBUTTONDOWN)
    {
        if (ev.button.button == SDL_BUTTON_LEFT)
        {
            if (ev.motion.x > 68 + 320 && ev.motion.x < 140 + 320 && ev.motion.y > 200 && ev.motion.y < 280)
            {
                enigme_alea->true_false_frame.x = 0;
                enigme_alea->user_input = 1;
                if (enigme_alea->user_input != enigme_alea->question_solve)
                {
                    printf("wrong \n");
                    *test = -1;
                }
                else
                {
                    printf("yes \n");
                    *test = 1;
                }
            }
            else if (ev.motion.x > 190 + 320 && ev.motion.x < 260 + 320 && ev.motion.y > 200 && ev.motion.y < 280)
            {
                enigme_alea->true_false_frame.x = 360;
                enigme_alea->user_input = 0;
                if (enigme_alea->user_input != enigme_alea->question_solve)
                {
                    printf("wrong \n");
                    *test = -1;
                }
                else
                {
                    *test = 1;
                    printf("yes \n");
                }
            }
        }
    }

    SDL_BlitSurface(background_file_enigma, 0, screen, 0);
    SDL_BlitSurface(question, &enigme_alea->question_frame, screen, &enigme_alea->question_cord);
    SDL_BlitSurface(true_false, &enigme_alea->true_false_frame, screen, &enigme_alea->question_cord);

    SDL_Flip(screen);
}

//

// menu
/**
* @brief Settings .
* @param window
* @param hero
* @param menu2_frame
* @return Nothing

*/
void settings(SDL_Event ev, SDL_Rect *menu2_frame, perso_hero *hero, SDL_Surface *screen, int *window)
{
    switch (ev.type)
    {

    case SDL_MOUSEMOTION:

        // fullscreen
        if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 18 && ev.motion.y < 30)
        {
            menu2_frame->x = 1000;
        }
        // no fullscreen
        else if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 82 && ev.motion.y < 94)
        {
            menu2_frame->x = 2000;
        }
        // sound
        else if (ev.motion.x > 230 && ev.motion.x < 280 && ev.motion.y > 202 && ev.motion.y < 250)
        {
            menu2_frame->x = 3000;
        }
        // sound
        else if (ev.motion.x > 650 && ev.motion.x < 700 && ev.motion.y > 202 && ev.motion.y < 250)
        {
            menu2_frame->x = 4000;
        }

        else if (ev.motion.x > 460 && ev.motion.x < 530 && ev.motion.y > 340 && ev.motion.y < 370)
        {
            menu2_frame->x = 5000;
            hero->multy = 1 ;
        }

        else if (ev.motion.x > 600 && ev.motion.x < 680 && ev.motion.y > 340 && ev.motion.y < 370)
        {
            menu2_frame->x = 6000;
            hero->multy= 0 ; 
        }

        else if (ev.motion.x > 450 && ev.motion.x < 550 && ev.motion.y > 420 && ev.motion.y < 480)
        {
            menu2_frame->x = 7000;
        }

        else
        {
            menu2_frame->x = 0;
        }

        break;

    case SDL_MOUSEBUTTONUP:

        if (ev.button.button == SDL_BUTTON_LEFT)
        {
            // fullscreen
            if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 18 && ev.motion.y < 30 && (*window) == 0)
            {
                menu2_frame->x = 1000;

                *window = SDL_WM_ToggleFullScreen(screen);
            }
            // no fullscreen
            else if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 82 && ev.motion.y < 94 && (*window) == 1)
            {
                menu2_frame->x = 2000;
                screen = SDL_SetVideoMode(1000, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            // sound
            else if (ev.motion.x > 230 && ev.motion.x < 280 && ev.motion.y > 202 && ev.motion.y < 250)
            {
                menu2_frame->x = 3000;
                Mix_PauseMusic();
            }
            // sound
            else if (ev.motion.x > 650 && ev.motion.x < 700 && ev.motion.y > 202 && ev.motion.y < 250)
            {
                menu2_frame->x = 4000;
                Mix_ResumeMusic();
            }
            //
            else if (ev.motion.x > 460 && ev.motion.x < 530 && ev.motion.y > 340 && ev.motion.y < 370)
            {
                menu2_frame->x = 5000;
                
            }

            else if (ev.motion.x > 600 && ev.motion.x < 680 && ev.motion.y > 340 && ev.motion.y < 370)
            {
                menu2_frame->x = 6000;
            }

            else if (ev.motion.x > 450 && ev.motion.x < 550 && ev.motion.y > 420 && ev.motion.y < 480)
            {
                menu2_frame->x = 7000;
                hero->pause = 0;
            }

            else
            {
                menu2_frame->x = 0;
            }
        }

        break;
    }
}
/**
* @brief menu .
* @param hero Our hero
* @param window
* @return Nothing

*/
void menu(SDL_Event ev, SDL_Rect menu1_frame, perso_hero *hero,  SDL_Surface *menu1, SDL_Surface *screen,
          SDL_Rect *menu2_frame, int *window, SDL_Surface *menu2)
{
    if (ev.type == SDL_QUIT)
    {
        hero->game = 5 ; 
    }

    if (hero->pause == 0 ) 
    {
        switch (ev.type)
        {
        case SDL_MOUSEMOTION:
            if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 78 && ev.motion.y < 140)
            {
                menu1_frame.x = 1000;
            }
            else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 190 && ev.motion.y < 250)
            {
                menu1_frame.x = 2000;
            }

            else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 280 && ev.motion.y < 340)
            {
                menu1_frame.x = 3000;
            }

            else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 380 && ev.motion.y < 440)
            {
                menu1_frame.x = 4000;
            }
            else
            {
                menu1_frame.x = 0;
            }

            break;

        case SDL_MOUSEBUTTONDOWN:
            if (ev.button.button == SDL_BUTTON_LEFT)
            {
                // load
                if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 78 && ev.motion.y < 140)
                {
                    menu1_frame.x = 1000;
                    hero->load = 1 ; 
                    hero->game = 5 ; 
                }
                // start
                else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 190 && ev.motion.y < 250)
                {
                    menu1_frame.x = 2000;
                    hero->game = 1 ; 
                    hero->load = 0 ; 
                    
                }

                // settings
                else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 280 && ev.motion.y < 340)
                {
                    menu1_frame.x = 3000;
                    hero->pause = 1;
                }

                // quit
                else if (ev.motion.x > 50 && ev.motion.x < 440 && ev.motion.y > 380 && ev.motion.y < 440)
                {
                    menu1_frame.x = 4000;
                    hero->game = 5 ;
                }
                else
                {
                    menu1_frame.x = 0;
                }
            }

            break;
        }

        SDL_BlitSurface(menu1, &menu1_frame, screen, 0);
       // SDL_Flip(screen);
    }
    
    
    if(hero->pause==1)
    {
        if (ev.type == SDL_QUIT)
        {
            hero->game = 5;
            hero->pause = 0;
        }

        settings(ev, menu2_frame, hero, screen, window);

        SDL_BlitSurface(menu2, menu2_frame, screen, 0);
        //SDL_Flip(screen);
    }
}

//

//  stage 3
/**
* @brief init stage 3.
* @param hero  Notre hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param frametime  Our frame
* @return Nothing
*/
void init_stage3(perso_hero *hero, entite_secondaire tab[], hajra hajjoura[], fond_ecran *background, SDL_Surface *black_background, int *frametime)
{
    *frametime = 0;
    // hero
    hero->cord.x = 50;
    hero->cord.y = 200;
    hero->cord.w = 32;
    hero->cord.h = 40;

    hero->frame.x = 150;
    hero->frame.w = 150;
    hero->frame.h = 150;
    hero->frame.y = 0;

    hero->heart_image_cord.x = 0;
    hero->heart_image_cord.y = 0;

    hero->heart_image_frame.x = 0;
    hero->heart_image_frame.y = 0;
    hero->heart_image_frame.w = 300;
    hero->heart_image_frame.h = 50;

    hero->ball_cord.x = hero->cord.x;
    hero->ball_cord.y = hero->cord.y;

    hero->first_entry_jump = 1;

    hero->coeff_sprite = 0;
    hero->direction = 1;
    hero->attack_state = 0;
    hero->acc = 0;
    hero->speed = 0;
    hero->pause = 0;
    hero->cord_score.x = 500;
    hero->cord_score.y = 200;

    //hero->score = 0;
    //

    // entit sec

    // bat 1

    tab[0].frame.x = 0;
    tab[0].frame.y = 0;
    tab[0].coef = 0;
    tab[0].cord.w = 110;
    tab[0].cord.h = 70;
    tab[0].death = 0;
    tab[0].cord.x = 200;
    tab[0].cord.y = 0;
    tab[0].direction = 1;

    // bat2

    tab[1].frame.x = 0;
    tab[1].frame.y = 0;
    tab[1].cord.w = 110;
    tab[1].cord.h = 70;
    tab[1].death = 0;
    tab[1].coef = 0;
    tab[1].cord.x = 800;
    tab[1].cord.y = 170;
    tab[1].direction = 1;

    //bat 3

    tab[2].frame.x = 0;
    tab[2].frame.y = 0;
    tab[2].cord.w = 110;
    tab[2].cord.h = 70;
    tab[2].death = 0;
    tab[2].coef = 0;
    tab[2].cord.x = 1500;
    tab[2].cord.y = 300;
    tab[2].direction = 1;

    // coin

    tab[3].coef = 0;
    tab[3].cord.w = 50;
    tab[3].cord.h = 50;
    tab[3].death = 0;
    tab[3].value = 200;
    tab[3].cord.x = 350;
    tab[3].cord.y = 270;

    // coin 2
    tab[4].coef = 0;
    tab[4].cord.w = 50;
    tab[4].cord.h = 50;
    tab[4].death = 0;
    tab[4].value = 200;
    tab[4].cord.x = 570;
    tab[4].cord.y = 270;

    // hajjoura

    hajjoura[0].cord.x = 1550;
    hajjoura[0].cord.y = -50;
    hajjoura[0].cord.w = 80;
    hajjoura[0].cord.h = 120;

    hajjoura[1].cord.x = 1810;
    hajjoura[1].cord.y = -50;
    hajjoura[1].cord.w = 80;
    hajjoura[1].cord.h = 120;

    hajjoura[2].cord.x = 2060;
    hajjoura[2].cord.y = -50;
    hajjoura[2].cord.w = 80;
    hajjoura[2].cord.h = 120;

    //

    // background

    background->camera.x = 0;
    background->camera.y = 0;
    background->camera.h = 500;
    background->camera.w = 1000;

    //
}

//

// multyplayer
/**
* @brief mouvement hero 1 .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void hero_movment2_player1(perso_hero *hero, SDL_Event ev, fond_ecran *x_background, SDL_Surface *x_screen, entite_secondaire tab[], hajra tab_hajar[], coin tab_coin[])
{

    switch (ev.type)
    {

    case SDL_KEYDOWN:
        switch (ev.key.keysym.sym)
        {
        case SDLK_SPACE:
            hero->acc += 0.1;

            if (hero->direction == 1)
            {
                hero->mvt = 1;
            }
            else
            {
                hero->mvt = 2;
            }

            break;

        case SDLK_RIGHT:
            //x_background->camera.x ++ ;
            if (x_background->camera.x + 500 > 2740)
            {
                hero->cord.x += 1;
                hero->cord_mini_perso.x += 0.1;
            }
            else if (hero->cord.x < 200)
            {
                hero->cord.x++;
                hero->cord_mini_perso.x += 0.1;
            }

            else
            {
                x_background->camera.x += 2;
                hero->cord.x += 2;
                hero->cord_mini_perso.x += 0.15;
            }

            hero->direction = 1;

            hero->mvt = 1;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera.x;

            break;

        case SDLK_r:

            if (hero->attack_state == 0)
            {
                hero->attack = 1;
                hero->attack_state = 1;
            }

            break;

        case SDLK_LEFT:

            if (x_background->camera.x < 40)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else if (hero->cord.x - x_background->camera.x > 250)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else
            {
                x_background->camera.x -= 2;
                hero->cord.x -= 2;
                hero->cord_mini_perso.x -= 0.15;
                //printf("wassila \n");
            }

            hero->direction = 0;
            hero->mvt = 2;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera.x;

            break;

        case SDLK_UP:

            if (hero->direction == 1 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;
                while (hero->initial_altitude.y - hero->cord.y < 150)
                {

                    if (x_background->camera.x + 500 > 2740)
                    {
                        hero->cord.x += 1;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else if (hero->cord.x < 200)
                    {
                        hero->cord.x++;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else
                    {
                        x_background->camera.x += 3;
                    }
                    //x_background->camera.x +=5;
                    //hero->cord.x +=5;
                    hero->cord.y -= 5;
                    hero->cord_mini_perso.y -= 0.3;
                    hero->mvt = 3;
                    hero->cord.x += 3;
                    hero->cord_mini_perso.x += 0.2;

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh2_player1(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
                }
            }

            if (hero->direction == 0 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;

                while (hero->initial_altitude.y - hero->cord.y < 150)
                {
                    if (x_background->camera.x < 40)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else if (hero->cord.x > 250)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else
                    {
                        x_background->camera.x -= 2;
                    }
                    hero->cord_mini_perso.y -= 0.3;

                    hero->cord_mini_perso.x -= 0.2;
                    //x_background->camera.x -=5;
                    //hero->cord.x -=7;
                    hero->cord.y -= 9;
                    hero->cord.x -= 3;
                    hero->mvt = 3;
                    //rocks_fall (&hajjoura );

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh2_player1(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
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

        case SDLK_ESCAPE:

            hero->pause = 1;
            hero->key_press_up_down = 0;

            break;

        case SDLK_SPACE:
            if (hero->speed > 0)
            {
                hero->acc -= 0.1;
            }

            break;

        case SDLK_UP:

            hero->first_entry_jump = 1;

            break;

        case SDLK_r:

            hero->attack_state = 0;

            break;

        case SDLK_RIGHT:

            break;

        case SDLK_LEFT:

            break;
        }

        break;
    }

    hero->cord_origin_axis.x = x_background->camera.x + hero->cord.x;
}
/**
* @brief mouvement hero 2 .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void hero_movment2_player2(perso_hero *hero, SDL_Event ev, fond_ecran *x_background, SDL_Surface *x_screen, entite_secondaire tab[], hajra tab_hajar[], coin tab_coin[])
{

    switch (ev.type)
    {

    case SDL_KEYDOWN:
        switch (ev.key.keysym.sym)
        {
        case SDLK_v:
            hero->acc += 0.1;

            if (hero->direction == 1)
            {
                hero->mvt = 1;
            }
            else
            {
                hero->mvt = 2;
            }

            break;

        case SDLK_d:
            //x_background->camera.x ++ ;
            if (x_background->camera2.x + 500 > 2740)
            {
                hero->cord.x += 1;
                hero->cord_mini_perso.x += 0.1;
            }
            else if (hero->cord.x < 200)
            {
                hero->cord.x++;
                hero->cord_mini_perso.x += 0.1;
            }

            else
            {
                x_background->camera2.x += 2;
                hero->cord.x += 2;
                hero->cord_mini_perso.x += 0.15;
            }

            hero->direction = 1;

            hero->mvt = 1;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera2.x;

            break;

        case SDLK_r:

            if (hero->attack_state == 0)
            {
                hero->attack = 1;
                hero->attack_state = 1;
            }

            break;

        case SDLK_q:

            if (x_background->camera2.x < 40)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else if (hero->cord.x - x_background->camera2.x > 250)
            {
                hero->cord.x--;
                hero->cord_mini_perso.x -= 0.1;
            }

            else
            {
                x_background->camera2.x -= 2;
                hero->cord.x -= 2;
                hero->cord_mini_perso.x -= 0.15;
                //printf("wassila \n");
            }

            hero->direction = 0;
            hero->mvt = 2;

            hero->cord_origin_axis.x = hero->cord.x + x_background->camera2.x;

            break;

        case SDLK_z:

            if (hero->direction == 1 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;
                while (hero->initial_altitude.y - hero->cord.y < 150)
                {

                    if (x_background->camera2.x + 500 > 2740)
                    {
                        hero->cord.x += 1;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else if (hero->cord.x < 200)
                    {
                        hero->cord.x++;
                        hero->cord_mini_perso.x += 0.1;
                    }
                    else
                    {
                        x_background->camera2.x += 3;
                    }
                    //x_background->camera.x +=5;
                    //hero->cord.x +=5;
                    hero->cord.y -= 5;
                    hero->cord_mini_perso.y -= 0.3;
                    hero->mvt = 3;
                    hero->cord.x += 3;
                    hero->cord_mini_perso.x += 0.2;

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh2(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
                }
            }

            if (hero->direction == 0 && hero->first_entry_jump == 1)
            {

                hero->initial_altitude.y = hero->cord.y;

                while (hero->initial_altitude.y - hero->cord.y < 150)
                {
                    if (x_background->camera2.x < 40)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else if (hero->cord.x > 500)
                    {
                        hero->cord.x--;
                        hero->cord_mini_perso.x -= 0.1;
                    }

                    else
                    {
                        x_background->camera2.x -= 2;
                    }
                    hero->cord_mini_perso.y -= 0.3;

                    hero->cord_mini_perso.x -= 0.2;
                    //x_background->camera.x -=5;
                    //hero->cord.x -=7;
                    hero->cord.y -= 9;
                    hero->cord.x -= 3;
                    hero->mvt = 3;
                    //rocks_fall (&hajjoura );

                    animation_hero(hero);
                    mvt_alea_entite_secondaire(&tab[0], 100, 500);
                    mvt_alea_entite_secondaire(&tab[1], 700, 1000);
                    mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

                    refresh2(*hero, tab, tab_hajar, x_background, x_screen, tab_coin);
                }
            }

            hero->first_entry_jump = 0;
            hero->cord_origin_axis.x = hero->cord.x + x_background->camera2.x;

            break;
        }

        break;

    case SDL_KEYUP:

        switch (ev.key.keysym.sym)
        {

        case SDLK_ESCAPE:

            hero->pause = 1;
            hero->key_press_up_down = 0;

            break;

        case SDLK_v:
            if (hero->speed > 0)
            {
                hero->acc -= 0.1;
            }

            break;

        case SDLK_z:

            hero->first_entry_jump = 1;

            break;

        case SDLK_r:

            hero->attack_state = 0;

            break;
        }

        break;
    }

    hero->cord_origin_axis.x = x_background->camera.x + hero->cord.x;
}
/**
* @brief refrech2 .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void refresh2(perso_hero hero, entite_secondaire tab[], hajra tab_hjarr[], fond_ecran *x_background, SDL_Surface *x_screen, coin tab_coin[])
{

    SDL_Color color = {0, 0, 0};

    SDL_BlitSurface(x_background->backk2, &x_background->camera2, x_screen, &x_background->pos_cam2);
    SDL_BlitSurface(hero.heart_image, &hero.heart_image_frame, x_screen, &hero.heart_image_cord);
    show_score2(x_screen, hero.score );
    SDL_BlitSurface(x_background->backk_entit_sec, NULL, x_background->backk2, NULL);
    // SDL_BlitSurface(hero.sprite,&hero.frame,x_screen,&hero.cord);
    SDL_BlitSurface(x_background->mini_map2, NULL, x_screen, &x_background->cord_min_map2);
    blit_mini_map(x_screen, hero.mini_perso, &hero.cord_mini_perso);

    SDL_BlitSurface(hero.sprite, &hero.frame, x_background->backk2, &hero.cord);
    SDL_BlitSurface(tab[0].sprite, &tab[0].frame, x_background->backk2, &tab[0].cord);
    SDL_BlitSurface(tab[2].sprite, &tab[2].frame, x_background->backk2, &tab[2].cord);
    SDL_BlitSurface(tab[1].sprite, &tab[1].frame, x_background->backk2, &tab[1].cord);

    if (tab_coin[0].byby != 10)
    {
        SDL_BlitSurface(tab_coin[0].coin, 0, x_background->backk2, &tab_coin[0].cord_coin);
    }
    //SDL_BlitSurface(tab_coin[1].coin,0,x_background->backk2,&tab_coin[1].cord_coin);

    if (tab_coin[1].byby != 10)
    {
        SDL_BlitSurface(tab_coin[1].coin, 0, x_background->backk2, &tab_coin[1].cord_coin);
    }

    //SDL_BlitSurface(tab[2].sprite,&tab[2].frame,x_background->backk,&tab[2].cord);

    SDL_BlitSurface(tab_hjarr[0].image, 0, x_background->backk2, &tab_hjarr[0].cord);
    SDL_BlitSurface(tab_hjarr[1].image, 0, x_background->backk2, &tab_hjarr[1].cord);
    SDL_BlitSurface(tab_hjarr[2].image, 0, x_background->backk2, &tab_hjarr[2].cord);

    SDL_Flip(x_screen);
}


/*
void show_score(SDL_Surface *ecran, perso_hero *hero)
    {

        SDL_Surface *x;
        SDL_Color color = {255, 255, 255};
        

        char buffer[50] = "";
        
        SDL_Rect posscore;

        posscore.x = 300;
        posscore.y = 0;
        
        sprintf(buffer, "score : %d", hero->score);
        x = TTF_RenderText_Blended(hero->font, buffer, color);
        
        SDL_BlitSurface(x, NULL, ecran, &posscore);
        printf("bazzola\n");

        SDL_Flip(ecran);
        
        
    }
*/
/**
* @brief mouvement hero .
* @param score  
* @return Nothing
*/
void show_score(SDL_Surface *ecran, int score )
{

	SDL_Surface *x;
	SDL_Color color = {255, 255, 255};
	TTF_Font *font = NULL;

	char buffer[50] = "";

	TTF_Init();
	font = TTF_OpenFont("Roboto-Black.ttf", 40);
	SDL_Rect posscore;

	posscore.x = 0;
	posscore.y = 70;

	sprintf(buffer, "score : %d", score);

	x = TTF_RenderText_Blended(font, buffer, color);

	SDL_BlitSurface(x, NULL, ecran, &posscore);

	TTF_CloseFont(font);
	TTF_Quit();
	
}

/**
* @brief mouvement hero .
* @param score  
* @return Nothing
*/
void show_score2(SDL_Surface *ecran, int score )
{

	SDL_Surface *x;
	SDL_Color color = {255, 255, 255};
	TTF_Font *font = NULL;

	char buffer[50] = "";

	TTF_Init();
	font = TTF_OpenFont("Roboto-Black.ttf", 40);
	SDL_Rect posscore;

	posscore.x = 500;
	posscore.y = 70;

	sprintf(buffer, "score : %d", score);

	x = TTF_RenderText_Blended(font, buffer, color);

	SDL_BlitSurface(x, NULL, ecran, &posscore);

	TTF_CloseFont(font);
	TTF_Quit();
	
}
/**
* @brief refrech1 .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void refresh(perso_hero hero, entite_secondaire tab[], hajra tab_hjarr[], fond_ecran *x_background, SDL_Surface *x_screen, coin tab_coin[])
{
    
    SDL_Color color = {0, 0, 0};
    x_background->camera.w = 1000;

    //x_background->backk= rotozoomSurface(x_background->backk, 0, hero.zoom, 10);

    SDL_BlitSurface(x_background->backk, &x_background->camera, x_screen, 0);
    
    //   SDL_BlitSurface(hero.heart_image, &hero.heart_image_frame, x_screen, 0);
    //printf("5obza\n");
    SDL_BlitSurface(hero.heart_image,&hero.heart_image_frame,x_screen,&hero.heart_image_cord);
    show_score(x_screen, hero.score );
                                    
   
    
    SDL_BlitSurface(x_background->backk_entit_sec, NULL, x_background->backk, NULL);
    SDL_BlitSurface(hero.sprite, &hero.frame, x_background->backk, &hero.cord);
    SDL_BlitSurface(x_background->mini_map, NULL, x_screen, &x_background->cord_min_map);
    blit_mini_map(x_screen, hero.mini_perso, &hero.cord_mini_perso);
    printf("heyyyyyyyyyyyyyyyyyyyyy \n");



    SDL_BlitSurface(tab[0].sprite, &tab[0].frame, x_background->backk, &tab[0].cord);
    SDL_BlitSurface(tab[2].sprite, &tab[2].frame, x_background->backk, &tab[2].cord);
    SDL_BlitSurface(tab[1].sprite, &tab[1].frame, x_background->backk, &tab[1].cord);

    if (tab_coin[0].cycy != 10)
    {
        SDL_BlitSurface(tab_coin[0].coin, 0, x_background->backk, &tab_coin[0].cord_coin);
    }
    if (tab_coin[1].cycy != 10)
    {
        SDL_BlitSurface(tab_coin[1].coin, 0, x_background->backk, &tab_coin[1].cord_coin);
    }
    // SDL_BlitSurface(tab_coin[1].coin,0,x_background->backk2,&tab_coin[1].cord_coin);

    //SDL_BlitSurface(tab[2].sprite,&tab[2].frame,x_background->backk,&tab[2].cord);

    SDL_BlitSurface(tab_hjarr[0].image, 0, x_background->backk, &tab_hjarr[0].cord);
    SDL_BlitSurface(tab_hjarr[1].image, 0, x_background->backk, &tab_hjarr[1].cord);
    SDL_BlitSurface(tab_hjarr[2].image, 0, x_background->backk, &tab_hjarr[2].cord);

    SDL_Flip(x_screen);
    
   



}

/**
* @brief refresh 2 player 1 .
* @param hero  Notre hero
* @param X_backgound our background
*@param tab[]  entité secondaire
*@param tab_hajra[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void refresh2_player1(perso_hero hero, entite_secondaire tab[], hajra tab_hjarr[], fond_ecran *x_background, SDL_Surface *x_screen, coin tab_coin[])
{

    SDL_Color color = {0, 0, 0};

    SDL_BlitSurface(x_background->backk, &x_background->camera, x_screen, 0);

    SDL_BlitSurface(hero.heart_image, &hero.heart_image_frame, x_screen, 0);
    //SDL_BlitSurface(hero.heart_image,&hero.heart_image_frame,x_screen,&hero.heart_image_cord);
    show_score(x_screen, hero.score );

    SDL_BlitSurface(x_background->backk_entit_sec, NULL, x_background->backk, NULL);
    SDL_BlitSurface(hero.sprite, &hero.frame, x_background->backk, &hero.cord);
    SDL_BlitSurface(x_background->mini_map, NULL, x_screen, &x_background->cord_min_map);
    blit_mini_map(x_screen, hero.mini_perso, &hero.cord_mini_perso);

    // blit_mini_map(screen,hero->mini_perso,&hero->cord_mini_perso) ;

    //blit_mini_map(x_screen,hero.mini_perso,&hero.cord_mini_perso) ;

    SDL_BlitSurface(tab[0].sprite, &tab[0].frame, x_background->backk, &tab[0].cord);
    SDL_BlitSurface(tab[2].sprite, &tab[2].frame, x_background->backk, &tab[2].cord);
    SDL_BlitSurface(tab[1].sprite, &tab[1].frame, x_background->backk, &tab[1].cord);

    if (tab_coin[0].cycy != 10)
    {
        SDL_BlitSurface(tab_coin[0].coin, 0, x_background->backk, &tab_coin[0].cord_coin);
    }
    if (tab_coin[1].cycy != 10)
    {
        SDL_BlitSurface(tab_coin[1].coin, 0, x_background->backk, &tab_coin[1].cord_coin);
    }
    // SDL_BlitSurface(tab_coin[1].coin,0,x_background->backk2,&tab_coin[1].cord_coin);

    //SDL_BlitSurface(tab[2].sprite,&tab[2].frame,x_background->backk,&tab[2].cord);

    SDL_BlitSurface(tab_hjarr[0].image, 0, x_background->backk, &tab_hjarr[0].cord);
    SDL_BlitSurface(tab_hjarr[1].image, 0, x_background->backk, &tab_hjarr[1].cord);
    SDL_BlitSurface(tab_hjarr[2].image, 0, x_background->backk, &tab_hjarr[2].cord);

    SDL_Flip(x_screen);
}


/**
* @brief gestion vie et score .
* @param hero  Notre hero
* @param backgound our background
* @return Nothing
*/

void control_gestion_vie_score2(perso_hero *hero, fond_ecran *background)
{
    if (hero->death == 1)
    {
        hero->heart_image_frame.y = 0;
        hero->score -= 100;
        background->camera.x = 0;
        hero->cord.x = 700;
        hero->cord.y = 0;
        hero->death = 0;
        hero->cord_origin_axis.x = 0;
        hero->cord_mini_perso.x = 790;
        hero->cord_mini_perso.y = 460;
    }
}
/**
* @brief everything2 .
* @param hero  Notre hero
*@param hero2 Notre 2eme hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param tab_coin[]  Our coin
* @return Nothing
*/
void everything2(perso_hero *hero, perso_hero *hero2, SDL_Event ev, fond_ecran *background, SDL_Surface *screen, entite_secondaire tab[], hajra hajjoura[], SDL_Surface *black_background, coin tab_coin[])
{
    control_gestion_vie_score(hero, background);
    control_gestion_vie_score2(hero2, background);

    if (collision_coin(hero2, &tab_coin[0]) == 1)
    {
        tab_coin[0].byby = 10;
    }
    else if (collision_coin(hero, &tab_coin[0]) == 1)
    {
        tab_coin[0].cycy = 10;
    }

    else if (collision_coin(hero2, &tab_coin[1]) == 1)
    {
        tab_coin[1].byby = 10;
    }
    else if (collision_coin(hero, &tab_coin[1]) == 1)
    {
        tab_coin[1].cycy = 10;
    }

    //collision_coin(hero,&tab[4]) ;
    //collision_coin(hero2,&tab_coin[1]) ;

    hero_movment2_player1(hero, ev, background, screen, tab, hajjoura, tab_coin);
    hero_movment2_player2(hero2, ev, background, screen, tab, hajjoura, tab_coin);

    collision_surface(black_background, hero);
    collision_surface(black_background, hero2);
    hero_attack(hero);

    collision_tah(hero, background->backk, &background->camera);
    collision_tah(hero2, background->backk2, &background->camera2);
    //collision_ennemy(hero2,&tab[1] );

    if (hero->speed > 0)
    {
        hero->acc = -0.001;
    }
    if (hero->speed < 0)
    {
        hero->acc = 0;
        hero->speed = 0;
    }

    if (hero2->speed > 0)
    {
        hero2->acc = -0.001;
    }
    if (hero2->speed < 0)
    {

        hero2->acc = 0;
        hero2->speed = 0;
    }

    hero_speed(hero, &background->camera, background->camera.x, background->dt);
    hero_speed(hero2, &background->camera2, background->camera2.x, background->dt2);

    //printf("%d  \n",hajjoura[0].cord.y );

    if (hero->cord.x < 600)
    {
        //hero_attack(hero );
        collision_ennemy(hero, &tab[0],background);

        collision_ennemy(hero2, &tab[0],background);
        //  hero_speed(hero2,background);
        mvt_alea_entite_secondaire(&tab[0], 200, 500);

        collision_attack(hero, &tab[0]);
    }

    else if (hero->cord.x > 600 && hero->cord.x < 1000)
    {
        collision_ennemy(hero, &tab[1],background);
        collision_ennemy(hero2, &tab[1],background);
        mvt_alea_entite_secondaire(&tab[1], 700, 1000);

        collision_attack(hero, &tab[1]);
    }

    else if (hero->cord.x > 1300 && hero->cord.x < 1700)
    {
        collision_ennemy(hero, &tab[2],background);
        collision_ennemy(hero2, &tab[2],background);
        mvt_alea_entite_secondaire(&tab[2], 1400, 1700);

        collision_attack(hero, &tab[2]);
    }

    if (SDL_GetTicks() % 300 == 0)
    {
        hajjoura[0].fall_state = 1;
        hajjoura[1].fall_state = 1;
        hajjoura[2].fall_state = 1;
    }

    hero2->coin=4 ; 
     rocks_fall (&hajjoura[0] );
        collision_hajjoura(hero,&hajjoura[0] , background);
      
    rocks_fall (&hajjoura[2] );
        collision_hajjoura(hero,&hajjoura[2] , background);
        
     rocks_fall (&hajjoura[1] );
        
        collision_hajjoura(hero,&hajjoura[1] , background); 


    
    rocks_fall (&hajjoura[0] );
        collision_hajjoura(hero2,&hajjoura[0] , background);
      
    rocks_fall (&hajjoura[2] );
        collision_hajjoura(hero2,&hajjoura[2] , background);
        
     rocks_fall (&hajjoura[1] );
        
        collision_hajjoura(hero2,&hajjoura[1] , background); 


    
}
/**
* @brief mission2_multiplayer.
* @param hero  Notre hero
*@param hero2 Notre 2eme hero
* @param backgound our background
*@param tab[]  entité secondaire
*@param hajjoura[]  Our Rock
*@param frametime  Our frame
*@param tab_coin[]  Our coin
* @return Nothing
*/
void mission2_multy(perso_hero *hero, perso_hero *hero2, SDL_Event ev, fond_ecran *background, SDL_Surface *screen, entite_secondaire tab[],
                    hajra hajjoura[], SDL_Surface *black_background, int *frametime, coin tab_coin[])
{

    

    everything2(hero, hero2, ev, background, screen, tab, hajjoura, black_background, tab_coin);
    //          printf("%d\n",hero2->coin) ;
    if (60 / (*frametime) == 1)
    {
        (*frametime) = 0;
        animation_hero(hero);
        animation_hero(hero2);
        animation_entite_sec(&tab[0]);
        animation_entite_sec(&tab[1]);
        animation_entite_sec(&tab[2]);
        hero->mvt = 0;
        hero2->mvt = 0;
    }

    //save_perso(hero , "hero.bin");

    refresh2_player1(*hero, tab, hajjoura, background, screen, tab_coin);
    refresh2(*hero2, tab, hajjoura, background, screen, tab_coin);
    //SDL_Flip(screen) ;

    // printf("%d %d \n",hero2->cord.x,hero->cord.x);
}

//
