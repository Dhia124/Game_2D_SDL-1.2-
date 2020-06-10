#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<string.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include"header.h"


int main()
{
    perso_hero x ;
    entite_secondaire tab[2];
    hajra hajj[2];
    fond_ecran f ;

    FILE *fp = NULL ; 
    fp= fopen("hero.bin","rb");
    fread(&x, sizeof( perso_hero), 1, fp); 
    printf("%d  %d \n",x.cord.x,x.game);
    fclose(fp);

    fp= fopen("back.bin","rb");
    fread(&f, sizeof( fond_ecran), 1, fp); 
    printf("camera :  %d \n",f.camera.x);
    fclose(fp);

    //load(x ,tab, f, hajj, "hero.bin");
    //printf("%d \n",x.cord.x);


    return 0 ;
}






















