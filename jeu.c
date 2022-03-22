#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <pthread.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "jeu.h"
#include "constantes.h"


typedef struct{
int **carte1;
SDL_Surface*ecran1;
}listearg;

listearg liste;

double compteurbombelink=0;
double destructionRocherlink=0;
double ratiolink=1;



SDL_Surface *texte=NULL;
TTF_Font *police=NULL;
SDL_Color couleurNoire={0,0,0},couleurOr={255,215,0};
char score[20]="";




SDL_Rect positionbomberouge;

SDL_Rect positionbombe5;
SDL_Rect positionbombedroit5;
SDL_Rect positionbombegauche5;
SDL_Rect positionbombebas5;
SDL_Rect positionbombehaut5;
SDL_Rect positionbombecentre5;

SDL_Rect positionlinkwin;
SDL_Rect positionlinkdarkwin;



void UpdateClavier(Touches* etat_clavier){

SDL_Event event;
while(SDL_PollEvent(&event)){
switch(event.type){
case SDL_KEYDOWN :
etat_clavier->key[event.key.keysym.sym]=1;
break;

case SDL_KEYUP:
etat_clavier->key[event.key.keysym.sym]=0;
break;

default:
break;


}
}
}



SDL_Rect position , positionJoueur;
SDL_Rect positiondark , positionJoueurdark;

int continuer;

void jouer (SDL_Surface* ecran){


Touches etat_clavier;
memset(&etat_clavier,0,sizeof(etat_clavier));


SDL_Surface *linkwin=NULL;
SDL_Surface *linkdarkwin=NULL;


SDL_Surface *link[4]={NULL};
SDL_Surface *linkd[4]={NULL};



SDL_Surface *linkActuel=NULL;
SDL_Surface *linkdarkActuel=NULL;


SDL_Surface *mur=NULL;
SDL_Surface *rocher=NULL;

SDL_Rect positionFond;
SDL_Surface *fond=NULL;

SDL_Event event;


SDL_Surface *bombe=NULL;
SDL_Surface *bombedroit5=NULL;
SDL_Surface *bombegauche5=NULL;
SDL_Surface *bombebas5=NULL;
SDL_Surface *bombehaut5=NULL;
SDL_Surface *bombecentre5=NULL;



SDL_Surface *bomberouge=NULL;



continuer=1;
int i=0, j=0 ;

int **carte=(int **)malloc(11*sizeof(int*));
for(int i=0;i<11;i++)
    carte[i]=(int*)malloc(27*sizeof(int));


carte[0][0]=0;
carte[0][1]=0;
carte[0][2]=0;
carte[0][3]=0;
carte[0][4]=0;
carte[0][5]=0;
carte[0][6]=0;
carte[0][7]=0;
carte[0][8]=0;
carte[0][9]=0;
carte[0][10]=0;
carte[0][11]=0;
carte[0][12]=0;
carte[0][13]=0;
carte[0][14]=0;
carte[0][15]=0;
carte[0][16]=0;
carte[0][17]=0;
carte[0][18]=0;
carte[0][19]=0;
carte[0][20]=0;
carte[0][21]=0;
carte[0][22]=0;
carte[0][23]=0;
carte[0][24]=0;
carte[0][25]=0;
carte[0][26]=0;

carte[1][0]=0;
carte[1][1]=0;
carte[1][2]=0;
carte[1][3]=0;
carte[1][4]=0;
carte[1][5]=0;
carte[1][6]=0;
carte[1][7]=0;
carte[1][8]=0;
carte[1][9]=0;
carte[1][10]=0;
carte[1][11]=0;
carte[1][12]=0;
carte[1][13]=0;
carte[1][14]=0;
carte[1][15]=0;
carte[1][16]=0;
carte[1][17]=0;
carte[1][18]=0;
carte[1][19]=0;
carte[1][20]=0;
carte[1][21]=0;
carte[1][22]=0;
carte[1][23]=0;
carte[1][24]=0;
carte[1][25]=0;
carte[1][26]=0;

carte[2][0]=0;
carte[2][1]=0;
carte[2][2]=1;
carte[2][3]=1;
carte[2][4]=1;
carte[2][5]=1;
carte[2][6]=1;
carte[2][7]=1;
carte[2][8]=1;
carte[2][9]=1;
carte[2][10]=1;
carte[2][11]=1;
carte[2][12]=1;
carte[2][13]=1;
carte[2][14]=1;
carte[2][15]=1;
carte[2][16]=1;
carte[2][17]=1;
carte[2][18]=1;
carte[2][19]=1;
carte[2][20]=1;
carte[2][21]=1;
carte[2][22]=1;
carte[2][23]=1;
carte[2][24]=1;
carte[2][25]=1;
carte[2][26]=1;
carte[3][0]=0;
carte[3][1]=0;
carte[3][2]=1;
carte[3][3]=0;
carte[3][4]=0;
carte[3][5]=0;
carte[3][6]=0;
carte[3][7]=0;
carte[3][8]=0;
carte[3][9]=0;
carte[3][10]=0;
carte[3][11]=0;
carte[3][12]=0;
carte[3][13]=0;
carte[3][14]=0;
carte[3][15]=0;
carte[3][16]=0;
carte[3][17]=0;
carte[3][18]=0;
carte[3][19]=0;
carte[3][20]=0;
carte[3][21]=0;
carte[3][22]=0;
carte[3][23]=0;
carte[3][24]=0;
carte[3][25]=0;
carte[3][26]=1;
carte[4][0]=0;

carte[4][1]=0;
carte[4][2]=1 ;
carte[4][3]=0;
carte[4][4]=1;
carte[4][5]=1;
carte[4][6]=0;
carte[4][7]=1;
carte[4][8]=0;
carte[4][9]=0;
carte[4][10]=1;
carte[4][11]=0;
carte[4][12]=1;
carte[4][13]=1;
carte[4][14]=1;
carte[4][15]=0;
carte[4][16]=1;
carte[4][17]=0;
carte[4][18]=1;
carte[4][19]=1;
carte[4][20]=1;
carte[4][21]=0;
carte[4][22]=1;
carte[4][23]=1;
carte[4][24]=1;
carte[4][25]=0;
carte[4][26]=1;
carte[5][0]=0;
carte[5][1]=0;
carte[5][2]=1;
carte[5][3]=0;
carte[5][4]=1;
carte[5][5]=0;
carte[5][6]=0;
carte[5][7]=1;
carte[5][8]=1;
carte[5][9]=0;
carte[5][10]=1;
carte[5][11]=0;
carte[5][12]=1;
carte[5][13]=0;
carte[5][14]=0;
carte[5][15]=0;
carte[5][16]=1;
carte[5][17]=0;
carte[5][18]=1;
carte[5][19]=0;
carte[5][20]=1;
carte[5][21]=0;
carte[5][22]=1;
carte[5][23]=0;
carte[5][24]=0;
carte[5][25]=1;
carte[5][25]=0;
carte[5][26]=1;
carte[6][0]=0;
carte[6][1]=999;
carte[6][2]=0;

carte[6][3]=0;
carte[6][4]=1;
carte[6][5]=1;
carte[6][6]=0;
carte[6][7]=1;
carte[6][8]=0;
carte[6][9]=1;
carte[6][10]=1;
carte[6][11]=0;
carte[6][12]=1;
carte[6][13]=1;
carte[6][14]=1;
carte[6][15]=0;
carte[6][16]=1;
carte[6][17]=0;
carte[6][18]=1;
carte[6][19]=1;
carte[6][20]=1;
carte[6][21]=0;
carte[6][22]=1;
carte[6][23]=1;
carte[6][24]=1;
carte[6][25]=0;
carte[6][26]=0;
carte[7][0]=0;
carte[7][1]=0;
carte[7][2]=1;
carte[7][3]=0;
carte[7][4]=1;
carte[7][5]=0;
carte[7][6]=0;
carte[7][7]=1;
carte[7][8]=0;
carte[7][9]=0;
carte[7][10]=1;
carte[7][11]=0;
carte[7][12]=0;
carte[7][13]=0;
carte[7][14]=1;
carte[7][15]=0;
carte[7][16]=1;
carte[7][17]=0;
carte[7][18]=1;
carte[7][19]=0;
carte[7][20]=1;
carte[7][21]=0;
carte[7][22]=0;
carte[7][23]=0;
carte[7][24]=1;
carte[7][25]=0;
carte[7][26]=1;
carte[8][0]=0;
carte[8][1]=0;
carte[8][2]=1;
carte[8][3]=0;
carte[8][4]=1;

carte[8][5]=1;
carte[8][6]=0;
carte[8][7]=1;
carte[8][8]=0;
carte[8][9]=0;
carte[8][10]=1;
carte[8][11]=0;
carte[8][12]=1;
carte[8][13]=1;
carte[8][14]=1;
carte[8][15]=0;
carte[8][16]=1;
carte[8][17]=0;
carte[8][18]=1;
carte[8][19]=0;
carte[8][20]=1;
carte[8][21]=0;
carte[8][22]=1;
carte[8][23]=1;
carte[8][24]=1;
carte[8][25]=0;
carte[8][26]=1;
carte[9][0]=0;
carte[9][1]=0;
carte[9][2]=1;
carte[9][3]=0;
carte[9][4]=0;
carte[9][5]=0;
carte[9][6]=0;
carte[9][7]=0;
carte[9][8]=0;
carte[9][9]=0;
carte[9][10]=0;
carte[9][11]=0;
carte[9][12]=0;
carte[9][13]=0;
carte[9][14]=0;
carte[9][15]=0;
carte[9][16]=0;
carte[9][17]=0;
carte[9][18]=0;
carte[9][19]=0;
carte[9][20]=0;
carte[9][21]=0;
carte[9][22]=0;
carte[9][23]=0;
carte[9][24]=0;
carte[9][25]=0;
carte[9][26]=1;
carte[10][0]=0;
carte[10][1]=0;
carte[10][2]=1;
carte[10][3]=1;
carte[10][4]=1;
carte[10][5]=1;
carte[10][6]=1;
carte[10][7]=1;

carte[10][8]=1;
carte[10][9]=1;
carte[10][10]=1;
carte[10][11]=1;
carte[10][12]=1;
carte[10][13]=1;
carte[10][14]=1;
carte[10][15]=1;
carte[10][16]=1;
carte[10][17]=1;
carte[10][18]=1;
carte[10][19]=1;
carte[10][20]=1;
carte[10][21]=1;
carte[10][22]=1;
carte[10][23]=1;
carte[10][24]=1;
carte[10][25]=1;
carte[10][26]=1;


linkwin=IMG_Load("win1.bmp");
linkdarkwin=IMG_Load("win2.bmp");

fond=IMG_Load("map2.bmp");

mur=IMG_Load("mur.bmp");
rocher=IMG_Load("rocher.bmp");


bombe=IMG_Load("bombe.bmp");
bombecentre5=IMG_Load("bcenter.bmp");
bombegauche5=IMG_Load("bleft.bmp");
bombedroit5=IMG_Load("bright.bmp");
bombehaut5=IMG_Load("bup.bmp");
bombebas5=IMG_Load("bdown.bmp");


bomberouge=IMG_Load("bomberouge.bmp");


link[BAS]=IMG_Load("link0.bmp");
link[GAUCHE]=IMG_Load("link1.bmp");
link[HAUT]=IMG_Load("link3.bmp");
link[DROITE]=IMG_Load("link2.bmp");



linkd[BAS]=IMG_Load("linkb0.bmp");
linkd[GAUCHE]=IMG_Load("linkb1.bmp");
linkd[HAUT]=IMG_Load("linkb3.bmp");
linkd[DROITE]=IMG_Load("linkb2.bmp");







linkActuel=link[BAS];
linkdarkActuel=linkd[BAS];


positionJoueur.x=3;
positionJoueur.y=3;
carte[3][3]=LINK;


positionJoueurdark.x=5;
positionJoueurdark.y=3;
carte[3][5]=LINKD;


placement_aleatoire_rocher(carte);

ratiolink=1;

TTF_Init();

police=TTF_OpenFont("Triforce.ttf",26);
sprintf(score,"%.2f :LINK",ratiolink);
texte=TTF_RenderText_Blended(police,score,couleurOr);

while(continuer==1){
{
UpdateClavier(&etat_clavier);

if(etat_clavier.key[SDLK_UP]){
linkActuel=link[HAUT];
deplacerJoueur(carte,&positionJoueur,HAUT);
}
if(etat_clavier.key[SDLK_DOWN]){
linkActuel=link[BAS];
deplacerJoueur(carte,&positionJoueur,BAS);
}
if(etat_clavier.key[SDLK_RIGHT]){
linkActuel=link[DROITE];
deplacerJoueur(carte,&positionJoueur,DROITE);
}
if(etat_clavier.key[SDLK_LEFT]){
linkActuel=link[GAUCHE];
deplacerJoueur(carte,&positionJoueur,GAUCHE);
}
if(etat_clavier.key[SDLK_m]){
creation_bombe(carte ,ecran);
}






if(etat_clavier.key[SDLK_z]){
linkdarkActuel=linkd[HAUT];
deplacerJoueur(carte,&positionJoueurdark,HAUT);
}
if(etat_clavier.key[SDLK_s]){
linkdarkActuel=linkd[BAS];
deplacerJoueur(carte,&positionJoueurdark,BAS);
}
if(etat_clavier.key[SDLK_d]){
linkdarkActuel=linkd[DROITE];
deplacerJoueur(carte,&positionJoueurdark,DROITE);
}
if(etat_clavier.key[SDLK_q]){
linkdarkActuel=linkd[GAUCHE];
deplacerJoueur(carte,&positionJoueurdark,GAUCHE);
}

if(etat_clavier.key[SDLK_ESCAPE]){
continuer=0;
}

}

SDL_FillRect(ecran , NULL ,SDL_MapRGB(ecran->format,255,255,255)) ;

positionFond.x=0;
positionFond.y=0;
SDL_BlitSurface(fond,NULL,ecran,&positionFond);



for(i=0;i<11;i++){
    for(j=0;j<27;j++){
        position.x=j*TAILLE_BLOC;
        position.y=i*TAILLE_BLOC;


        switch(carte[i][j]){
        case MUR :
        SDL_BlitSurface(mur,NULL,ecran,&position);
        break;
        case ROCHER :
        SDL_BlitSurface(rocher,NULL,ecran,&position);
        break;

        case BOMBE :
        SDL_BlitSurface(bombe,NULL,ecran,&position);
        break;
        case BOMBEROUGE :
        SDL_BlitSurface(bomberouge,NULL,ecran,&position);
        break;
        case BOMBECENTRE5 :
        SDL_BlitSurface(bombecentre5,NULL,ecran,&position);
        break;
        case BOMBEBAS5 :
        SDL_BlitSurface(bombebas5,NULL,ecran,&position);
        break;
        case BOMBEHAUT5:
        SDL_BlitSurface(bombehaut5,NULL,ecran,&position);
        break;
        case BOMBEDROIT5 :
        SDL_BlitSurface(bombedroit5,NULL,ecran,&position);
        break;
        case BOMBEGAUCHE5 :
        SDL_BlitSurface(bombegauche5,NULL,ecran,&position);
        break;

}

}
}


position.x=positionJoueur.x*TAILLE_BLOC;
position.y=positionJoueur.y*TAILLE_BLOC;
SDL_BlitSurface(linkActuel,NULL,ecran,&position);

positiondark.x=positionJoueurdark.x*TAILLE_BLOC;
positiondark.y=positionJoueurdark.y*TAILLE_BLOC;
SDL_BlitSurface(linkdarkActuel,NULL,ecran,&positiondark);

usleep(40000);


position.x=200;
position.y=3;
SDL_BlitSurface(texte,NULL,ecran,&position);

SDL_Flip(ecran);

}


if(continuer==5){
Mix_CloseAudio();
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
Mix_Music *gagner;
gagner=Mix_LoadMUS("gagner.mp3");
Mix_PlayMusic(gagner,0);
positionlinkwin.x=45;
positionlinkwin.y=8;
SDL_BlitSurface(linkwin,NULL,ecran,&positionlinkwin);
SDL_Flip(ecran);
sleep(14);
continuer=0;
}

if(continuer==6){
Mix_CloseAudio();
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
Mix_Music *gagner;
gagner=Mix_LoadMUS("gagner.mp3");
Mix_PlayMusic(gagner,0);
positionlinkdarkwin.x=45 ;
positionlinkdarkwin.y=8 ;
SDL_BlitSurface(linkdarkwin,NULL,ecran,&positionlinkdarkwin);
SDL_Flip(ecran);
sleep(14);
continuer=0;
}




SDL_EnableKeyRepeat(0,0);

SDL_FreeSurface(mur);
SDL_FreeSurface(rocher);

for(i=0;i<4;i++){
SDL_FreeSurface(link[i]);
}

for(i=0;i<4;i++){
SDL_FreeSurface(linkd[i]);
}

SDL_FreeSurface(bombe);
SDL_FreeSurface(bombecentre5);
SDL_FreeSurface(bombegauche5);
SDL_FreeSurface(bombedroit5);
SDL_FreeSurface(bombehaut5);
SDL_FreeSurface(bombebas5);

SDL_FreeSurface(bomberouge);

SDL_FreeSurface(linkwin);
SDL_FreeSurface(linkdarkwin);




}



void deplacerJoueur(int **carte,SDL_Rect *pos , int direction){

switch(direction){
case HAUT:
if(carte[pos->y-1][pos->x]==MUR)
break;
if(carte[pos->y-1][pos->x]==ROCHER)
break;

pos->y--;
break;
case BAS:
if(carte[pos->y+1][pos->x]==MUR)
break;
if(carte[pos->y+1][pos->x]==ROCHER)
break;

pos->y++;
break;
case GAUCHE:
if(positionJoueur.x==2 && positionJoueur.y==6 && carte[6][26]==3){
break;}
if(positionJoueurdark.x==2 && positionJoueurdark.y==6 && carte[6][26]==3){
break;}



if(positionJoueur.x==2 && positionJoueur.y==6){
  positionJoueur.x=25 ;
  positionJoueur.y=6;
  break;
}
if(positionJoueurdark.x==2 && positionJoueurdark.y==6){
  positionJoueurdark.x=25 ;
  positionJoueurdark.y=6;
  break;
}


if(carte[pos->y][pos->x-1]==MUR)
break;
if(carte[pos->y][pos->x-1]==ROCHER)
break;

pos->x--;
break;


case DROITE:
if(positionJoueur.x==26 && positionJoueur.y==6 && carte[6][2]==3){
break;}
if(positionJoueurdark.x==26 && positionJoueurdark.y==6 && carte[6][2]==3){
break;}


if(positionJoueur.x==25 && positionJoueur.y==6){
  positionJoueur.x=2 ;
  positionJoueur.y=6;
  break;}
if(positionJoueurdark.x==25 && positionJoueurdark.y==6){
  positionJoueurdark.x=2 ;
  positionJoueurdark.y=6;
  break;}


if(carte[pos->y][pos->x+1]==MUR)
break;
if(carte[pos->y][pos->x+1]==ROCHER)
break;

pos->x++;
break;


}

}



void placement_aleatoire_rocher(int **carte ){
    int a=0 , b=0 ;
    for(a=3 ; a<11 ; a++){
    srand(time(NULL));
    for(b=2 ; b<28 ; b++){
        if(carte[a][b]==0 && carte[a][b]!=LINK){
        int v=rand()%3;
        if(v==0){
            carte[a][b]=ROCHER;
        }

        }


    }
    }


for(a=3 ; a<11 ; a++){
    for(b=2 ; b<28 ; b++){
    if(carte[a][b]==LINK){
        if(carte[a+1][b]==3){
        carte[a+1][b]=0;
        }
        if(carte[a-1][b]==3){
        carte[a-1][b]=0;
        }
        if(carte[a][b+1]==3){
        carte[a][b+1]=0;
        }
        if(carte[a][b-1]==3){
        carte[a][b-1]=0;
        }
    }

    }
    }


}





void creation_bombe(int **carte , SDL_Surface* ecran){

pthread_t thread1;

liste.carte1=carte;
liste.ecran1=ecran;

pthread_create(&thread1,NULL,gestion_bombe,(void*)&liste);

}


void *gestion_bombe(void*arg){


int fin;


listearg *args=(listearg*)arg;
int **carte1=args-> carte1;

int a ,b=0;
for(a=2;a<11;a++){
for(b=2;b<27;b++){
if(carte1[a][b]==BOMBE ||carte1[a][b]==BOMBEROUGE ){
pthread_exit(NULL);

}
}
}



carte1[positionJoueur.y][positionJoueur.x]=BOMBE;

if(carte1[positionJoueur.y][positionJoueur.x]==BOMBE){
compteurbombelink=compteurbombelink+1;
}



usleep(200000);

Mix_AllocateChannels(32);
Mix_Chunk *bruitbombe;
bruitbombe=Mix_LoadWAV("bombeson.mp3");
Mix_PlayChannel(2,bruitbombe,0);

for(a=2;a<11;a++){
for(b=2;b<27;b++){
if(carte1[a][b]==BOMBE){
if(carte1[a][b-1]==ROCHER){
destructionRocherlink=destructionRocherlink+1;
}
if(carte1[a][b+1]==ROCHER){
destructionRocherlink=destructionRocherlink+1;
}
if(carte1[a-1][b]==ROCHER){
destructionRocherlink=destructionRocherlink+1;
}
if(carte1[a][b]==ROCHER){
destructionRocherlink=destructionRocherlink+1;
}




}
}}


for(a=2;a<11;a++){
for(b=2;b<27;b++){
if(carte1[a][b]==BOMBE){
carte1[a][b]=BOMBEROUGE;
usleep(200000);
carte1[a][b]=BOMBE;
usleep(200000);
carte1[a][b]=BOMBEROUGE;
usleep(200000);
carte1[a][b]=BOMBE;
usleep(200000);
}
}
}




for(a=2;a<11;a++){
for(b=2;b<27;b++){
if(carte1[a][b]==BOMBE){

carte1[a][b]=BOMBECENTRE5;

  if(carte1[a][b]==carte1[positionJoueur.y][positionJoueur.x]){
   fin=1;
   }  if(carte1[a][b]==carte1[positionJoueurdark.y][positionJoueurdark.x]){
   fin=2;
   }








    if(carte1[a+1][b]!=MUR){
    carte1[a+1][b]=BOMBEBAS5;
    }
    if(carte1[a+1][b]==carte1[positionJoueur.y][positionJoueur.x]){
    carte1[a+1][b]=BOMBEBAS5;
    fin=2;
    }
    if(carte1[a+1][b]==carte1[positionJoueurdark.y][positionJoueurdark.x]){
    carte1[a+1][b]=BOMBEBAS5;
    fin=1;
    }
    if(carte1[a+1][b]==ROCHER){
    carte1[a+1][b]=BOMBEBAS5;
    }

    ///////////////

    if(carte1[a-1][b]!=MUR){
    carte1[a-1][b]=BOMBEHAUT5;
    }
    if(carte1[a-1][b]==carte1[positionJoueur.y][positionJoueur.x]){
    carte1[a-1][b]=BOMBEHAUT5;
    fin=2;
    }
    if(carte1[a-1][b]==carte1[positionJoueurdark.y][positionJoueurdark.x]){
    carte1[a-1][b]=BOMBEHAUT5;
    fin=1;
    }
    if(carte1[a-1][b]==ROCHER){
    carte1[a-1][b]=BOMBEHAUT5;
    }



    if(carte1[a][b+1]!=MUR){
    carte1[a][b+1]=BOMBEDROIT5;
    }
    if(carte1[a][b+1]==carte1[positionJoueur.y][positionJoueur.x]){
    carte1[a][b+1]=BOMBEDROIT5;
    fin=2;
    }
    if(carte1[a][b+1]==carte1[positionJoueurdark.y][positionJoueurdark.x]){
    carte1[a][b+1]=BOMBEDROIT5;
    fin=1;
    }
    if(carte1[a][b+1]==ROCHER){
    carte1[a][b+1]=BOMBEDROIT5;
    }


    if(carte1[a][b-1]!=MUR){
    carte1[a][b-1]=BOMBEGAUCHE5;
    }
    if(carte1[a][b-1]==carte1[positionJoueur.y][positionJoueur.x]){
    carte1[a][b-1]=BOMBEGAUCHE5;
    fin=2;
    }
    if(carte1[a][b-1]==carte1[positionJoueurdark.y][positionJoueurdark.x]){
    carte1[a][b-1]=BOMBEGAUCHE5;
    fin=1;
    }
    if(carte1[a][b-1]==ROCHER){
    carte1[a][b-1]=BOMBEGAUCHE5;
    }




    }



}
}


usleep(200000);

ratiolink=destructionRocherlink/compteurbombelink;
sprintf(score,"%.2f :LINK",ratiolink);
texte=TTF_RenderText_Blended(police,score,couleurOr);


for(a=2;a<11;a++){
for(b=2;b<27;b++){
if(carte1[a][b]==BOMBECENTRE5){
carte1[a][b]=0;
}
if(carte1[a][b]==BOMBEHAUT5){
carte1[a][b]=0;
}
if(carte1[a][b]==BOMBEDROIT5){
carte1[a][b]=0;
}
if(carte1[a][b]==BOMBEGAUCHE5){
carte1[a][b]=0;
}
if(carte1[a][b]==BOMBEBAS5){
carte1[a][b]=0;
}

}
}


if(fin==1){
continuer=5;
}
if(fin==2){
continuer=6;
}




pthread_exit(NULL);



}







