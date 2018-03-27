#ifndef FONCTIONS_C
#define FONCTIONS_C

#include "Constantes.h"
#include "fonctions.h"




/*Fonctions*/


void Affichage(int bub_array[BUB_NY][BUB_NX], SDL_Rect rcSprite_Blue, int mouvement)
{
  int compteur_x, compteur_y;
  SDL_Rect nb_bulle;
  SDL_Rect centre_lanceur;
  centre_lanceur.x = CENTRE_LANCEUR_X;
  centre_lanceur.y = CENTRE_LANCEUR_Y;
  compteur_y = 0;
  SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);
  SDL_BlitSurface(gear,&rcSrc_Gear,screen,&rcGear);
  SDL_BlitSurface(grass,NULL,screen,NULL);
  SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);
  if(mouvement == 1)
    {
      /*SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));*/
      SDL_BlitSurface(grass,NULL,screen,NULL);
      SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);
      SDL_BlitSurface(gear,&rcSrc_Gear,screen,&rcGear);
      SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);
      SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);
      SDL_BlitSurface(bub[couleur], &rcSrc_Blue, screen, &rcSprite_Blue);
      SDL_BlitSurface(bub[couleur], &rcSrc_Blue, screen, &centre_lanceur);
      /* SDL_BlitSurface(Chiffre, &rcSrc_Chiffre[0],screen,(&pos_score));  */
    }
  if(mouvement== 0)
    {
      SDL_BlitSurface(grass,NULL,screen,NULL);
      SDL_BlitSurface(bub[couleur], &rcSrc_Blue, screen, &centre_lanceur);
      SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);
      SDL_BlitSurface(gear,&rcSrc_Gear,screen,&rcGear);
      SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);
      SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);
      SDL_BlitSurface(bub[couleur], &rcSrc_Blue, screen, &centre_lanceur);
      /*SDL_BlitSurface(Chiffre, &rcSrc_Chiffre[0],screen,(&pos_score));*/
      /*SDL_BlitSurface(bubble_blue, &rcSrc_Blue, screen, &rcSprite_Blue);*/
    }
  /* SDL_BlitSurface(Chiffre, &rcSrc_Chiffre[0],screen,(&pos_score));*/
  affichage_score();
  ecrire_score();
  remplissage();
  if(new_game==1)
    {
      newgame();
    }
  if(rest ==1)
    {
      restart();
    }
  if(pause == 1)
    {
      pause_disp();
    }
  SDL_UpdateRect(screen,0,0,0,0);
}





float Tir_directionx(int angle_lanceur)
{
  float Alpha; 
  float directionx_locale;
  
  Alpha = (angle_lanceur*PI)/48; 
  directionx_locale = 0.65*(sin(Alpha)); /*0.65*/
  return directionx_locale;
}





float Tir_directiony(int angle_lanceur)
{
  float Alpha;
  float directiony_locale;
  
  Alpha = (angle_lanceur*PI)/48;
  directiony_locale = -0.65*(cos(Alpha));
  if(directiony_locale < 0.)
    {  
      return directiony_locale * 1.;
    }
  if(directiony_locale > 0.)
    {
      return -directiony_locale * 1.;
    }
  if(directiony_locale == 0.)
    {
      return -1.0;
    }
}





int Dessiner_balle_tiree(float directionx, float directiony)
{
  double rcSprite_Blue_locale_y;
  double rcSprite_Blue_locale_x;
  
  rcSprite_Blue_locale_y = rcSprite_Blue.y * 1.;
  rcSprite_Blue_locale_x = rcSprite_Blue.x * 1.;
  while(mouvement == 1)
    {
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      rcSprite_Blue_locale_y += directiony;   /*on augmente la hauteur de notre balle -en fonction de direction y-*/
      
      if(rcSprite_Blue_locale_y == PLAFOND || rcSprite_Blue_locale_y < PLAFOND) /*on verifie que l'on ne touche pas le plafond*/
	{
	  /*remplir de maniere a stopper le mouvement de la balle si c'est le cas -ajouter une variable ?-*/
 	  mouvement = 0;
	  rcSprite_Blue_locale_y = PLAFOND;
	}
      /*ajouter une partie verifiant si l'on a toucher une autre bulle*/
      
      /*on deplace la bulle vers la droite ou la gauche -en fonction de directionx- */
      rcSprite_Blue_locale_x += directionx *1.;
      
      /*si on touche l'un des mur -peu importe lequel- on inverse directionx*/
      if((rcSprite_Blue_locale_x <= (MUR_GAUCHE))||(rcSprite_Blue_locale_x >= (MUR_DROIT-40)))
	{
	  directionx = -directionx *1.;
	  rcSprite_Blue_locale_x += directionx *1.;
	}
      /*SDL_UpdateRect(screen, 0, 0, 0, 0);*/
      /* SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0,0,0));/*on nettoie l'ecran*/
      /*SDL_BlitSurface(grass, NULL, screen, NULL);/*on redessine l'ecran etape par etape 1: le background*/
      /*SDL_BlitSurface(sprite,&rcSrc, screen, &rcSprite);/*on redessine le lanceur*/
      rcSprite_Blue.x = rcSprite_Blue_locale_x;
      rcSprite_Blue.y = rcSprite_Blue_locale_y;
      /*SDL_BlitSurface(bubble_blue, &rcSrc_Blue, screen, &rcSprite_Blue);/*on dessine la bulle a chaque passage de la boucle*/
      
      if(collision(rcSprite_Blue_locale_x, rcSprite_Blue_locale_y))
	{
	  mouvement = 0;
	  if(rcSprite_Blue.y > 380.)
	    {
	      gameover = 1;
	      printf("Gameover");
	      break;
	    }
	  placage_boules_contact(rcSprite_Blue_locale_x, rcSprite_Blue_locale_y);
	}
      
      Affichage(bub_array, rcSprite_Blue, mouvement);
    }
  
  return bub_array[BUB_NY][BUB_NX];
}





int discretiser(double x)
{
  int i; /*x discretiser*/
  /* au cas ou*/
  
  i = ((x+((BUB_SIZE)/2)-MUR_GAUCHE)/BUB_SIZE);

  return i;
}

int discretiser_y(double y)
{
  int j;
  
  j=((y+((BUB_SIZE)/2)+PLAFOND/BUB_SIZE));
  
  return j;
}


void remplissage()
{
  SDL_Rect Bulle_locale;
  int compteur_x, compteur_y;

  for(compteur_y = 0; compteur_y < BUB_NY; compteur_y ++)
    {
      for(compteur_x = 0; compteur_x < BUB_NX-(compteur_y%2); compteur_x ++)
	{
	  if (bub_array[compteur_y][compteur_x] != -1) 
	    {
	      Bulle_locale.x=(compteur_x * BUB_SIZE)+(MUR_GAUCHE+20*(compteur_y%2));
	      Bulle_locale.y=((compteur_y*(BUB_SIZE-5))+PLAFOND);
	      SDL_BlitSurface(bub[bub_array[compteur_y][compteur_x]], &rcSrc_Blue, screen, &Bulle_locale);
	    }
	}
    }
}

int collision(float posx, float posy)
{
  int i, j;

  if (posy <= PLAFOND)
    return 1;

  for(i=0; i < BUB_NX; i ++)
    {
      for(j = 0; j < BUB_NY; j ++)
	{
	  if ((bub_array[j][i])!=-1)
	    {
	      double cx = (i * BUB_SIZE)+(MUR_GAUCHE+20*(j%2));
	      double cy = ((j*(BUB_SIZE-5))+PLAFOND);
	      double d2 = (cx-posx)*(cx-posx) + (cy-posy)*(cy-posy);
	      if (d2 < ALPHA*ALPHA*BUB_SIZE*BUB_SIZE) 
		{
		  printf("Collision avec (%d,%d)\n", j, i);
		  return 1;
		}
	    }
	}
    }
  return 0;
}



void placage_boules_contact(float posx, float posy)
{
  SDL_Rect rcSprite_collisions_locale;
  int i,j, imin, jmin;
  double dmin = 70000;

  for(j = 0; j < BUB_NY; j++)
    {
      for(i=0; i < BUB_NX-(j%2); i++)
	{
	  if((bub_array[j][i])==-1)
	    {
	      double cx = (i * BUB_SIZE)+(MUR_GAUCHE + 20*(j%2));
	      double cy = ((j*(BUB_SIZE-5))+PLAFOND);
	      double d2 = (cx-posx)*(cx-posx) + (cy-posy)*(cy-posy);
	      if(d2 < dmin)
		{
		  imin = i;
		  jmin = j;
		  dmin = d2;
		}
	    }
	}
    }

  double cx = (imin * BUB_SIZE)+(MUR_GAUCHE + 20*(jmin%2));
  double cy = ((jmin*(BUB_SIZE-5))+PLAFOND);
  bub_array[jmin][imin]=couleur;
  for(j = 0; j < BUB_NY; j++)
    {
      for(i=0; i < BUB_NX-(j%2); i++)
	{
	  bub_connected_component[j][i] = 0;
	}
    }
  bub_connected_component[jmin][imin] = 1;
  calcul_connexe(jmin, imin);
  victoire();
  
  /*bulle_flottante();*/
}


void calcul_connexe(int j, int i)
{
  int i_cpt;
  int j_loc;
  int i_loc;
  int compteur;
  int test;
  int nouveau = 1;
  SDL_Rect Bulle_locale;
  j_loc=0;
  compteur = 0;
  while (nouveau) 
    {
      nouveau = 0;
      for (j_loc = 0; j_loc < BUB_NY; j_loc++)
	{
	  for(i_loc = 0; i_loc < BUB_NX - (j_loc%2); i_loc++)
	    {
	      if(bub_connected_component[j_loc][i_loc]==1)
		{
		  int voisines[6][2];
		  voisines[0][0] = j_loc;
		  voisines[0][1] = i_loc-1;
		  voisines[1][0] = j_loc;
		  voisines[1][1] = i_loc+1;
		  voisines[2][0] = j_loc-1;
		  voisines[2][1] = i_loc-1 + (j_loc%2);
		  voisines[3][0] = j_loc-1;
		  voisines[3][1] = i_loc   + (j_loc%2);
		  voisines[4][0] = j_loc +1;
		  voisines[4][1] = i_loc-1 + (j_loc%2);
		  voisines[5][0] = j_loc +1;
		  voisines[5][1] = i_loc   + (j_loc%2);
		  
		  for(int l = 0; l < 6; l++)
		    {
		      int nj = voisines[l][0];
		      int ni = voisines[l][1];
		      if((ni >=0 && ni<BUB_NX - (nj%2) )&& (nj >=0 && nj < BUB_NY) && (bub_array[nj][ni]==bub_array[j][i] )&& (bub_connected_component[nj][ni] !=1))
			{
			  bub_connected_component[nj][ni] = 1;
			  nouveau = 1;
			}
		    }
		}
	    }
	}
    }
  compteur = 0;
  for(j_loc = 0; j_loc < BUB_NY; j_loc++)
    { 
      for(i_loc = 0; i_loc < BUB_NX - (j%2); i_loc++)
	{
	  if(bub_connected_component[j_loc][i_loc]==1)
	    {
	      compteur += 1;
	    }
	}
    }
  if(compteur>=3)
    {
      for(j_loc = 0; j_loc < BUB_NY; j_loc++)
	{
	  for(i_loc = 0; i_loc < BUB_NX - (j%2); i_loc++)
	    {
	      if(bub_connected_component[j_loc][i_loc]==1)
		{
		  Bulle_locale.x = (i_loc * BUB_SIZE)+(MUR_GAUCHE + 20*(j_loc%2));
		  Bulle_locale.y = ((j_loc*(BUB_SIZE-5))+PLAFOND);
		  bub_array[j_loc][i_loc]= -1;
		  bub_connected_component[j_loc][i_loc]=0;
		}
	    }
	}
      Score += 300;
      newscore = 1;
      compteur -= 3;
      while(compteur > 0)
	{
	  i_cpt += 1;
	  Score += i_cpt*25;
	  Score += 100;
	  compteur -= 1;
	}
      i_cpt = 0;
    }
  nouveau = 1;
  for(i_loc = 0; i_loc < BUB_NX; i_loc++)
    {
      if (bub_array[0][i_loc] != -1)
	bub_connected_component[0][i_loc]=1;
    }
  while (nouveau) 
    {
      nouveau = 0;
      for (j_loc = 0; j_loc < BUB_NY; j_loc++)
	{
	  for(i_loc = 0; i_loc < BUB_NX - (j_loc%2); i_loc++)
	    {
	      if(bub_connected_component[j_loc][i_loc]==1)
		{
		  int voisines[6][2];
		  voisines[0][0] = j_loc;
		  voisines[0][1] = i_loc-1;
		  voisines[1][0] = j_loc;
		  voisines[1][1] = i_loc+1;
		  voisines[2][0] = j_loc-1;
		  voisines[2][1] = i_loc-1 + (j_loc%2);
		  voisines[3][0] = j_loc-1;
		  voisines[3][1] = i_loc   + (j_loc%2);
		  voisines[4][0] = j_loc +1;
		  voisines[4][1] = i_loc-1 + (j_loc%2);
		  voisines[5][0] = j_loc +1;
		  voisines[5][1] = i_loc   + (j_loc%2);
		  
		  for(int l = 0; l < 6; l++)
		    {
		      int nj = voisines[l][0];
		      int ni = voisines[l][1];
		      if((ni >=0 && ni<BUB_NX - (nj%2) )&& (nj >=0 && nj < BUB_NY) && (bub_array[nj][ni]!=-1 ) && (bub_connected_component[nj][ni] != 1))
			{
			  bub_connected_component[nj][ni] = 1;
			  nouveau = 1;
			}
		      
		    }
		}
	    }
	}
    }
  for(j_loc = 0; j_loc < BUB_NY; j_loc++)
    {
      for(i_loc = 0; i_loc < BUB_NX - (j%2); i_loc++)
	{
	  if(bub_connected_component[j_loc][i_loc]==0 && j_loc != BUB_NY-1 && bub_array[j_loc][i_loc] != -1)
	    {
	      bub_array[j_loc][i_loc]= -1;
	      bub_connected_component[j_loc][i_loc]=0;
	      Score += 50;
	      newscore = 1;
	    }
	}
    }
  empty = 1;
  for(j_loc = 0; j_loc < BUB_NY; j_loc++)
    {
      for(i_loc = 0; i_loc < BUB_NX - (j%2); i_loc++)
	{
	  if(bub_array[j_loc][i_loc] != -1)
	    {
	      empty = 0;
	    }
	}
    }
  if(empty==1)
    {
      Score += 5000;
    }
}

void victoire()
{
  int i, j, victoire;
  victoire = 1;
  for(i=0; i < BUB_NX; i ++)
    {
      for(j = 0; j < BUB_NY; j ++)
	{
	  if ((bub_array[j][i])!=-1)
	    {
	      victoire = 0;
	    }
	}
    }
  if(victoire == 1)
    {
      printf("VICTOIRE, OH YEAH");
      remplissage();
    }
}


void conversion_score(int Score)
{
  int i;
  int Score_loc;
  Score_loc = Score;
  i = 0;

  while(Score_loc>10)
    {
      Tab_Score[i] = Score_loc % 10;
      Score_loc = (Score_loc - (Score_loc%10))/10;
      i += 1;
    }
  if(Score_loc>0)
    {
      Tab_Score[i]=Score_loc;
    }
}


void affichage_score()
{
  int i;
  conversion_score(Score);
  pos_score.y = 410;
  pos_score.x = 170;

  for(i = 0; i < 10; i++)
    {
      SDL_BlitSurface(Chiffre,&rcSrc_Chiffre[Tab_Score[i]],screen,(&pos_score));
      pos_score.x -= 17;
    }
}



void affichage_S(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[18], screen, (&pos_lettre));
}
void affichage_C(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[2], screen, (&pos_lettre));
}
void affichage_O(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[14], screen, (&pos_lettre));
}

void affichage_P(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[15], screen, (&pos_lettre));
}
void affichage_R(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[17], screen, (&pos_lettre));
}
void affichage_E(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[4], screen, (&pos_lettre));
}

void affichage_A(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[0], screen, (&pos_lettre));
}

void affichage_T(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[19], screen, (&pos_lettre));
}

void ecrire_score()
{
  pos_lettre.y = 380;
  pos_lettre.x = 135;
  affichage_E(pos_lettre);
  pos_lettre.x -= 20;
  affichage_R(pos_lettre);
  pos_lettre.x -= 20;
  affichage_O(pos_lettre);
  pos_lettre.x -= 20;
  affichage_C(pos_lettre);
  pos_lettre.x -= 20;
  affichage_S(pos_lettre);
  pos_lettre.x -= 20;
}

void ecriture_score_save()
{
  long int score_loc;
  score_loc = Score;
  fputc(score_loc, score_save);
}

void lecture_score(FILE* scorefile)
{
  double test;

  if(score_save != NULL)
    {
      do
	{
	  test = fgetc(score_save);
	  printf("%f", test);
	}while(test != EOF);
    }
}

void affichage_I(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[8], screen, (&pos_lettre));
}

void affichage_U(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[20], screen, (&pos_lettre));
}

void affichage_X(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[23], screen, (&pos_lettre));
}

void affichage_Y(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[24], screen, (&pos_lettre));
}

void affichage_fl(SDL_Rect pos_lettre)
{
  pos_lettre.y += desc;
  SDL_BlitSurface(Chiffre, &rcSrc_Chiffre[14], screen, (&pos_lettre));
}

void affichage_N(SDL_Rect pos_lettre)
{
  SDL_BlitSurface(Lettre, &rcSrc_Lettre[13], screen, (&pos_lettre));
}



void newgame()
{

  if(Score != 0)
    {
      Score = 0;
      for(int i=0; i<10; i++)
	{
	  Tab_Score[i] = 0;
	}
    }
  empty = 1;
  pos_lettre.y = 200;
  pos_lettre.x = 314;
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  affichage_fl(pos_lettre);
  pos_lettre.x += 17;
  affichage_S(pos_lettre);
  pos_lettre.x += 17;
  affichage_T(pos_lettre);
  pos_lettre.x += 17;
  affichage_A(pos_lettre);
  pos_lettre.x += 17;
  affichage_R(pos_lettre);
  pos_lettre.x += 17;
  affichage_T(pos_lettre);

  pos_lettre.x = 331;
  pos_lettre.y = 250;
  affichage_E(pos_lettre);
  pos_lettre.x +=17;
  affichage_X(pos_lettre);
  pos_lettre.x += 22;
  affichage_I(pos_lettre);
  pos_lettre.x += 12;
  affichage_T(pos_lettre);
  
  
}


void restart()
{
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  pos_lettre.x= 200;
  pos_lettre.y = 200;
  affichage_R(pos_lettre);
  pos_lettre.x += 17;
  affichage_E(pos_lettre);
  pos_lettre.x += 17;
  affichage_S(pos_lettre);
  pos_lettre.x += 17;
  affichage_T(pos_lettre);
  pos_lettre.x +=17;
  affichage_A(pos_lettre);
  pos_lettre.x +=17;
  affichage_R(pos_lettre);
  pos_lettre.x +=17;
  affichage_T(pos_lettre);
  pos_lettre.x +=25;
  affichage_fl(pos_lettre);
  pos_lettre.x += 17;
  affichage_Y(pos_lettre);
  pos_lettre.x += 17;
  affichage_E(pos_lettre);
  pos_lettre.x += 17;
  affichage_S(pos_lettre);
  pos_lettre.x -= 34;
  pos_lettre.y +=50;
  affichage_N(pos_lettre);
  pos_lettre.x += 17;
  affichage_O(pos_lettre);
}

void pause_disp()
{
  pos_lettre.y = 200;
  pos_lettre.x = 314;
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
  affichage_P(pos_lettre);
  pos_lettre.x += 17;
  affichage_A(pos_lettre);
  pos_lettre.x += 17;
  affichage_U(pos_lettre);
  pos_lettre.x += 17;
  affichage_S(pos_lettre);
  pos_lettre.x +=17;
  affichage_E(pos_lettre);
  pos_lettre.x += 17;
}
#endif
