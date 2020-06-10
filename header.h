#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<string.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>

 /**
* @struct posf
* @brief struct for position
*/
typedef struct 
{ 
    float x ; 
    float y ; 
    float w ; 
    float h ; 
}posf; 
/**
* @struct coin
* @brief struct for coin
*/
typedef struct 
{
SDL_Surface *coin ; 
SDL_Rect cord_coin ;  
int stop ;
int byby ; 
int cycy ; 
}coin ;



/**
* @struct perso_hero
* @brief struct for our hero
*/
typedef struct 
{

    SDL_Surface *save ; 
    SDL_Rect save_cord , save_frame ; 



    int multy ;
    int game_state ; 

    int enigma  ; 
    // 13

    double speed , acc ;//
    int  key_press_up_down , key_press_right_left , key_touch ; 
    
    int death , pause  ; //
    SDL_Surface *heart_image ; 
    SDL_Rect heart_image_cord ; 
    SDL_Rect heart_image_frame ; 

    int damage;
    SDL_Surface *sprite;

    int first_entry_jump;//
    
    

    SDL_Rect cord_origin_axis ; 

    SDL_Surface *attack_ball ;
    SDL_Rect ball_cord ;
    int attack_state;
    int attack ;

    SDL_Rect cord;//
    SDL_Rect frame;
    int direction;
    int is_running;
    int collision_state;
    int touch ;    
    int coeff_sprite;
    int mvt; 
    SDL_Rect initial_altitude,max_jump;

    SDL_Surface *mini_perso ;
    posf cord_mini_perso ; 

    int load , game ; 



    TTF_Font *font ; 


    // score 
    int score ; 
    SDL_Rect cord_score ; 
    SDL_Surface *image_score;
    TTF_Font *font_score ; 
    char score_text[20];

    double zoom ; 
int coin ;

}perso_hero;
/**
* @struct entite_secondaire
* @brief struct for entite_secondaire
*/
typedef struct 
{
    int health ,stop,coef; 
    SDL_Rect cord,old_cord ; 
    int num;
    SDL_Rect frame ; 
    SDL_Surface *sprite;
    int direction;
    int death ; 

    int value ; 
    int first_collect;

}entite_secondaire;

/**
* @struct fond_ecran
* @brief struct for background
*/

typedef struct 
{
    SDL_Surface *backk , *backk2;
    SDL_Surface *backk_entit_sec ,*backk_entit_sec2; 
    SDL_Rect camera ,camera2 ;
    
    int scroll_count ; 
    int scroll_state;

    SDL_Rect pos_cam2 ,pos_cam1; 

    SDL_Surface *mini_map;
    SDL_Rect cord_min_map ;
      SDL_Surface *mini_map2;
    SDL_Rect cord_min_map2 ;

    Uint32 t_prev , dt ,t_prev2 , dt2 ; 

}fond_ecran;
/**
* @struct hajra
* @brief struct for hajra
*/
typedef struct 
{
    SDL_Surface *image ;
    SDL_Rect cord ; 
    int fall_state ;    
}hajra;
/**
* @struct flous
* @brief struct for flous
*/
typedef struct 
{
    int value , first_collect ; 
    SDL_Rect cord ; 
    

}flous;



void collision_tah(perso_hero *hero, SDL_Surface *x_background,SDL_Rect *camera );

    void save_hero(perso_hero *hero , char file_name[]);
    void save_back(fond_ecran *y,char file_name[]);
    void load_back(fond_ecran *y, char file_name[]);
    void load_hero(perso_hero *hero ,char file_name[]);
    void save_all (perso_hero *hero, fond_ecran *y);
    void load_all (perso_hero *hero, fond_ecran *y);

void pause(SDL_Event ev , perso_hero *hero , SDL_Surface *screen,fond_ecran *background);
void show_score2(SDL_Surface *ecran, int score );

void show_score(SDL_Surface *ecran, int score );
void init_stage2(perso_hero *hero, entite_secondaire tab[], hajra hajjoura[], fond_ecran *background, SDL_Surface *black_background, int *frametime);
void init_stage1(perso_hero *hero , entite_secondaire tab[],hajra hajjoura[],fond_ecran *background,SDL_Surface *black_background,int *frametime);
void collision_surface2(SDL_Surface *black_background,perso_hero *hero);
void refresh2_player1(perso_hero hero, entite_secondaire tab[], hajra tab_hjarr[], fond_ecran *x_background, SDL_Surface *x_screen, coin tab_coin[]);


void animation_coin(entite_secondaire *coin);
int  collision_coin(perso_hero *hero,coin *ennemy );
void collision_hajjoura(perso_hero *hero,hajra *hajjoura , fond_ecran *x_background);

void hero_movment2(perso_hero *hero , SDL_Event ev);

void mission2(perso_hero *hero , SDL_Event ev , fond_ecran *background , SDL_Surface *screen ,entite_secondaire tab[] , hajra hajjoura[] , SDL_Surface *black_background , int *frametime ,coin tab_coin[]  );


void control_gestion_vie_score(perso_hero *hero , fond_ecran *background );

void collision_attack(perso_hero *hero,entite_secondaire *ennemy );

void hero_attack(perso_hero *hero );
void animation_entite_sec(entite_secondaire *ennemy);

void hero_movment(perso_hero *hero , SDL_Event ev,fond_ecran *x_background,SDL_Surface *x_screen ,entite_secondaire *test,hajra tab_hajar[],coin tab_coin[]);
void update_ennemy_cord(entite_secondaire *ennemy ,fond_ecran *x_background);

void animation_hero(perso_hero *hero);

int collision(perso_hero *hero, SDL_Surface *x_background  );
void collision_ennemy(perso_hero *hero, entite_secondaire *ennemy,fond_ecran *x_background);
void refresh(perso_hero hero , entite_secondaire tab[],hajra tab_hjarr[] ,fond_ecran *x_background,SDL_Surface *x_screen,coin tab_coin[]);
void mvt_alea_entite_secondaire(entite_secondaire *ent,int X_min,int X_max);

void everything (perso_hero *hero,SDL_Event ev , fond_ecran *background , SDL_Surface *screen ,entite_secondaire tab[], hajra hajjoura[] ,SDL_Surface *black_background,coin tab_coin[] );

void hero_speed(perso_hero *hero, SDL_Rect *x_camera,int camera , double dt );

void collision_surface(SDL_Surface *black_background,perso_hero *hero);

void update_hero_cord(perso_hero *hero,fond_ecran *x_background);
SDL_Color GetPixel(SDL_Surface *x_background,int x,int y);
void rocks_fall (hajra *x );

void tictactoe(int *first_time, int *game_state , int mat[][3], int *tour ,SDL_Surface *o_image ,
SDL_Surface *x_image , SDL_Surface *screen , SDL_Event ev , SDL_Surface *backgroundimage , SDL_Surface *texte_nothing,SDL_Surface *texte_win , 
SDL_Surface *texte_loss , SDL_Rect textelPosition , int *enigma_solved );

int verif_game_loop(int mat[][3]);
int pos(int x, int y, SDL_Surface *o, SDL_Surface *screen, int mat[][3]);
int pos2(int x, int y, SDL_Surface *o, SDL_Surface *screen, int mat[][3]);



void initi_enigma_dhia(SDL_Surface *background , SDL_Surface *screen , SDL_Surface *initial ,SDL_Surface *heart1 , SDL_Rect posanswer , int *enigma_solved  );

void enigme_dhia(SDL_Event ev , int *try , SDL_Surface *background , SDL_Surface *screen , SDL_Surface *wrong_answer1 , SDL_Surface *wrong_answer2 , SDL_Surface *wrong_answer3 , SDL_Surface *right_answer ,int *done , SDL_Rect posanswer ,int *enigma_solved , SDL_Surface *heart1 , SDL_Surface *heart2 ,SDL_Surface *heart3 );


//
/**
* @struct ship_enigme
* @brief struct for enigme
*/

typedef struct 
{
    SDL_Rect cord ; 
    SDL_Surface *image ; 
    int health ,end; 
}ship_enigme;

void blit_ennemy_ligne_1(SDL_Surface *screen , SDL_Surface *x_background,ship_enigme *x,int *pass,ship_enigme *x2,int *mort,int *score);
void blit_ennemy_ligne_2(SDL_Surface *screen , SDL_Surface *x_background,ship_enigme *x,int *pass,ship_enigme *x2,int *mort,int *score) ;
void blit_ennemy_ligne_3(SDL_Surface *screen , SDL_Surface *x_background,ship_enigme *x,int *pass,ship_enigme *x2,int *mort,int *score); 
void refresh_2 (int *passe,SDL_Surface *screen , SDL_Surface *x_background,ship_enigme *x,int *choix,ship_enigme *x2,int *mort,int *score,int*mort1,int*mort2); 
void refresh_hero(SDL_Event ev,SDL_Surface *screen ,SDL_Surface *background,ship_enigme *ship2,int *deriction,int *play); 

void enigme_star_wars(int *frame_time_enigme_SW , SDL_Surface *screen , int *frame_time_enigme_SW2,int *passe1 , SDL_Surface *background , 
ship_enigme *ship1 , int *choix,ship_enigme *ship2 , int *mort , int *score , int *mort1 , int *mort2 , SDL_Event ev , int *direction ,int *play,
SDL_Surface *c1 , SDL_Surface *c2 , SDL_Surface *c3 , int *SW_enigma );

//

//
/**
* @struct enigma
* @brief struct for enigme
*/

typedef struct 
    {
        char question[30];
        char background[30];
        char true_false[30];
        int user_input ; 
        SDL_Rect question_cord , question_frame , true_false_frame;
        int question_solve  ; 

    }enigma;

void load_enigma_rand(enigma *x , char file_name[]);
void initi_enigma_rand( enigma *x , char file_name[]);
void enigma_nu_3(SDL_Event ev , enigma *enigme_alea ,SDL_Surface *background_file_enigma , 
    SDL_Surface *question , SDL_Surface *true_false,SDL_Surface *screen ,int *test);


//


//
void menu(SDL_Event ev , SDL_Rect menu1_frame , perso_hero *hero ,SDL_Surface *menu1 ,SDL_Surface *screen , 
        SDL_Rect *menu2_frame ,int *window , SDL_Surface *menu2 );

void settings(SDL_Event ev ,SDL_Rect *menu2_frame , perso_hero *hero ,SDL_Surface *screen,int *window);


void init_stage3(perso_hero *hero , entite_secondaire tab[],hajra hajjoura[],fond_ecran *background,SDL_Surface *black_background,int *frametime);

void blit_mini_map(SDL_Surface * screen , SDL_Surface * mini_perso , posf *position  ) ;

//


// multy 

void mission2_multy(perso_hero *hero,perso_hero *hero2 , SDL_Event ev , fond_ecran *background , SDL_Surface *screen ,entite_secondaire tab[] , 
    hajra hajjoura[] , SDL_Surface *black_background , int *frametime ,coin tab_coin[]  );

void everything2 (perso_hero *hero,perso_hero *hero2,SDL_Event ev , fond_ecran *background , SDL_Surface *screen ,entite_secondaire tab[], hajra hajjoura[] ,SDL_Surface *black_background,coin tab_coin[] );
void control_gestion_vie_score2(perso_hero *hero , fond_ecran *background );

void refresh2(perso_hero hero , entite_secondaire tab[],hajra tab_hjarr[] ,fond_ecran *x_background,SDL_Surface *x_screen,coin tab_coin[]);
void hero_movment2_player2(perso_hero *hero , SDL_Event ev,fond_ecran *x_background,SDL_Surface *x_screen ,entite_secondaire tab[],hajra tab_hajar[],coin tab_coin[]);

void hero_movment2_player1(perso_hero *hero , SDL_Event ev,fond_ecran *x_background,SDL_Surface *x_screen ,entite_secondaire tab[],hajra tab_hajar[],coin tab_coin[]);











//



