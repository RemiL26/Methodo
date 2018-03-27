#ifndef CONSTANTES_H
#define CONSTANTES_H


/*Fichiers contenant les constantes utilisées dans le programme*/
#define SCREEN_WIDTH  720
#define SCREEN_HEIGHT 540
#define SPRITE_SIZE     32
#define SPRITE_HEIGHT 45*157 /*La hauteur de notre sprite (ici; le lanceur)*/
#define MIDDLE_HEIGHT_ARROW SPRITE_HEIGHT/2 /*Le milieux de notre sprite 5le lanceur), qui equivaut a son milieu d'animation*/
#define BUBBLE_SPRITE_HEIGHT 960
#define PI 3.14159265359 /*la precision est relative mais devrais suffire au projet*/
#define MUR_GAUCHE 200.  /*le mur gauche de notre ecran */
#define MUR_DROIT 520. /*le mur droit de notre ecran*/
#define PLAFOND 30. /*le plafond de notre ecran*/
#define CENTRE_LANCEUR_X (SCREEN_WIDTH/2)-20 /*le centre de l'ecran pour la bulle du lanceur -abcisse-*/
#define CENTRE_LANCEUR_Y 459 /*le centre de l'ecran pour la bulle du lanceur -ordonnée-*/
#define BUB_NX 8             /*bulle max a l'horizontale*/
#define BUB_NY 11            /*bulle max a la verticale*/
#define BUB_SIZE 40 /*taille des bulle*/
#define NB_BULLE 100 /*nombre max de bulle*/
#define ALPHA 0.87 /*permet aux bulles de se "faufiler" entre elles*/
#define NUM_COLORS 8








/*variables globale*/

SDL_Surface *temp, *sprite, *grass, *wheel, *gear;
SDL_Rect rcGrass;


SDL_Rect Tableau_Bulles_Lancees[90];
int nombre_bulle_lancees;
int longueur;
int compteur;
int gameover;
int couleur;
int nvcouleur;
int egale;
int score;
int empty;
int Temps_animation, Temps_etat;
float Mouvement_x;
SDL_Surface *bub[NUM_COLORS];



SDL_Surface *bubble_blue;
SDL_Surface *bubble_yellow;
SDL_Surface *bubble_green;
SDL_Surface *bubble_white;
SDL_Surface *bubble_pink;
SDL_Surface *bubble_red;
SDL_Surface *bubble_black;
SDL_Surface *bubble_Orange;

int angle_lanceur,angle_lanceur2, rotation_angle; /*l'angle du lanceur est la position du lanceur au moment t et est comprise entre [-22,22]*/
/*rotation_angle gere l'incrementation de angle_lanceur a chaque mouvement et est toujours de 1 mais par soucis de lisibilité je prefere passer par une variable*/

float directionx, directiony; /*les direction horizontale et verticale de notre bulle calculée par les fonctions éponymes*/

int mouvement; /*booléen, prenant soit 0 soit 1, et gere si la bulle rencontre un obstacle (mur, autre bulle) ou non*/

/* source and destination rectangles */
SDL_Rect rcSrc, rcSprite, rcWheel,rcSrc_Wheel, rcGear, rcSrc_Gear, pos_score, pos_lettre;
SDL_Surface *screen;

/* Rectangle source et destination pour les sprite de nos bulles*/
SDL_Rect rcSrc_Blue, rcSprite_Blue, rcSprite_Yellow, rcSprite_Green, rcSprite_White, rcSprite_Pink, rcSprite_Red, rcSprite_Black, rcSprite_Orange;


/*tableau d'entier bulle*/
int bub_array[BUB_NY][BUB_NX];
int bub_array_centers[BUB_NY][BUB_NX];
SDL_Rect nb_bulle[NB_BULLE];
int bub_connected_component[BUB_NY][BUB_NX];

/* GESTION DU SCORE */
SDL_Surface *Chiffre;
int Tab_Score[10];
int Score;
SDL_Rect rcSrc_Chiffre[15];
int newscore;



/* GESTION DES LETTRES */
SDL_Surface *Lettre;
SDL_Rect rcSrc_Lettre[26];
int new_game;
int desc;
int rest;
int pause;

/*Gestion de la sauvegarde*/
FILE* score_save = NULL;


#endif
