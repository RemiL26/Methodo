#ifndef TABLEAU_BULLES_H
#define TABLEAU_BULLES_H

/***********************************/
/*Type abstrait : tableau de bulles*/
/*******Nom : Tableau_Bulles********/
/*par Funck Yohan et Lallemand Remy*/
/***********************************/


/*************************/
/*    Librarie utile     */
/*************************/

#include "SDL.h"   
#include <stdbool.h>

/******************************/
/* Definition de la structure */
/******************************/

/* un tableau de bulle est une structure composée de :
 * un champs premier contenant un SDL_Rect
 * un champs reste contenant l'adresse du prochain tableau de bulles
 */

struct Tableau_Bulles
{
  SDL_Rect prem;
  struct Tableau_Bulles * reste;
};

/********************************/
/* Definition du type Tab_B     */
/********************************/

typedef struct Tableau_Bulles * Tab_B;

/*****************************/
/* Prototypes de la fonction */
/*****************************/

/* Constructeurs */

Tab_B nouveau_Tableau_vide(void);


Tab_B Ajouter_Bulle_Tableau(SDL_Rect Bulle, Tab_B Tableau_de_Bulles);

Tab_B Copier_Bulle_Tableau(Tab_B Tableau_de_Bulles);

/* Fonction accès */
Tab_B Reste_Tableau(Tab_B Tableau_de_Bulles);

bool Est_vide_Tableau(Tab_B Tableau_de_Bulles);

SDL_Rect Premiere_Bulle(Tab_B Tableau_de_Bulles);

int Longeur_Tableau(Tab_B Bulles, int compteur);



/* Operations non primitives*/
Tab_B retirer_Bulle(Tab_B Tableau_de_Bulles); 
/*fonction qui retire la premiere bulle du tableau*/

Tab_B Copier_Tableau(Tab_B Tableau_de_Bulles);
/*Fonction creant un clone du tableau en parametre*/

bool Collisions_Bulles(Tab_B Bulle_lancees, Tab_B Bulle_lanceur); 
/*Fonction qui verifie si la bulle du lanceur pendant son mouvement, entre en collision avec une autre bulle*/

SDL_Rect Conversion_Coordonnees(float coordonnees_x, float coordonnees_y,Tab_B);





/**********************************/
/* Fonction de libération mémoire */
/**********************************/

void Tableau_Free(Tab_B);


#endif
