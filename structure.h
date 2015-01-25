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
char* initTableauChar();
char* setGrilleToTableau(Grille g);
void remplirGrilleByString(Grille *g,char string[]);
Etat inspecterPosition(Grille *g, int verticale, int horizontale);
void modifierPosition(Grille *g, int verticale, int horizontale, Etat e);
int attaquerPosition(Grille *g, int verticale, int horizontale);
int placerNavire(Grille *g,int verticaleAvant,int horizontaleAvant, int tailleNavire, Axe axe);
int selectionPositionVerticale();
int selectionPositionHorizontale();
Axe selectionAxe();
void afficherGrille(Grille g);
/*Attention probleme avec les fonctions utilisant des char** */
char** initMatriceChar();
char** setGrilleToMatrice(Grille g);
void remplirGrilleByMatrice(Grille *g,char** matrice);
void affich(char** mat);
