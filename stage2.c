#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_rotozoom.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include"header.h"



int main()
{
    
//ndeclari kil3ada 

    const int FPS=60;
    SDL_Surface * screen = NULL ; 
    fond_ecran background ; 
    SDL_Surface *background_zoom = NULL ;
    SDL_Rect camera_zoom ; 
    SDL_Surface *black_background;
    int game= - 1 ;
    SDL_Event ev ; 
    int frametime;

    Uint32 start ; 
    entite_secondaire tab[5];
    hajra hajjoura[3] ;   
    perso_hero hero;
    
    

//

    
   

//

// init entit_sec 
    

    TTF_Font *font ; 
    SDL_Surface *image_score ; 
    SDL_Rect text_cord ; 
    text_cord.x=300;
    text_cord.y=200;

    

// loadzz
    
 

    font=TTF_OpenFont("Roboto-Black.ttf",100);
    //image_score=TTF_RenderText_Solid(font,"lablebi",color);
    

    SDL_Surface *settings = IMG_Load("savesettingssprite.png");
    SDL_Surface * save = IMG_Load("sqvesprit.png");
    SDL_Rect frame_sett , frame_save , save_cord ; 
    //
    frame_sett.x = 0 ; 
    frame_sett.y = 0 ; 
    frame_sett.w = 1000 ; 
    frame_sett.h = 500 ; 
    //
    frame_save.x = 0 ; 
    frame_save.y = 0 ;
    frame_save.w = 499 ; 
    frame_save.h = 200 ; 

    save_cord.x = 270 ; 
    save_cord.y = 120 ; 


    /*
    while (game==1)
    {
        intialis_mission1
        game = 2 
        while(game == 2 )
        {
            pull(ev)
            mission 1
            if()
            {
                enigme1=1
            } 

        } 
        if (enigme1==1)
        {
            intialisatoionenigme1

        }
        while (enigme1_not_resolu==1)
        {
            fzirrfhifr

        }
        inti
    
    }
    */


    
//

// blit + initialisation
    SDL_Init(SDL_INIT_VIDEO );
    screen=SDL_SetVideoMode(1000,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    
    
//
            
    //tab[0].sprite= rotozoomSurface(tab[0].sprite, 2.5, 1, 10);
    //background.backk= rotozoomSurface(background.backk, 0, 1.5, 10);


    init_stage2(&hero , tab,hajjoura,&background,black_background,&frametime);

    hero.attack_ball=IMG_Load("ball2.png");
    hero.heart_image=IMG_Load("hearts.png");


    tab[0].sprite=IMG_Load("bats.png");
    tab[1].sprite=IMG_Load("bats.png");
    tab[2].sprite=IMG_Load("bats.png");

    tab[3].sprite=IMG_Load("coin.png");
    tab[4].sprite=IMG_Load("coin.png");


    hero.sprite = IMG_Load("sprite_fedi.png");
    background.backk=IMG_Load("map_cave2.jpg");
    background_zoom=IMG_Load("map_cave2.jpg");

    background.backk_entit_sec=IMG_Load("map_cave2.jpg");
    black_background=IMG_Load("map_cave2_black.jpg");

    hajjoura[0].image = IMG_Load("rocks.png");
    hajjoura[1].image=IMG_Load("rocks.png");
    hajjoura[2].image = IMG_Load("rocks.png");

    
    while (game==1)
    {

        SDL_PollEvent(&ev);

        if (ev.type==SDL_QUIT)
        {
            game=0;
        }

        background.t_prev = SDL_GetTicks();    

        frametime ++ ;
        mission2(&hero , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime   );
        

            while (hero.pause == 1 )
            {
                //printf("%d %d \n",ev.motion.x , ev.motion.y);
                SDL_PollEvent(&ev);
                if (ev.type==SDL_MOUSEBUTTONUP  && ev.motion.x > 444 && ev.motion.x < 490 && ev.motion.y > 260 && ev.motion.y < 313)
                {
                    
                    hero.pause = 0 ; 
                }
            


                else if (ev.type==SDL_MOUSEBUTTONUP  && ev.motion.x > 506 && ev.motion.x < 620 && ev.motion.y > 190 && ev.motion.y < 230)
                {
                    hero.pause = 0 ; 
                    game = 0 ; 
                }
                
        
                switch (ev.type)
                {
                    /*
                    case SDL_MOUSEBUTTONUP:
                    
                        hero.pause = 0 ;
                        /*if (ev.key.keysym.sym == SDLK_ESCAPE ) 
                        {
                            hero.pause = 0 ;
                        }
                        
                    break;
                    */
                    /*
                        case  SDL_MOUSEMOTION:

                            // fullscreen
                            if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 18 && ev.motion.y < 30 )
                            {
                                frame_sett.x = 1000 ; 
                            }
                            // no fullscreen 
                            else if (ev.motion.x > 360 && ev.motion.x < 520 && ev.motion.y > 82 && ev.motion.y < 94  )
                            {
                                frame_sett.x = 2000 ; 
                            }

                            else if (ev.motion.x > 230 && ev.motion.x < 280 && ev.motion.y > 202 && ev.motion.y < 250  )
                            {
                                frame_sett.x = 3000 ; 
                            }

                            else if (ev.motion.x > 650 && ev.motion.x < 700 && ev.motion.y > 202 && ev.motion.y < 250  )
                            {
                                frame_sett.x = 4000 ; 
                            }

                            else if (ev.motion.x > 460 && ev.motion.x < 530 && ev.motion.y > 340 && ev.motion.y < 370 )
                            {
                                frame_sett.x = 5000;
                            }

                            else if (ev.motion.x > 600 && ev.motion.x < 680 && ev.motion.y > 340 && ev.motion.y < 370 )
                            {
                                frame_sett.x = 6000;
                            }

                            else if (ev.motion.x > 450 && ev.motion.x < 550 && ev.motion.y > 420 && ev.motion.y < 480 )
                            {
                                frame_sett.x = 7000;
                            }
                            
                            else 
                            {
                                frame_sett.x = 0 ;
                            }
                            
                            
                        break;
                        //

                        case SDL_KEYUP : 
                            if (ev.key.keysym.sym == SDLK_DOWN && hero.key_press_up_down != 5 ) 
                            {
                                hero.key_press_up_down += 1 ; 
                            }
                            else if (ev.key.keysym.sym == SDLK_UP && hero.key_press_up_down != 0 ) 
                            {
                                hero.key_press_up_down -= 1 ; 
                            }
                            
                            frame_sett.x = hero.key_press_up_down * 1000 ; 
                            


                        break ; 
                    */
                    
                    
                    case SDL_MOUSEMOTION : 
                        if (ev.motion.x > 300 && ev.motion.x < 430 && ev.motion.y > 190 && ev.motion.y < 230 )
                        {
                            frame_save.x = 500 ; 
                        }
                        
                        else if (ev.motion.x > 506 && ev.motion.x < 620 && ev.motion.y > 190 && ev.motion.y < 230)
                        {
                            frame_save.x = 1000 ; 
                        }

                        else if (ev.motion.x > 444 && ev.motion.x < 490 && ev.motion.y > 260 && ev.motion.y < 313)
                        {
                            frame_save.x = 1500 ; 
                            
                            
                            
                        }

                        else
                        {
                            frame_save.x = 0 ;
                        }
                        
                    break ; 
                        


                }


                SDL_BlitSurface(save,&frame_save,screen,&save_cord);
                
                SDL_Flip(screen);

                //printf("%d \n",hero.pause);
            }
            
            
        
        
        
        
        //printf("%d \n",hero.pause);
        
        
    }
    

    SDL_FreeSurface(screen);

    return 0 ;
}