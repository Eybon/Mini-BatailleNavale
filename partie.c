#include "partie.h"

Partie initPartie()
{
	Partie p;
	p.gJ1 = (Grille*)malloc(sizeof(Grille));
	*(p.gJ1) = initGrille();
	p.gJ2 = (Grille*)malloc(sizeof(Grille));
	*(p.gJ2) = initGrille();
	return p;
}