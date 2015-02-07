#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h> 
#include "structure.h"

typedef struct Partie Partie;
struct Partie
{
	int socketJ1;
	int socketJ2;
	Grille *gJ1;
	Grille *gJ2;
};

Partie initPartie();
void envoieGrille(int sock,char* mat);
int receptionGrille(int sock,Grille *g);
void envoieCoordonnees(int sock,int ph, int pv);
void initialisationDebutPartie(Grille *g);
void envoieSignal(int sock);
int receptionSignal(int sock);

/*pas Ici*/
void receptionCoordonnees(Partie p, int joueur);
