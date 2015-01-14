#include "structure.h"

int main(int argc, char *argv[])
{
	Grille g = initGrille();
	printf("vide : %d\n",(int)g.matrice[3][3]);
	modifierPosition(&g,3,3,OCCUPE);
	modifierPosition(&g,9,9,OCCUPE);
	printf("occupé : %d\n",(int)g.matrice[3][3]);
	afficherGrille(g);
	attaquerPosition(&g,3,3);
	attaquerPosition(&g,5,3);
	placerNavire(&g,1,1,9,VERTICALE);
	placerNavire(&g,1,2,3,HORIZONTALE);	
	afficherGrille(g);	
	return 0;
}

Grille initGrille()
{
	Grille g;
	int i,j;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			g.matrice[i][j] = VIDE;
		}
	}
	return g;
}

Etat inspecterPosition(Grille *g, int longueur, int largeur)
{
	return g->matrice[longueur][largeur];
}

void modifierPosition(Grille *g, int longueur, int largeur, Etat e)
{
	g->matrice[longueur][largeur] = e;
}

/*
*Retourne 0 si la case ciblé est vide, 1 si la case est occupé, -1 pour les erreurs autres cas
*/
int attaquerPosition(Grille *g, int longueur, int largeur)
{
	if(g->matrice[longueur][largeur] == VIDE)
	{
		g->matrice[longueur][largeur] = RATE;
		return 0;
	}	
	else
	{
		if(g->matrice[longueur][largeur] == OCCUPE)
		{
			g->matrice[longueur][largeur] = TOUCHE;
			return 1;
		}
	}
	return -1;
}

/*
*Retourne 1 si le le placement du navire est ok, -1 sinon
*/
int placerNavire(Grille *g,int longueurAvant,int largeurAvant, int tailleNavire, Axe axe)
{
	//placement d'un navire horizontal
	if(axe == HORIZONTALE)
	{
		if((0<longueurAvant)&&(longueurAvant<TAILLE)&&(0<largeurAvant)&&(largeurAvant<TAILLE)&&(largeurAvant+tailleNavire-1<TAILLE))
		{
			int i;
			//on verifie que les cases sont disponibles
			for(i=0;i<tailleNavire;i++)
			{
				if(inspecterPosition(g,longueurAvant,largeurAvant)==OCCUPE)
				{
					return -1;
				}
			}
			//on place les navires			
			for(i=0;i<tailleNavire;i++)
			{
				modifierPosition(g,longueurAvant,largeurAvant+i,OCCUPE);
			}
			return 1;
		}
	}
	//placement d'un navire vertical
	if(axe == VERTICALE)
	{
		if((0<longueurAvant)&&(longueurAvant<TAILLE)&&(0<largeurAvant)&&(largeurAvant<TAILLE)&&(longueurAvant+tailleNavire-1<TAILLE))
		{
			int i;
			//on verifie que les cases sont disponibles
			for(i=0;i<tailleNavire;i++)
			{
				if(inspecterPosition(g,longueurAvant,largeurAvant)==OCCUPE)
				{
					return -1;
				}
			}	
			//on place les navires		
			for(i=0;i<tailleNavire;i++)
			{
				modifierPosition(g,longueurAvant+i,largeurAvant,OCCUPE);
			}
			return 1;
		}			
	}
	return -1;
}

void afficherGrille(Grille g)
{
	int i,j,k;
	for(i=0;i<TAILLE;i++)
	{	
		for(k=0;k<TAILLE;k++)
		{
			printf("----");
		}
		printf("-\n");
		printf("| ");		
		for(j=0;j<TAILLE;j++)
		{
			if(g.matrice[i][j] == VIDE)
			{
				printf(" ");
			}
			if(g.matrice[i][j] == RATE)
			{
				printf("+");
			}			
			if(g.matrice[i][j] == OCCUPE)
			{
				printf("O");
			}
			if(g.matrice[i][j] == TOUCHE)
			{
				printf("X");
			}
			printf(" | ");						
		}
		printf("\n");
	}
	for(k=0;k<TAILLE;k++)
	{
		printf("----");
	}
	printf("-\n");
}