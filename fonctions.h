#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Constantes.h"
/*Dans ce fichier on placera toutes les fonctions qui :
  A- Sont fonctionnels (et ne nescessite pas de modifications)
  B- Sont utilisée dans le programme
*/



/*Signatures*/

float Tir_directionx(int angle_lanceur);/*Fonction gérant le tir de la bulle presente dans le lanceur*/



float Tir_directiony(int angle_lanceur);



int Dessiner_balle_tiree(int directionx, int directiony, int couleur); /*fonction gerant le dessins de la bulle*/



void Reinitialiser_bulle();



int discretiser(double x); 



SDL_Rect initialiser_nb_bulle(int bub_array[BUB_NY][BUB_NX]);



/*void afficher_bulle_lanceur(int bub_array);*/



void Affichage(int bub_array[BUB_NY][BUB_NX], SDL_Rect nb_bulle[NB_BULLE], SDL_Rect rcSprite_Blue, int mouvement);/*gere l'affichage entier du jeu, fonction principale !*/

void remplissage();

int collision(float posx, float posy);

void placage_boules_contact(float posx, float posy);


void calcul_connexe(int j, int i);


void victoire();

void conversion_score(int Score);

void affichage_score();

void affichage_A(SDL_Rect pos_lettre);
void affichage_C(SDL_Rect pos_lettre);
void affichage_I(SDL_Rect pos_lettre);
void affichage_N(SDL_Rect pos_lettre);
void affichage_O(SDL_Rect pos_lettre);
void affichage_P(SDL_Rect pos_lettre);
void affichage_R(SDL_Rect pos_lettre);
void affichage_S(SDL_Rect pos_lettre);
void affichage_T(SDL_Rect pos_lettre);
void affichage_U(SDL_Rect pos_lettre);
void affichage_E(SDL_Rect pos_lettre);
void affichage_I(SDL_Rect pos_lettre);
void affichage_X(SDL_Rect pos_lettre);
void affichage_Y(SDL_Rect pos_lettre);
void affichage_P(SDL_Rect pos_lettre);

void ecrire_score();

void ecriture_score_save();
void lecture_score(FILE* scorefile);

void newgame();
void affichage_fl(SDL_Rect pos_lettre);
void restart();
void pause_disp();
#endif
