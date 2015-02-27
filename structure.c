#include "structure.h"

/*int main(int argc, char *argv[])
{
	Grille g = initGrille();
	modifierPosition(&g,3,3,OCCUPE);
	modifierPosition(&g,9,9,OCCUPE);
	//afficherGrille(g);
	attaquerPosition(&g,3,3);
	attaquerPosition(&g,5,3);
	placerNavire(&g,1,1,9,VERTICALE);
	placerNavire(&g,1,2,3,HORIZONTALE);	
	afficherGrille(g);
	char** mat = setGrille(g);
	printf("ok\n");
	affich(mat);	
	return 0;
}*/

char** initMatriceChar()
{
	char **matrice = (char**)malloc(sizeof(char*) * TAILLE);
	int i;
	for(i = 0; i <TAILLE; i++)
	{
	    matrice[i] = (char*)malloc(sizeof(char) * TAILLE);
	}
	return matrice;
}

char* initTableauChar()
{
	char *matrice = (char*)malloc(sizeof(char) * TAILLE);
	return matrice;
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

void remplirGrilleByString(Grille *g,char string[])
{
	int i;
	for(i=0;i<TAILLE;i++)
	{
		int j;
		for(j=0;j<TAILLE;j++)
		{
			if(string[i*10+j]==' ')
				modifierPosition(g,i,j,VIDE);
			if(string[i*10+j]=='+')
				modifierPosition(g,i,j,RATE);
			if(string[i*10+j]=='O')
				modifierPosition(g,i,j,OCCUPE);
			if(string[i*10+j]=='X')
				modifierPosition(g,i,j,TOUCHE);	
			if(string[i*10+j]=='1')
				modifierPosition(g,i,j,BAT1);	
			if(string[i*10+j]=='2')
				modifierPosition(g,i,j,BAT2);	
			if(string[i*10+j]=='3')
				modifierPosition(g,i,j,BAT3);	
			if(string[i*10+j]=='4')
				modifierPosition(g,i,j,BAT4);	
			if(string[i*10+j]=='5')
				modifierPosition(g,i,j,BAT5);																													
		}
	}
}

void remplirGrilleByMatrice(Grille *g,char** matrice)
{
	int i;
	for(i=0;i<TAILLE;i++)
	{
		int j;
		for(j=0;j<TAILLE;j++)
		{
			if(matrice[i][j]==' ')
				modifierPosition(g,i,j,VIDE);
			if(matrice[i][j]=='+')
				modifierPosition(g,i,j,RATE);
			if(matrice[i][j]=='O')
				modifierPosition(g,i,j,OCCUPE);
			if(matrice[i][j]=='X')
				modifierPosition(g,i,j,TOUCHE);	
			if(matrice[i][j]=='1')
				modifierPosition(g,i,j,BAT1);	
			if(matrice[i][j]=='2')
				modifierPosition(g,i,j,BAT2);	
			if(matrice[i][j]=='3')
				modifierPosition(g,i,j,BAT3);	
			if(matrice[i][j]=='4')
				modifierPosition(g,i,j,BAT4);	
			if(matrice[i][j]=='5')
				modifierPosition(g,i,j,BAT5);																							
		}
	}
}

char* setGrilleToTableau(Grille g)
{
	char *matrice = initTableauChar();
	int i;
	for(i=0;i<TAILLE;i++)
	{
		int j;
		for(j=0;j<TAILLE;j++)
		{
			if(g.matrice[i][j]==VIDE)
				matrice[i*10+j]=' ';
			if(g.matrice[i][j]==RATE)
				matrice[i*10+j]='+';
			if(g.matrice[i][j]==OCCUPE)
				matrice[i*10+j]='O';
			if(g.matrice[i][j]==TOUCHE)
				matrice[i*10+j]='X';
			if(g.matrice[i][j]==BAT1)
				matrice[i*10+j]='1';
			if(g.matrice[i][j]==BAT2)
				matrice[i*10+j]='2';
			if(g.matrice[i][j]==BAT3)
				matrice[i*10+j]='3';
			if(g.matrice[i][j]==BAT4)
				matrice[i*10+j]='4';
			if(g.matrice[i][j]==BAT5)
				matrice[i*10+j]='5';				
		}
	}
	return matrice;
}

char** setGrilleToMatrice(Grille g)
{
	char **matrice = initMatriceChar();
	int i;
	for(i=0;i<TAILLE;i++)
	{
		int j;
		for(j=0;j<TAILLE;j++)
		{
			if(g.matrice[i][j]==VIDE)
				matrice[i][j]=' ';
			if(g.matrice[i][j]==RATE)
				matrice[i][j]='+';
			if(g.matrice[i][j]==OCCUPE)
				matrice[i][j]='O';
			if(g.matrice[i][j]==TOUCHE)
				matrice[i][j]='X';
			if(g.matrice[i][j]==BAT1)
				matrice[i][j]='1';
			if(g.matrice[i][j]==BAT2)
				matrice[i][j]='2';
			if(g.matrice[i][j]==BAT3)
				matrice[i][j]='3';
			if(g.matrice[i][j]==BAT4)
				matrice[i][j]='4';
			if(g.matrice[i][j]==BAT5)
				matrice[i][j]='5';																			
		}
	}
	return matrice;
} 

void affich(char** mat)
{
	int i;
	for(i=0;i<TAILLE;i++)
	{
		int j;
		for(j=0;j<TAILLE;j++)
		{
			char c = mat[i][j];
			printf("  %c ",c);
		}
		printf("\n");
	}
}

Etat inspecterPosition(Grille *g, int vertical, int horizontale)
{
	return g->matrice[vertical][horizontale];
}

void modifierPosition(Grille *g, int vertical, int horizontale, Etat e)
{
	g->matrice[vertical][horizontale] = e;
}

/*
*Retourne 0 si la case ciblé est vide, l'etat de la case si la case est occupé, -1 pour les erreurs autres cas
*/
int attaquerPosition(Grille *g, int vertical, int horizontale)
{
	if(g->matrice[vertical][horizontale] == VIDE)
	{
		g->matrice[vertical][horizontale] = RATE;
		return 0;
	}	
	else
	{
		if(g->matrice[vertical][horizontale] == OCCUPE)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return 1;
		}
		if(g->matrice[vertical][horizontale] == BAT1)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return BAT1;
		}
		if(g->matrice[vertical][horizontale] == BAT2)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return BAT2;
		}
		if(g->matrice[vertical][horizontale] == BAT3)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return BAT3;
		}
		if(g->matrice[vertical][horizontale] == BAT4)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return BAT4;
		}
		if(g->matrice[vertical][horizontale] == BAT5)
		{
			g->matrice[vertical][horizontale] = TOUCHE;
			return BAT5;
		}										
	}
	return -1;
}

/*
*Retourne 1 si le le placement du navire est ok, -1 sinon
*/
int placerNavire(Grille *g,int verticalAvant,int horizontaleAvant, int tailleNavire, Axe axe, Etat numBateau)
{
	//placement d'un navire horizontal
	if(axe == HORIZONTALE)
	{
		if((0<=verticalAvant)&&(verticalAvant<TAILLE)&&(0<=horizontaleAvant)&&(horizontaleAvant<TAILLE)&&(horizontaleAvant+tailleNavire-1<TAILLE))
		{
			int i;
			//on verifie que les cases sont disponibles
			for(i=0;i<tailleNavire;i++)
			{
				if((inspecterPosition(g,verticalAvant,horizontaleAvant+i)==OCCUPE)||(inspecterPosition(g,verticalAvant,horizontaleAvant+i)==BAT1)||
					(inspecterPosition(g,verticalAvant,horizontaleAvant+i)==BAT2)||(inspecterPosition(g,verticalAvant,horizontaleAvant+i)==BAT3)||
					(inspecterPosition(g,verticalAvant,horizontaleAvant+i)==BAT4)||(inspecterPosition(g,verticalAvant,horizontaleAvant+i)==BAT5))
				{
					return -1;
				}
			}
			//on place les navires			
			for(i=0;i<tailleNavire;i++)
			{
				modifierPosition(g,verticalAvant,horizontaleAvant+i,numBateau);
			}
			return 1;
		}
	}
	//placement d'un navire vertical
	if(axe == VERTICALE)
	{
		if((0<=verticalAvant)&&(verticalAvant<TAILLE)&&(0<=horizontaleAvant)&&(horizontaleAvant<TAILLE)&&(verticalAvant+tailleNavire-1<TAILLE))
		{
			int i;
			//on verifie que les cases sont disponibles
			for(i=0;i<tailleNavire;i++)
			{
				if((inspecterPosition(g,verticalAvant+i,horizontaleAvant)==OCCUPE)||(inspecterPosition(g,verticalAvant+i,horizontaleAvant)==BAT1)||
					(inspecterPosition(g,verticalAvant+i,horizontaleAvant)==BAT2)||(inspecterPosition(g,verticalAvant+i,horizontaleAvant)==BAT3)||
					(inspecterPosition(g,verticalAvant+i,horizontaleAvant)==BAT4)||(inspecterPosition(g,verticalAvant+i,horizontaleAvant)==BAT5))
				{
					return -1;
				}
			}	
			//on place les navires		
			for(i=0;i<tailleNavire;i++)
			{
				modifierPosition(g,verticalAvant+i,horizontaleAvant,numBateau);
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
			if(g.matrice[i][j] == BAT1)
			{
				printf("1");
			}
			if(g.matrice[i][j] == BAT2)
			{
				printf("2");
			}
			if(g.matrice[i][j] == BAT3)
			{
				printf("3");
			}
			if(g.matrice[i][j] == BAT4)
			{
				printf("4");
			}
			if(g.matrice[i][j] == BAT5)
			{
				printf("5");
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

void afficherDuoGrille(Grille g,Grille g2)
{
	int i,j,k;
	for(i=0;i<TAILLE;i++)
	{	
		for(k=0;k<TAILLE;k++)
		{
			printf("----");
		}
		printf("   ");
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
			if(g.matrice[i][j] == BAT1)
			{
				printf("1");
			}
			if(g.matrice[i][j] == BAT2)
			{
				printf("2");
			}
			if(g.matrice[i][j] == BAT3)
			{
				printf("3");
			}
			if(g.matrice[i][j] == BAT4)
			{
				printf("4");
			}
			if(g.matrice[i][j] == BAT5)
			{
				printf("5");
			}									
			printf(" | ");						
		}
		printf(" | ");
		for(j=0;j<TAILLE;j++)
		{
			if(g2.matrice[i][j] == VIDE)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == RATE)
			{
				printf("+");
			}			
			if(g2.matrice[i][j] == OCCUPE)
			{
				printf("O");
			}
			if(g2.matrice[i][j] == TOUCHE)
			{
				printf("X");
			}
			if(g2.matrice[i][j] == BAT1)
			{
				printf("1");
			}
			if(g2.matrice[i][j] == BAT2)
			{
				printf("2");
			}
			if(g2.matrice[i][j] == BAT3)
			{
				printf("3");
			}
			if(g2.matrice[i][j] == BAT4)
			{
				printf("4");
			}
			if(g2.matrice[i][j] == BAT5)
			{
				printf("5");
			}			
			printf(" | ");						
		}		
		printf("\n");
	}
	for(k=0;k<TAILLE;k++)
	{
		printf("----");
	}
	printf("   ");
	for(k=0;k<TAILLE;k++)
	{
		printf("----");
	}	
	printf("-\n");
}

/* g est la grille client, g2 la grille adversaire*/
void affichageClient(Grille g, Grille g2)
{
	int i,j,k;
	printf("         Votre Grille                                    Grille Adversaire\n");
	for(i=0;i<TAILLE;i++)
	{	
		for(k=0;k<TAILLE;k++)
		{
			printf("----");
		}
		printf("   ");
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
			if(g.matrice[i][j] == BAT1)
			{
				printf("1");
			}
			if(g.matrice[i][j] == BAT2)
			{
				printf("2");
			}
			if(g.matrice[i][j] == BAT3)
			{
				printf("3");
			}
			if(g.matrice[i][j] == BAT4)
			{
				printf("4");
			}
			if(g.matrice[i][j] == BAT5)
			{
				printf("5");
			}			
			printf(" | ");						
		}
		printf(" | ");
		for(j=0;j<TAILLE;j++)
		{
			if(g2.matrice[i][j] == VIDE)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == RATE)
			{
				printf("+");
			}			
			if(g2.matrice[i][j] == OCCUPE)
			{
				printf(" "); // on ne veut pas voir les positions adversaires
			}
			if(g2.matrice[i][j] == TOUCHE)
			{
				printf("X");
			}
			if(g2.matrice[i][j] == BAT1)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == BAT2)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == BAT3)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == BAT4)
			{
				printf(" ");
			}
			if(g2.matrice[i][j] == BAT5)
			{
				printf(" ");
			}			
			printf(" | ");						
		}		
		printf("\n");
	}
	for(k=0;k<TAILLE;k++)
	{
		printf("----");
	}
	printf("   ");
	for(k=0;k<TAILLE;k++)
	{
		printf("----");
	}	
	printf("-\n");
}

int selectionPositionHorizontale()
{
	int val = 0;
	while((val<1)||(val>10))
	{
		char s[10] ;
		printf("Coordonnée horizontale(de 1 à 10) : ");
		scanf("%s",s);
		val = atoi(s);
	}
	return val-1;
}

int selectionPositionVerticale()
{
	int val = 0;
	while((val<1)||(val>10))
	{
		char s[10] ;
		printf("Coordonnée verticale(de 1 à 10) : ");
		scanf("%s",s);
		val = atoi(s);
	}
	return val-1;
}

Axe selectionAxe()
{	
	char val = '0';
	while((val!='h')&&(val!='v'))
	{
		char s[10] ;
		printf("Horizontalement ou verticalement (h ou v) ? : ");
		scanf("%s",s);
		val = s[0];
	}
	if (val == 'h')
	{
		return HORIZONTALE;
	}
	else
	{
		return VERTICALE;
	}
}

int rechercheBateau(Grille g,Etat e)
{
	int i,j;
	int count = 0;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			if(g.matrice[i][j]==e)
			{
				count++;
			}
		}
	}
	return count;
}

int rechercheFinDePartie(Grille g)
{
	int i,j;
	int count = 0;
	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			if(g.matrice[i][j]==BAT1)
			{
				count++;
			}
			if(g.matrice[i][j]==BAT2)
			{
				count++;
			}
			if(g.matrice[i][j]==BAT3)
			{
				count++;
			}
			if(g.matrice[i][j]==BAT4)
			{
				count++;
			}
			if(g.matrice[i][j]==BAT5)
			{
				count++;
			}												
		}
	}
	return count;
}