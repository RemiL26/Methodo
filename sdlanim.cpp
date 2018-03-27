/*Les Includes*/

#include "SDL.h"
#include <math.h> /*Pour differentes opération mathématique avancée*/
#include <stdbool.h>
#include <time.h>

#include "Constantes.h"
#include "fonctions.h"
#include "fonctions.c"




void HandleEvent(SDL_Event event)
{
	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			gameover = 1;
			break;
			
		/* handle the keyboard */
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_SPACE:
				  if(new_game != 1 && rest != 1)
				    {
				      if(((rcSprite_Blue.x)== CENTRE_LANCEUR_X)&&((rcSprite_Blue.y) == (CENTRE_LANCEUR_Y)))
					{
					  directionx = Tir_directionx(angle_lanceur);
					  directiony = Tir_directiony(angle_lanceur);
					  mouvement = 1;
					  bub_array[BUB_NY][BUB_NX] = Dessiner_balle_tiree(directionx, directiony);
					  nvcouleur = 0;
					  
					}
				      else
					{
					  
					  (rcSprite_Blue.x) = CENTRE_LANCEUR_X;
					  (rcSprite_Blue.y) = CENTRE_LANCEUR_Y;
					  Affichage(bub_array, rcSprite_Blue, 2);  
					}
				    }
				  else 
				    {
				      if(desc == 50 && new_game==1)
					{
					  gameover = 1;
					}
				      else if(desc == 50 && rest == 1)
					{
					  rest = 0;
					}
				      else if(new_game == 1)
					{
					  new_game = 0;
					}
				      else
					{
					  new_game = 1;
					  rest = 0;
					}
				    }
				  break;
			case SDLK_p:
			  {
			    if(pause != 1 && new_game != 1 && rest != 1)
			      {
				pause = 1;
			      }
			    else
			      {
				pause = 0;
			      }
			    break;
			  }
				case SDLK_q:
				  gameover = 1;
				  break;
				case SDLK_LEFT:
				  /*Si on est pas en fin d'animation (vers la gauche), alors on avance l'animation vers la gauche*/
				  /*ce qui revient a "baisser" dans le sprite*/
				  /*on change aussi l'angle du lanceur*/
					if ( rcSrc.y > 0 )
					{
						rcSrc.y -= 157;
						rcSrc_Wheel.y -= 47;
						if(rcSrc_Wheel.y < 0)
						  { 
						    rcSrc_Wheel.y = 752-47;
						  }
						rcSrc_Gear.y -= 116;
						if(rcSrc_Gear.y < 0)
						  {
						    rcSrc_Gear.y = 4640-116;
						  }
						angle_lanceur -= rotation_angle;
					}		
					break;
			case SDLK_f:
			  {
			    nvcouleur = 0;
			  }
			  break;
				case SDLK_RIGHT:
				  if ( rcSrc.y < SPRITE_HEIGHT-157)
				  {	
					  rcSrc.y = rcSrc.y+157;
					  rcSrc_Wheel.y += 47;
					  if(rcSrc_Wheel.y==752)
					    {
					      rcSrc_Wheel.y = 0;
					    }
					  rcSrc_Gear.y += 116;
					  if(rcSrc_Gear.y==4640)
					    {
					      rcSrc_Gear.y = 0;
					    }
					  angle_lanceur += rotation_angle;
				  }	
					break;
				case SDLK_UP: 
				  /*la fleche haut montera la fleche vers le centre de l'ecran (a la verticale)*/
				  if(new_game != 1 && rest != 1)
				    {
				      if (rcSrc.y < (MIDDLE_HEIGHT_ARROW)-157)
					{
					  rcSrc.y = rcSrc.y+157;
					  angle_lanceur += rotation_angle;
					}
				      else if (rcSrc.y >(MIDDLE_HEIGHT_ARROW))
					{
					  rcSrc.y = rcSrc.y - 157;
					  angle_lanceur -= rotation_angle;
					}
				    }
				  else
				    {
				      if(desc == 50 )
					{
					  desc -= 50;
					}
				    }
				  break;
			case SDLK_r:
			  
			  if(new_game != 1 && rest != 1 && pause != 1)
			    {
			      rest=1;
			    }
			  break;
				case SDLK_DOWN:
				  /*La fleche bas va faire descendre la fleche jusque l'horizontal (gauche, ou droite dependant de la position de  "depart" de notre fleche*/
				  if(new_game !=1 && rest != 1)
				    {
				      if ((rcSrc.y < (MIDDLE_HEIGHT_ARROW)) && rcSrc.y > 0)
					{
					  rcSrc.y = rcSrc.y-157;
					  angle_lanceur -= rotation_angle;
					}
				      else if ((rcSrc.y <(SPRITE_HEIGHT-157)) && rcSrc.y != 0)
					{
					  rcSrc.y = rcSrc.y + 157;
					  angle_lanceur += rotation_angle;
					}
				    }
				  else
				    {
				      if(desc != 50)
					{
					  desc += 50;
					}
				    }
				  break;

			default: break;
			}
			break;
	default: break;
	}
}










int main(int argc, char* argv[])
{
	int colorkey, colorkey_black;
	int i,y;
	int tempsPrecedent, tempsActuel; /*Les Variables ci sont utilisée avec les fonctions gérant le temps réel; ex : SDL_GetTicks*/
	desc = 0;

	Score = 0;
	new_game = 1;
	srand(time(NULL));
	/*Initialisation des differentes Variable*/
	angle_lanceur = -22;
	rotation_angle = 1;

	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption("SDL Animation", "SDL Animation");

	/* create window */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	/* set keyboard repeat */
	SDL_EnableKeyRepeat(70, 70);

	/* load sprite */
	temp   = SDL_LoadBMP("sprite.bmp");
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* load sprite wheel */
	temp = SDL_LoadBMP("frame_wheel.bmp");
	wheel = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/*load sprite gear */
	temp = SDL_LoadBMP("frame_gears.bmp");
	gear = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	

	/*load fichier de save*/
	score_save = fopen("score.txt", "w+");

	/*************************************************************************/

	/* Bulles Bleues */
	temp = SDL_LoadBMP("bub_blue.bmp");
	bubble_blue = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* Bulles Jaune*/
	temp = SDL_LoadBMP("bub_yellow.bmp");
	bubble_yellow = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* Bulles Verte */
	temp = SDL_LoadBMP("bub_green.bmp");
	bubble_green = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* Bulles Blanches */
	temp = SDL_LoadBMP("bub_white.bmp");
	bubble_white = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);


	/*tableau de bulles*/
	temp = SDL_LoadBMP("bub_black.bmp");
	bub[0]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("bub_blue.bmp");
	bub[1]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("bub_green.bmp");
	bub[2]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("bub_orange.bmp");
	bub[3]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("bub_purple.bmp");
	bub[4]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
 
	
	temp = SDL_LoadBMP("bub_red.bmp");
	bub[5]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("bub_yellow.bmp");
	bub[6]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
 
	temp = SDL_LoadBMP("bub_white.bmp");
	bub[7]=SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);



	/*Integration de Sprite : Chiffres et Lettres*/
	temp = SDL_LoadBMP("franklin.bmp");
	Chiffre = SDL_DisplayFormat(temp); 
	/*pour raison de lisibilité on sépare les chiffres et les lettres, meme si ils utilisent le meme sprite*/
	Lettre = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* setup sprite colorkey and turn on RLE */
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	colorkey_black = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_SetColorKey(bubble_blue, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);
	SDL_SetColorKey(wheel, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);
	SDL_SetColorKey(gear, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);
	SDL_SetColorKey(Chiffre, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);
	SDL_SetColorKey(Lettre, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);

	for(int i = 0; i<NUM_COLORS; i++)
	  {
	    SDL_SetColorKey(bub[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey_black);
	  }


	
	
	/***************************************************************************/

	/* load Background */
	temp  = SDL_LoadBMP("grass.bmp");
	grass = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/***************************************************************************/

	/* set sprite position */
	rcSprite.x = 267;
	rcSprite.y = 385;

	/***************************************************************************/
	
	/* set animation frame */
	rcSrc.x = 0;
	rcSrc.y = 0;
	rcSrc.w = 187; /*Largeur de notre sprite (le lanceur)*/
	rcSrc.h = 157; /*Hauteur de notre sprite (le lanceur)*/

	/***************************************************************************/
	rcSrc_Wheel.x = 0;
	rcSrc_Wheel.y = 0;
	rcSrc_Wheel.w = 33;
	rcSrc_Wheel.h = 47;

	rcWheel.x = 432;
	rcWheel.y = 474;
	/***************************************************************************/

	rcSrc_Gear.x = 0;
	rcSrc_Gear.y = 0;
	rcSrc_Gear.w = 126;
	rcSrc_Gear.h = 116;

	rcGear.x = 306;
	rcGear.y = 405;
	/***************************************************************************/
	for(i=0; i<15;i++)
	  {
	    rcSrc_Chiffre[i].x = 0 + (i*32);/**/
	    rcSrc_Chiffre[i].y = 100;
	    rcSrc_Chiffre[i].w = 24;
	    rcSrc_Chiffre[i].h = 24;
	  }

	for(i = 1; i<16; i++)
	  {
	    rcSrc_Lettre[i-1].x = 0 + (i*32);
	    rcSrc_Lettre[i-1].y = 133;
	    rcSrc_Lettre[i-1].w = 24;
	    rcSrc_Lettre[i-1].h = 24;
	  }

	for(i = 0; i<10; i++)
	  {
	    rcSrc_Lettre[i+15].x = 0 + (i*32);
	    rcSrc_Lettre[i+15].y = 165;
	    rcSrc_Lettre[i+15].w = 24;
	    rcSrc_Lettre[i+15].h = 24;
	  }

	/***************************************************************************/

	/* Sprite position : Bubble (Bleu) valeur dans le tableau : 1*/
	rcSprite_Blue.x = CENTRE_LANCEUR_X;
	rcSprite_Blue.y = CENTRE_LANCEUR_Y;

	/* Sprite position : Bulle (Jaune) valeur dans le tableau : 2*/
	rcSprite_Yellow.x = CENTRE_LANCEUR_X;
	rcSprite_Yellow.y = CENTRE_LANCEUR_Y;

	/* Sprite position : Bulle (Verte) valeur dans le tableau : 3*/
	rcSprite_Green.x = CENTRE_LANCEUR_X;
	rcSprite_Green.y = CENTRE_LANCEUR_Y;

	/* Sprite position : Bulle (blanche) valeur dans le tableau : 4*/
	rcSprite_White.x = CENTRE_LANCEUR_X;
	rcSprite_White.y = CENTRE_LANCEUR_Y;

	/**************************************************************************/
	for(int j = 0; j< BUB_NY; j++)
	  {
	    for(int i = 0; i<BUB_NX; i++)
	      {
		bub_connected_component[j][i]=0;
	      }
	  }

	for (int j = 0; j < BUB_NY; ++j)
	  for (int i = 0; i < BUB_NX; ++i)
	    bub_array[j][i] = -1;

	empty = 1;
	

	/*Sprite animation frame : Bubble (Bleu)*/

	rcSrc_Blue.x = 0;
	rcSrc_Blue.y = 0;
	rcSrc_Blue.w = 40; /*Largeur de notre bulle (Bleu)*/
	rcSrc_Blue.h = 40; /*Hauteur de notre bulle (Bleu)*/

	gameover = 0;
	/*on initialise notre "Bulles_Lanceur" a tableau_vide*/
	/*Bulles_Lanceur = nouveau_Tableau_vide();
	  Bulles_Lanceur = Ajouter_Bulle_Tableau(rcSprite_Blue,Bulles_Lanceur);*/

	/* message pump */
	while (!gameover)
	{
	  Affichage(bub_array, rcSprite_Blue, mouvement);
	  remplissage();
	  if(empty==1)
	    {
	      for (int j = 0; j <3; ++j) 
		{
		  for (int i = 0; i < BUB_NX-(j%2); ++i) 
		    {
		      bub_array[j][i]=rand()%8;
		      empty=0;
		    }
		}
	    }
		SDL_Event event;
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event);
		}
		if(nvcouleur !=1)
		  {
		    couleur = rand()%8;
		    for(y=0; y< BUB_NY; y++)
		      {
			for(i=0; i < BUB_NX-(y%2); i++)
			  {
			    if(bub_array[y][i]==couleur)
			      {
				nvcouleur = 1;
			      }
			  }
		      }
		    Affichage(bub_array, rcSprite_Blue, mouvement);
		  }

		/* collide with edges of screen */
		if (rcSprite.x <= 0)
			rcSprite.x = 0;
		if (rcSprite.x >= SCREEN_WIDTH - SPRITE_SIZE) 
			rcSprite.x = SCREEN_WIDTH - SPRITE_SIZE;

		if (rcSprite.y <= 0)
			rcSprite.y = 0;
		if (rcSprite.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
			rcSprite.y = SCREEN_HEIGHT - SPRITE_SIZE;

		/* draw the grass */

		SDL_BlitSurface(grass, NULL, screen, NULL);
			
		

		/* draw the sprite */
		SDL_BlitSurface(sprite,&rcSrc, screen, &rcSprite);
		SDL_BlitSurface(wheel,&rcSrc_Wheel,screen, &rcWheel);

		/* dessiner Sprite : Bubble (Bleu) */
		SDL_BlitSurface(bub[couleur], &rcSrc_Blue, screen, &rcSprite_Blue);
		Affichage(bub_array, rcSprite_Blue, mouvement);

		/* update the screen */
		/*SDL_UpdateRect(screen, 0, 0, 0, 0);*/
		i = 0;
		tempsPrecedent = 0;
		tempsActuel = SDL_GetTicks(); /*on donne a notre "tempsActuel" la valeur en milliseconde du temps ecoulés depuis le début du niveau (ici notre programme)*/
		/*if(tempsActuel - tempsPrecedent > 300) /*gestion de l'animation de la bulle bleue (penser a placer cela en fonction/procedure)
		  {
		    SDL_UpdateRect(screen, 0, 0, 0, 0);
		    if (rcSrc_Blue.y < BUBBLE_SPRITE_HEIGHT - 40)
		      {
			rcSrc_Blue.y += 40;
		      }
		    else
		      {
			rcSrc_Blue.y = 0;
		      }
		    tempsPrecedent=tempsActuel;
		  }*/
		
		
	}

	/* clean up */
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(grass);
	SDL_Quit();

	return 0;
}
