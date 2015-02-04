#include <stdio.h>
#include <stdlib.h>
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

/*pas Ici*/
void receptionCoordonnees(Partie p, int joueur);
