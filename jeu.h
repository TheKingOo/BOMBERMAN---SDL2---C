#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

typedef struct{
int key[SDLK_LAST];
}
Touches;

void creation_bombe(int **carte , SDL_Surface* ecran);
void *gestion_bombe(void*arg);
void UpdateClavier(Touches* etat_clavier);
void jouer(SDL_Surface* ecran);
void deplacerJoueur(int **carte,SDL_Rect *pos , int direction);
void placement_aleatoire_rocher(int **carte );

#endif // JEU_H_INCLUDED
