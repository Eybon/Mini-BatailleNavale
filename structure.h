#include <stdio.h>
#include <stdlib.h>

#define TAILLE 10

typedef enum Etat Etat;
enum Etat
{
    VIDE, RATE, OCCUPE, TOUCHE
};

typedef enum Axe Axe;
enum Axe
{
    HORIZONTALE,VERTICALE
};

/*
*La Grille est un matrice de caractère représentant le grille du jeu.
*Une case peut etre vide(VIDE), occupé par un bateau (OCCUPE) ou occupé mais détruite(TROUVE)	
*/
typedef struct Grille Grille;
struct Grille
{
	Etat matrice[TAILLE][TAILLE]; 
};


Grille initGrille();
Etat inspecterPosition(Grille *g, int longueur, int largeur);
void modifierPosition(Grille *g, int longeur, int largeur, Etat e);
int attaquerPosition(Grille *g, int longueur, int largeur);
int placerNavire(Grille *g,int longueurAvant,int largeurAvant, int tailleNavire, Axe axe);
void afficherGrille(Grille g);
