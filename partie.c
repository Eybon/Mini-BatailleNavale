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

void envoieGrille(int sock,char* mat)
{
    if ((write(sock, mat, strlen(mat))) < 0) 
    {
        perror("erreur : impossible d'ecrire le message destine au serveur.");
        exit(1);
    }      
}

int receptionGrille(int sock,Grille *g)
{
        char buffer[200];
        int longueur;      
        if ((longueur = read(sock, buffer, sizeof(buffer))) <= 0) 
        {
            printf("Erreur de lecture !! \n");
            exit(1);        
        }
        remplirGrilleByString(g,buffer);
        return 1;
}

void envoieCoordonnees(int sock,int ph, int pv)
{
    char buffer[3];

    buffer[0] = (char)(((int)'0')+ph);

    buffer[1] = ' ';

    buffer[2] = (char)(((int)'0')+pv);

    if ((write(sock, buffer, strlen(buffer))) < 0) 
    {
        perror("erreur : impossible d'ecrire le message destine au serveur.");
        exit(1);
    }    
}

int receptionSignal(int sock)
{
    char buffer[3];
    int longueur; 
    printf("Reception - sock : %d \n",sock);     
    if ((longueur = read(sock, buffer, sizeof(buffer))) <= 0) 
    {
        printf("Erreur de lecture !! \n");
        exit(1);        
    }
    return 1;
}

void envoieSignal(int sock)
{
	char buffer[3];
    printf("Envoi - sock : %d \n",sock);
    if ((write(sock, buffer, strlen(buffer))) < 0) 
    {
        perror("erreur : impossible d'ecrire le message destine au serveur.");
        exit(1);
    }  
}

void initialisationDebutPartie(Grille *g)
{
    int i = 5;
    for(i=5;i>2;i--)
    {   
        bool test = false;
        while(test == false)
        {
            printf("---Placement du bateau de taille %d---\n",i);
            int ph = selectionPositionHorizontale();
            int pv = selectionPositionVerticale();
            Axe axe = selectionAxe();
            if (placerNavire(g,pv,ph,i,axe) == 1)
            {
                test = true;
            }
            else
            {
                printf("Erreur de positionnement !\n");
            }
            afficherGrille(*g);
        }
    }  
}