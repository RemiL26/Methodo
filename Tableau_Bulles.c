/*******************************/
/*                             */
/*                             */
/*                             */

/*******************************/
/*        Librairies           */
/*******************************/

/***********************************************/
/*      Un exemple de tableau de bulle         */
/***********************************************/
/* Tab_B Tableau_test
   Premiere
      Premiere.x
      Premiere.y
   Reste
*/


#include "SDL.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tableau_Bulles.h"

/**/
/**/
/*Constructeurs*/

Tab_B nouveau_Tableau_vide(void)
{
  return NULL;
}


/*fonction creant un tableau en ajoutant un SDL_rect a un tableau existant deja*/

Tab_B Ajouter_Bulle_Tableau(SDL_Rect Bulle, Tab_B Tableau_de_Bulles)
{
  Tab_B nouvelle;
  nouvelle = nouveau_Tableau_vide();

  /*on alloue de la memoire pour la nouvelle Bulle*/
  nouvelle = (Tab_B)malloc(sizeof(struct Tableau_Bulles));
  nouvelle->prem = Bulle;
  nouvelle->reste = Tableau_de_Bulles;
  return nouvelle;
}

/*fonction verifiant si un tableau est vide ou non*/
bool Est_vide_Tableau(Tab_B Tableau_de_Bulles) 
{
  return(Tableau_de_Bulles == NULL);
}

/*fonction donnant la premiere Bulle du tableau*/
SDL_Rect Premiere_Bulle(Tab_B Tableau_de_Bulles)
{
  return Tableau_de_Bulles->prem;
}


/*fonction donnant le reste d'un tableau */
Tab_B Reste_Tableau(Tab_B Tableau_de_Bulles)
{
  return Tableau_de_Bulles->reste;
}

Tab_B retirer_Bulle(Tab_B Tableau_de_Bulles)
{
  Tab_B nouvelle;
  nouvelle = Reste_Tableau(Tableau_de_Bulles);
  return nouvelle;
}

Tab_B Copier_Tableau(Tab_B Tableau_de_Bulles)
{
  Tab_B nouvelle;
  nouvelle = Ajouter_Bulle_Tableau(Premiere_Bulle(Tableau_de_Bulles),Reste_Tableau(Tableau_de_Bulles));
  return nouvelle;
}

bool Collision_Bulles(Tab_B Bulle_Lanceur, Tab_B Bulle_Lancees)
{
  Tab_B Tableau_Test;
  Tableau_Test = Bulle_Lancees;
  /*Si les coordonnées x ou y de la premiere -et seules- bulle du lanceur correspondent a la premiere des bulles lancees, on retourne Vrai*/
  if(((Premiere_Bulle(Bulle_Lanceur)).x == (Premiere_Bulle(Bulle_Lancees)).x)&&(Premiere_Bulle(Bulle_Lanceur)).y==(Premiere_Bulle(Bulle_Lancees)).y)
    {
      return true;
    }
  /*Sinon on verifie pour le reste, si la derniere bulles presente ne verifie pas la condition; on retourne faux*/
  return(!Est_vide_Tableau(Reste_Tableau(Bulle_Lancees)))&&(Collision_Bulles(Bulle_Lanceur,Reste_Tableau(Bulle_Lancees))); 
}

SDL_Rect Conversion_Coordonnees(float coordonnees_x, float coordonnees_y, Tab_B Bulles)
{
  SDL_Rect Prem;
  Prem = (Premiere_Bulle(Bulles));
  Prem.x = coordonnees_x;
  Prem.y = coordonnees_y;
  return Prem;

}

int Longueur_Tableau(Tab_B Bulles, int compteur)
{
  if(Reste_Tableau(Bulles)!=0)
    {
      return Longueur_Tableau(Reste_Tableau(Bulles), compteur+1);
    }
  return compteur;
}
