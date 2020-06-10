
/**
* @file main_final.c
* @author Gurzil Team
* @date jun 06, 2020
* @version 1.2
*/

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_rotozoom.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include"header.h"
#define TEMPS 30

int main()
{
    // init all hero.game basic elements 
        const int FPS=60;
        SDL_Surface * screen = NULL ; 
        fond_ecran background ; 
        SDL_Surface *background_zoom = NULL ;
        SDL_Rect camera_zoom ; 
        SDL_Surface *black_background;
        
        
        SDL_Event ev ; 
        int frametime;
        Uint32 start ; 
        entite_secondaire tab[5];
        hajra hajjoura[3] ;   
        perso_hero hero , hero2;
        hero.game= - 1 ;
    // 

    // tictactoe
        TTF_Init() ;
        SDL_Color color={0,0,0} ;
        SDL_Surface *texte_win;
        SDL_Surface *texte_nothing;
        SDL_Surface *texte_loss;
        SDL_Rect textelPosition ;
        TTF_Font *fontTest ;
        fontTest=TTF_OpenFont("test.ttf",100);
        hero.font = TTF_OpenFont("Roboto-Black.ttf", 40);
        textelPosition.x=180;
        textelPosition.y=210;

        // init

        int mat[3][3], i, j;

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                mat[i][j] = -1;
            
            }
        }
        //
        int tour = 0;

        SDL_Surface *backgroundimage = NULL;
        SDL_Surface *x_image = NULL;
        SDL_Surface *o_image = NULL;
        o_image = IMG_Load("oo.png");
        x_image = IMG_Load("x.png");
        backgroundimage = IMG_Load("board.png");
        texte_win=TTF_RenderText_Solid(fontTest,"rak rba7t",color) ;
        texte_loss=TTF_RenderText_Solid(fontTest,"rak 5sart",color) ;
        texte_nothing=TTF_RenderText_Solid(fontTest,"rak 3adalt",color) ;
        int game_state=0;int first_time=0;

    //

    // enigma dhia 
        SDL_Surface *background_plastic = IMG_Load("ben.jpg");
        SDL_Surface *initial      = IMG_Load("question.png");
        SDL_Surface *wrong_answer1= IMG_Load("question1.png");
        SDL_Surface *wrong_answer2= IMG_Load("question2.png");
        SDL_Surface *wrong_answer3= IMG_Load("question3.png");
        SDL_Surface *right_answer = IMG_Load("question4.png");

        
        SDL_Surface *heart1 = IMG_Load("100.png");
        SDL_Surface *heart2 = IMG_Load("50.png");
        SDL_Surface *heart3 = IMG_Load("30.png");
        
        SDL_Rect posanswer ; 

        posanswer.x = 300;
        posanswer.y = 0;

        int try = 3  ; 
    //


    //  decl SW

        ship_enigme ship1, ship2;
        ship1.cord.x = 1000;
        ship1.cord.y = 30;
        ship2.cord.x = 0;
        ship2.cord.y = 180;
        int time;
        int frame_time_enigme_SW  = 0;
        int frame_time_enigme_SW2 = 0;
        ship1.image = IMG_Load("ship.png");
        ship2.image = IMG_Load("ship2.png");
        SDL_Surface *background_enigma_SW = IMG_Load("123.png");
        int choix = 4;int play = 1;int passe1 = 9;int passe = 9;  int mort1 = 0;int mort = 0;int score = 3;int mort2 = 0;int direction = 1;

    //

    // decl enigle_file
        enigma enigme_alea ; 
        initi_enigma_rand( &enigme_alea ,"enigma_alea.bin");        
        SDL_Surface *background_file_enigma = IMG_Load(enigme_alea.background);
        SDL_Surface *question = IMG_Load(enigme_alea.question);
        SDL_Surface *true_false = IMG_Load(enigme_alea.true_false);

    //


    //
        int window = 0 ; 
        SDL_Surface *menu1 = IMG_Load("choose.png");
        SDL_Surface *menu2=IMG_Load("menu2.png");
        SDL_Surface *menu3 = SDL_LoadBMP("menu3.bmp");
        SDL_Rect menu1_frame , menu2_frame,rect ; 
        SDL_Surface *rotation;

        menu1_frame.x = 0 ;
        menu1_frame.y = 0 ; 
        menu1_frame.w = 1000 ;
        menu1_frame.h = 500 ; 

        menu2_frame.x = 0 ;
        menu2_frame.y = 0 ; 
        menu2_frame.w = 1000 ;
        menu2_frame.h = 500 ; 
          hero.score=0 ; 
        Mix_Chunk *gta_sound;
        Uint8 volume = 0;
        //Mix_PlayChannel(-1,gta_sound,0);

        SDL_Init(SDL_INIT_AUDIO);
        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
        //if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
        //printf("Error : %s",Mix_GetError());

        hero.pause = 0 ; 

        Mix_Music *music = Mix_LoadMUS("sound2.mp3");

    //

    // enigma states 
        int tictactoe_enigma = 0 ; 
        int plastic_enigma= 0   ; 
        int SW_enigma = 0 , SW_timer ; 
        int file_enigma_alea_rand = 0 ; 

    //


    // mini maps 
        hero2.mini_perso=IMG_Load("perso_mini_map.png") ;
       
        background.cord_min_map.x=290 ; 
        background.cord_min_map.y=420 ; 
        hero.mini_perso=IMG_Load("perso_mini_map.png") ;
        background.cord_min_map2.x=790 ; 
        background.cord_min_map2.y=420 ; 


    //

    // multy 

        hero.heart_image_cord.x = 0 ; 
        hero.heart_image_cord.y = 0 ; 


        hero.heart_image_frame.x=0;
        hero.heart_image_frame.y=0;
        hero.heart_image_frame.w=300;
        hero.heart_image_frame.h=50;

        hero.ball_cord.x=hero.cord.x;
        hero.ball_cord.y=hero.cord.y;


        hero2.heart_image_cord.x = 500 ; 
        hero2.heart_image_cord.y = 0 ; 


        hero2.heart_image_frame.x=0;
        hero2.heart_image_frame.y=0;
        hero2.heart_image_frame.w=300;
        hero2.heart_image_frame.h=50;

        hero2.ball_cord.x=hero.cord.x;
        hero2.ball_cord.y=hero.cord.y;


       
        hero2.direction=1;
        hero2.attack_state=0;
        hero2.first_entry_jump=1;
        hero2.coeff_sprite=0;
        
        background.camera.x=0;
        background.camera.y=0;
        background.camera.h=500;
        background.camera.w=500;
        
        background.camera2.x=0;
        background.camera2.y=0;
        background.camera2.h=500;
        background.camera2.w=500;


        background.pos_cam1.x=0;
        background.pos_cam1.y=0;
        background.pos_cam1.w=500;
        background.pos_cam1.h=500;

        background.pos_cam2.x=500;
        background.pos_cam2.y=0;
        background.pos_cam2.w=500;
        background.pos_cam2.h=500;

        hero.game_state = 0 ;



        coin tab_coin[3] ; 



    //

    // save 

        hero.save = IMG_Load("sqvesprit.png");
        
        
        hero.save_frame.x = 0 ; 
        hero.save_frame.y = 0 ;
        hero.save_frame.w = 499 ; 
        hero.save_frame.h = 200 ; 

        hero.save_cord.x = 270 ; 
        hero.save_cord.y = 120 ; 


    //

    // endgame

        SDL_Surface *end_game = IMG_Load("2.png") ;

    //




    SDL_Init(SDL_INIT_VIDEO );
    screen=SDL_SetVideoMode(1000,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    int hh=0 , healthejja=100;
    hero.score = 0;
    hero.load = 0; 
    int tempsPrecedent = 0, tempsActuel = 0;
    double zoom = 1;
    int sens = 1;
double angle = 0;

    //init_stage1(&hero , tab,hajjoura,&background,black_background,&frametime);
    //init_stage2(&hero2 , tab,hajjoura,&background,black_background,&frametime,tab_coin);
    
    while (hero.game == -1)
    {
        hero.game = 0 ;

        hero2.pause = 0  ; 
        hero.pause = 0 ;
        
        hero.multy = 0 ; 
        // menu
           
            while (hero.game ==  0)
            {
                SDL_PollEvent(&ev);
                tempsActuel = SDL_GetTicks();

            if (tempsActuel - tempsPrecedent > TEMPS)
            {
                angle += 2; //On augmente l'angle pour que l'image tourne sur elle-même.

                tempsPrecedent = tempsActuel;
            }
           
            // SDL_SetColorKey(menu3, SDL_SRCCOLORKEY, SDL_MapRGB(menu3->format, 0, 0, 255));

            rotation = rotozoomSurface(menu3, angle, zoom, 0);
            //On transforme la surface image.
            //rotozoomSurfaceSize(menu3->w, menu3->h, angle, 1.0, &destw, &desth);

            rect.x = ev.button.x - rotation->w / 2;
            rect.y = ev.button.y - rotation->h / 2;
            SDL_SetColorKey(rotation, SDL_SRCCOLORKEY, SDL_MapRGB(rotation->format, 255, 255, 255));
            SDL_SetAlpha(rotation, SDL_SRCALPHA, 75);
            SDL_BlitSurface(rotation, 0, screen, &rect);

            if (zoom >= 2)
            {
                sens = 0;
            }
            else if (zoom <= 0.5)
            {
                sens = 1;
            }

            if (sens == 0)
            {
                zoom -= 0.02;
            }
            else
            {
                zoom += 0.02;
            }
            SDL_Flip(screen);
               // printf("hey\n");
                menu( ev ,  menu1_frame , &hero ,menu1 ,screen , &menu2_frame ,&window , menu2  );
               // printf("%d \n",hero.load);
               
            }


            
            if (hero.load==1 )
            {
                                     //        printf("asba : %d \n",hero.load);

                load_all(&hero ,&background);
                printf("hey %d %d %d\n",hero.game,hero.cord.x,background.camera.x);
                hero.multy = 0 ; 
                hero.load = 1 ; 
               // hero.game = 5 ; 

                
            }
               
            
        //
        
        // loading stage 1
            
            else if(hero.load == 0 )
            {
                hero.cord.x = 50;
                hero.cord.y = 200;
                hero.cord.w = 32;
                hero.cord.h = 40;
                hero.score = 0;

                hero.frame.x = 150;
                hero.frame.w = 150;
                hero.frame.h = 150;
                hero.frame.y = 0;

                // background

                background.camera.x = 0;
                background.camera.y = 0;
                background.camera.h = 500;
                background.camera.w = 500;

                
            }


          //  hero.game= 3 ; 
            if (hero.game==1 )
            {
                
                init_stage1(&hero , tab,hajjoura,&background,black_background,&frametime);
                init_stage1(&hero2 , tab,hajjoura,&background,black_background,&frametime);
                hero.cord_mini_perso.x=290; 
                hero.cord_mini_perso.y=474; 
                hero.attack_ball=IMG_Load("ball2.png");
                hero2.attack_ball=IMG_Load("ball2.png");
                hero.heart_image=IMG_Load("hearts.png");
                hero2.heart_image=IMG_Load("hearts.png");
                tab_coin[0].coin=IMG_Load("coin.png");
                tab_coin[1].coin=IMG_Load("coin.png");
                hero.save = IMG_Load("sqvesprit.png");

                hajjoura[0].cord.x = 900 ; 
                hajjoura[1].cord.x = 1300 ; 
                hajjoura[2].cord.x = 2300 ; 

                tab[1].cord.y = 100 ; 
                tab[2].cord.y = 50 ; 
                tab_coin[0].cord_coin.x = 280 ;
                tab_coin[0].cord_coin.y = 216 ;
                tab_coin[0].stop=0 ;
                tab_coin[1].stop=0 ; 
                tab_coin[1].cord_coin.x = 650;
                tab_coin[1].cord_coin.y = 229 ;

                tab[0].sprite=IMG_Load("UFO.png");
                tab[1].sprite=IMG_Load("UFO.png");
                tab[2].sprite=IMG_Load("UFO.png");
                hero.mini_perso=IMG_Load("perso_mini_map.png") ;

                hero.sprite = IMG_Load("sprite_fedi.png");
                hero2.sprite = IMG_Load("sprite_fedi.png");
                background.backk=IMG_Load("map_desert.png");
                background.backk2=IMG_Load("map_desert.png");
                background_zoom=IMG_Load("map_desert.png");

                background.backk_entit_sec=IMG_Load("map_desert.png");
                background.backk_entit_sec2=IMG_Load("map_desert.png");
                black_background=IMG_Load("map_desert_black.png");

                hajjoura[0].image = IMG_Load("astero.png");
                hajjoura[1].image=IMG_Load("astero.png");
             
                hajjoura[2].image = IMG_Load("astero.png");
                background.mini_map=IMG_Load("mini_map1.png");
                background.mini_map2=IMG_Load("mini_map1.png");
                
                
                hero2.cord_mini_perso.x=790; 
                hero2.cord_mini_perso.y=464; 
                hero2.heart_image_cord.x=500 ; 
                
            }
            
           // hero.game = 2 ; 
        //

        
        // stage 1 

            while (hero.game == 1 )
            {
                SDL_PollEvent(&ev);

                if (ev.type==SDL_QUIT)
                {
                    hero.game=0;
                }
                

                // printf("%f \n",hero.acc) ;

                background.t_prev = SDL_GetTicks();   
                background.t_prev2 = SDL_GetTicks(); 
                frametime ++ ;
               // background.backk= rotozoomSurface(background.backk, 0, hero.zoom, 10);
                
             //   printf("%d %d %d %f\n",hero.cord.x,hero.score,background.camera.x,hero.zoom);

                if (hero.multy == 0)
                {
                    mission2(&hero , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime ,tab_coin  );
                }
                else if (hero.multy==1)
                {
                    mission2_multy(&hero,&hero2 , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime , tab_coin );
                }
                
                
                

                if ( hero.cord.x  >=2200    &&hero.cord.x  <=2500 && plastic_enigma == 0 ) 
                {
                    initi_enigma_dhia(background_plastic ,screen , initial ,heart1 ,  posanswer , &plastic_enigma  );
                    try = 3 ; 
                    while (plastic_enigma != 1 )
                    {
                        SDL_WaitEvent(&ev);
                        enigme_dhia(ev , &try , background_plastic , screen , wrong_answer1 , 
                            wrong_answer2 , wrong_answer3 , right_answer ,&hero.game , posanswer , 
                            &plastic_enigma , heart1 , heart2 ,heart3 );


                        if (plastic_enigma == -1 )
                        {
                            hero.score -= 100 ; 
                            initi_enigma_dhia(background_plastic ,screen , initial ,heart1 ,  posanswer , &plastic_enigma  );
                            try = 3 ; 
                            plastic_enigma = 0 ; 
                        }
                        else if (plastic_enigma == 1 ) 
                        {
                            hero.game = 2 ; 
                            hero.score += 1000 ; 
                            hero.cord.x = 600 ; 
                        }
                         
                    }
                    
                }
                
                background.dt = SDL_GetTicks() - background.t_prev ; 
                background.dt2 = SDL_GetTicks() - background.t_prev2 ; 
            }
        
        // 
        
        
        // loading stage 2 
        

        
        
        if(hero.game==2 )
        {
           
            init_stage2(&hero , tab,hajjoura,&background,black_background,&frametime);
            init_stage2(&hero2 , tab,hajjoura,&background,black_background,&frametime);

            hero.attack_ball=IMG_Load("ball2.png");
            hero2.attack_ball=IMG_Load("ball2.png");
            hero.heart_image=IMG_Load("hearts.png");
            hero2.heart_image=IMG_Load("hearts.png");
            tab_coin[0].coin=IMG_Load("coin.png");
            tab_coin[1].coin=IMG_Load("coin.png");
            tab[0].sprite=IMG_Load("bats.png");
            tab[1].sprite=IMG_Load("bats.png");
            tab[2].sprite=IMG_Load("bats.png");
           tab_coin[0].cycy = 0 ; 
            hero.save = IMG_Load("sqvesprit.png");

           tab_coin[1].cycy = 0 ; 
            tab[1].cord.y=290 ; 
            tab_coin[0].cord_coin.x = 280 ;
            tab_coin[0].cord_coin.y = 316 ;
            
            tab_coin[1].cord_coin.x = 650;
            tab_coin[1].cord_coin.y = 229 ;

            hajjoura[1].cord.x = 1530;
            hajjoura[2].cord.x = 2600 ; 
            hajjoura[0].cord.x = 470;
            

            tab[2].cord.y = 100 ; 
            
                hero.mini_perso=IMG_Load("perso_mini_map.png") ;


            hero.sprite = IMG_Load("sprite_fedi.png");
            hero2.sprite = IMG_Load("sprite_fedi.png");


            
            background.backk=IMG_Load("map_cave2.png");
            
            background.backk2=IMG_Load("map_cave2.png");
            

            
            background.backk_entit_sec=IMG_Load("map_cave2.png");
            background.backk_entit_sec2=IMG_Load("map_cave2.png");
            black_background=IMG_Load("map_cave2_black.png");
            

            hajjoura[0].image = IMG_Load("rocks.png");
            
            hajjoura[1].image=IMG_Load("rocks.png");
            hajjoura[2].image = IMG_Load("rocks.png");
            background.mini_map=IMG_Load("mini_map2.png");
            background.mini_map2=IMG_Load("mini_map2.png"); 
            //hero2.cord_mini_perso.x=790; 
         //   hero2.cord_mini_perso.y=474; 
           // hero2.heart_image_cord.x=500 ; 
                hero.mini_perso=IMG_Load("perso_mini_map.png") ;
            
                hero2.cord_mini_perso.x=790; 
                hero2.cord_mini_perso.y=474; 
                hero2.heart_image_cord.x=500 ; 
                tab_coin[0].stop=0 ;
                tab_coin[1].stop=0 ; 

                
        }
           
 
        //
        // stage 2 
            while (hero.game == 2 )
            {

                
       
                SDL_PollEvent(&ev);

                if (ev.type==SDL_QUIT)
                {
                    hero.game=0;
                }
            

               // printf("%d \n",hero.score);
                background.t_prev = SDL_GetTicks();   
                background.t_prev2 = SDL_GetTicks();   
                
                
                
                frametime ++ ;
                if (hero.multy == 0)
                {
                  //  printf("%d %d %f %f %f \n",hero.game,hero.cord.x,hero.cord_mini_perso.x,hero.cord_mini_perso.y,hero.zoom);
                    
                    mission2(&hero , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime ,tab_coin  );
                    
                    
                }
                else if (hero.multy==1)
                {
                    mission2_multy(&hero,&hero2 , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime , tab_coin );
                }
                
                

                //
                

                
                /*
                if (hero.cord.x == 500 && file_enigma_alea_rand == 0 )
                {
                    load_enigma_rand(&enigme_alea ,"enigma_alea.bin");

                    while (file_enigma_alea_rand != 1 )
                    {
                        SDL_WaitEvent(&ev);
                        enigma_nu_3( ev , &enigme_alea ,background_file_enigma , question , true_false,screen ,&file_enigma_alea_rand);

                        if (file_enigma_alea_rand== 1 )
                        {
                            hero.score += 1000 ; 
                            hero.game = 2 ; 
                        }
                        else if(file_enigma_alea_rand == -1 ) 
                        {
                            hero.score -=100 ; 
                            load_enigma_rand(&enigme_alea ,"enigma_alea.bin");
                            file_enigma_alea_rand = 0 ;

                        }

                    }

                }
                */
                            
                
    
                
                if ( hero.cord.x >=1800 &&hero.cord.x <=1950 && tictactoe_enigma== 0  )
                {
                    //printf("heyyyyy \n");
                    
                    while (tictactoe_enigma == 0 ) 
                    {
                        SDL_WaitEvent(&ev);
                        tictactoe(&first_time, &hero.game_state , mat, &tour ,o_image ,x_image , screen , ev ,backgroundimage , texte_nothing,texte_win , texte_loss , textelPosition ,&tictactoe_enigma);

                        if (tictactoe_enigma == 1 )
                        {
                            hero.game = 3 ; 
                            hero.score += 1000 ; 
                            hero.cord.x = 1800 ; 
                        }

                        else if (tictactoe_enigma == -1) // loss
                        {
                            hero.score -= 100 ; 
                            for (i = 0; i < 3; i++)
                            {
                                for (j = 0; j < 3; j++)
                                {
                                    mat[i][j] = -1;
                                
                                }
                            }
                            tictactoe_enigma = 0 ;

                            SDL_BlitSurface(backgroundimage, NULL, screen, 0);
                            SDL_Flip(screen);
                            hero.game_state=0;first_time=0;tour = 0 ;

                        }
                        
                            
                    }
                    
                    
                    
                    
                }
                
                
                /*
                if (hero.cord.x == 400 && plastic_enigma == 0 ) 
                {
                    initi_enigma_dhia(background_plastic ,screen , initial ,heart1 ,  posanswer , &plastic_enigma  );
                    try = 3 ; 
                    while (plastic_enigma != 1 )
                    {
                        SDL_WaitEvent(&ev);
                        enigme_dhia(ev , &try , background_plastic , screen , wrong_answer1 , 
                            wrong_answer2 , wrong_answer3 , right_answer ,&hero.game , posanswer , 
                            &plastic_enigma , heart1 , heart2 ,heart3 );


                        if (plastic_enigma == -1 )
                        {
                            hero.score -= 100 ; 
                            initi_enigma_dhia(background_plastic ,screen , initial ,heart1 ,  posanswer , &plastic_enigma  );
                            try = 3 ; 
                            plastic_enigma = 0 ; 
                        }
                        else if (plastic_enigma == 1 ) 
                        {
                            hero.game = 2 ; 
                            hero.score += 1000 ; 
                            hero.cord.x = 600 ; 
                        }
                         
                    }
                    

                }
                */
                

                /*
                if (hero.cord.x== 300 && SW_enigma== 0 ) 
                {
                    SW_timer = 0 ;
                    while (SW_enigma!=1)
                    {
                        SW_timer ++ ;
                        frame_time_enigme_SW2 ++ ; 
                        frame_time_enigme_SW ++ ; 
                        SDL_PollEvent(&ev);
                        if (ev.type==SDL_QUIT)
                        {
                            hero.game=0;
                        }
                        
                        enigme_star_wars(&frame_time_enigme_SW , screen , &frame_time_enigme_SW2,&passe1 ,background_enigma_SW , 
                        &ship1 , &choix,&ship2 ,&mort , &score , &mort1 , &mort2 , ev , &direction ,&play,heart1 , heart2 , heart3 ,&SW_enigma);
                        if (SW_timer < 30000 )
                        {
                            hero.score += 200 ; 
                        }
                        else if (SW_timer >= 30000 && SW_timer <= 100000 ) 
                        {
                            hero.score +=500 ; 
                        }
                        else if (SW_timer >= 100000)
                        {
                            hero.score +=1000 ; 
                        }
                        else if (SW_timer == 150000)
                        {
                            SW_enigma = 1 ; 
                        }
                        
                    }
                    

                }
                */

                background.dt = SDL_GetTicks() - background.t_prev ; 
                background.dt2 = SDL_GetTicks() - background.t_prev2 ; 
                       // printf("%d\n",background.dt2) ;

                
                
        
                
            }
            
        //
            
            
        //
        if(hero.game == 3)
        {   
            // loading stage 3
            init_stage2(&hero , tab,hajjoura,&background,black_background,&frametime);
            init_stage2(&hero2 , tab,hajjoura,&background,black_background,&frametime);
            //init_stage2(&hero , tab,hajjoura,&background,black_background,&frametime,tab_coin);
            //init_stage2(&hero2 , tab,hajjoura,&background,black_background,&frametime,tab_coin);
            hero.save = IMG_Load("sqvesprit.png");

            hero.attack_ball=IMG_Load("ball2.png");
            hero2.attack_ball=IMG_Load("ball2.png");
            hero.heart_image=IMG_Load("hearts.png");
            hero2.heart_image=IMG_Load("hearts.png");
            tab_coin[0].coin=IMG_Load("coin.png");
            tab_coin[1].coin=IMG_Load("coin.png");
            tab_coin[0].cycy = 0 ; 
            tab_coin[1].cycy = 0 ; 
            hero.sprite = IMG_Load("sprite_fedi.png");
            hero2.sprite = IMG_Load("sprite_fedi.png");
            background.backk=IMG_Load("map3.png");
            background.backk2=IMG_Load("map3.png");
            background_zoom=IMG_Load("map3.png");
                hero.mini_perso=IMG_Load("perso_mini_map.png") ;

            background.backk_entit_sec=IMG_Load("map3.png");
             background.backk_entit_sec2=IMG_Load("map3.png");
            black_background=IMG_Load("map3_black.png");

            background.mini_map=IMG_Load("mini_map3.png");
            background.mini_map2=IMG_Load("mini_map3.png");
         
            tab[0].sprite=IMG_Load("ghost.png");
            tab[1].sprite=IMG_Load("ghost.png");
            tab[2].sprite=IMG_Load("ghost.png");

            

            hajjoura[0].image = IMG_Load("chandelier.png");
            hajjoura[1].image=IMG_Load("chandelier.png");
            hajjoura[2].image = IMG_Load("chandelier.png");
           
            hajjoura[0].cord.x = 250;
            hajjoura[1].cord.x=1700 ; 
            hajjoura[2].cord.x = 2000;
            
            
            hero2.cord_mini_perso.x=790; 
            hero2.cord_mini_perso.y=474; 
            hero2.heart_image_cord.x=500 ; 
            tab[1].cord.y =340;
            tab[2].cord.x =800;
            tab[2].cord.y =85;
            tab_coin[0].stop=0 ;
            tab_coin[1].stop=0 ; 

            
        }   

        //

        // stage 3
            hero.pause = 0 ; 
            while (hero.game == 3 )
            {
               
                SDL_PollEvent(&ev);

                if (ev.type==SDL_QUIT)
                {
                    hero.game=0;
                }

                background.t_prev = SDL_GetTicks();    
                background.t_prev2 = SDL_GetTicks(); 
               

                frametime ++ ;
                hh ++ ; 

                if (hero.multy == 0)
                {
                    mission2(&hero , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime ,tab_coin  );
                }
                else if (hero.multy==1)
                {
                    mission2_multy(&hero,&hero2 , ev , &background ,screen ,tab , hajjoura , black_background ,&frametime , tab_coin );
                }


                if (hero.cord.x >1000 && hero.cord.x < 1300 ) 
                {
                    if ( hero.cord.x > tab[2].cord.x )
                    {
                        tab[2].direction = 1 ;
                        tab[2].cord.x ++ ; 
                        if (hero.heart_image_frame.y != 300  && hero.touch==0  && hh%200==0  )
                        {
                            hero.heart_image_frame.y +=75;
                            hero.touch=1;
                            printf("3ejja \n");
                            //SDL_Delay(500);
                            //printf("%d  \n",hero->health);
            
            
                        }
                        else if (hero.heart_image_frame.y==300)
                        {
                            hero.death=1;
                        }

                    }

                    if ( hero.cord.x < tab[2].cord.x )
                    {
                        tab[2].direction = 0 ;
                        tab[2].cord.x -- ; 
                        
                        if (hero.heart_image_frame.y != 300  && hero.touch==0 && hh%200==0 )
                        {
                            hero.heart_image_frame.y +=75;
                            hero.touch=1;
                            printf("3ejja \n");
                            //SDL_Delay(500);
                            //printf("%d  \n",hero->health);
            
            
                        }
                        else if (hero.heart_image_frame.y==300)
                        {
                            hero.death=1;
                        }
               

                    }
                  
                    
                }
                
             //   printf("%d \n",hero.cord.x);

                if (hero.cord.x >= 1300 && hero.cord.x <= 1500 && file_enigma_alea_rand == 0 )
                {
                    load_enigma_rand(&enigme_alea ,"enigma_alea.bin");

                    while (file_enigma_alea_rand != 1 )
                    {
                        SDL_WaitEvent(&ev);
                        enigma_nu_3( ev , &enigme_alea ,background_file_enigma , question , true_false,screen ,&file_enigma_alea_rand);

                        if (file_enigma_alea_rand== 1 )
                        {
                            hero.score += 1000 ; 
                            hero.game = 3 ; 
                        }
                        else if(file_enigma_alea_rand == -1 ) 
                        {
                            hero.score -=100 ; 
                            load_enigma_rand(&enigme_alea ,"enigma_alea.bin");
                            file_enigma_alea_rand = 0 ;

                        }

                    }

                }



                if ( hero.cord.x>= 1850 &&hero.cord.x<= 2000 && SW_enigma== 0 ) 
                {
                    SW_timer = 0 ;
                    while (SW_enigma!=1)
                    {
                        SW_timer ++ ;
                        frame_time_enigme_SW2 ++ ; 
                        frame_time_enigme_SW ++ ; 
                        SDL_PollEvent(&ev);
                        if (ev.type==SDL_QUIT)
                        {
                            hero.game=0;
                        }
                        
                        enigme_star_wars(&frame_time_enigme_SW , screen , &frame_time_enigme_SW2,&passe1 ,background_enigma_SW , 
                        &ship1 , &choix,&ship2 ,&mort , &score , &mort1 , &mort2 , ev , &direction ,&play,heart1 , heart2 , heart3 ,&SW_enigma);
                        if (SW_timer < 30000 )
                        {
                       //     hero.score += 10 ;
                
                        
                        }
                        else if (SW_timer >= 30000 && SW_timer <= 100000 ) 
                        {
                           // hero.score +=50 ; 
                   
                        
                        }
                        else if (SW_timer >= 100000)
                        {
                            //hero.score +=70 ; 
     
                   
                        }
                        else if (SW_timer == 150000)
                        {
             
                            SW_enigma = 1 ; 
                            
                           // hero.score +=100 ; 
                        }
                        
                    }
                    

                }



                if (SW_enigma == 1)
                {
                    hero.game = 4 ; 
                }
                



                background.dt = SDL_GetTicks() - background.t_prev ; 
                 background.dt2 = SDL_GetTicks() - background.t_prev2 ; 
            }
        
        // 


        if (hero.game == 4 )
        {
            end_game = IMG_Load("aa.png") ;
        }

        while (hero.game == 4 )
        {
            SDL_PollEvent(&ev);
            
            if (ev.type == SDL_MOUSEBUTTONUP ) 
            {
                if (ev.button.button == SDL_BUTTON_LEFT && ev.motion.x > 0 && ev.motion.x < 130 && ev.motion.y > 0 && ev.motion.y < 130)
                {
                    hero.game = -1 ; 
                }
                
            }
            
            SDL_BlitSurface(end_game , 0 , screen , 0 );
            SDL_Flip(screen);


        }
        
        

    }
    

    return 0 ;
}



































