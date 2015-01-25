/*-----------------------------------------------------------
Client a lancer apres le serveur avec la commande :
client <adresse-serveur> <message-a-transmettre>
------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <unistd.h>
#include <stdbool.h> 
#include "structure.h"

typedef struct sockaddr 	sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct hostent 		hostent;
typedef struct servent 		servent;

void envoieCoordonnees(int sock)
{
    char buffer[3];
    int tmp;

    printf("Saisir la coordonnée horizontale : ");
    scanf("%d",&tmp);
    buffer[0] = (char)(((int)'0')+tmp);

    buffer[1] = ' ';

    printf("Saisir la coordonnée verticale : ");
    scanf("%d",&tmp);
    buffer[2] = (char)(((int)'0')+tmp);

    if ((write(sock, buffer, strlen(buffer))) < 0) 
    {
        perror("erreur : impossible d'ecrire le message destine au serveur.");
        exit(1);
    }    
}

void envoieGrille(int sock,char* mat)
{
    if ((write(sock, mat, strlen(mat))) < 0) 
    {
        perror("erreur : impossible d'ecrire le message destine au serveur.");
        exit(1);
    }      
}

void initialisation(Grille *g)
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

int main(int argc, char **argv) {
  
    int 	socket_descriptor;	/* descripteur de socket */
    sockaddr_in adresse_locale; 	/* adresse de socket local */
    hostent *	ptr_host; 		/* info sur une machine hote */
    //servent *	ptr_service; 		/* info sur service */
    char *	prog; 			/* nom du programme */
    char *	host; 			/* nom de la machine distante */
     
    if (argc != 2) 
    {
    	perror("usage : client <adresse-serveur> ");
    	exit(1);
    }
   
    prog = argv[0];
    host = argv[1];
    
    printf("nom de l'executable : %s \n", prog);
    printf("adresse du serveur  : %s \n", host);
    
    if ((ptr_host = gethostbyname(host)) == NULL) 
    {
    	perror("erreur : impossible de trouver le serveur a partir de son adresse.");
    	exit(1);
    }
    
    /* copie caractere par caractere des infos de ptr_host vers adresse_locale */
    bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
    adresse_locale.sin_family = AF_INET; /* ou ptr_host->h_addrtype; */

    adresse_locale.sin_port = htons(5000);
   
    
    printf("numero de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port));
 
    Grille g = initGrille();
    initialisation(&g);

    for(;;)
    {

        selectionPositionVerticale();
            /* creation de la socket */
        if ((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        {
            perror("erreur : impossible de creer la socket de connexion avec le serveur.");
            exit(1);
        }

        /* tentative de connexion au serveur dont les infos sont dans adresse_locale */
        if ((connect(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0) 
        {
        	perror("erreur : impossible de se connecter au serveur.");
        	exit(1);
        }
        
        printf("connexion etablie avec le serveur. \n");
        
        printf("envoi d'un message au serveur. \n");

        //envoieCoordonnees(socket_descriptor);
        envoieGrille(socket_descriptor,setGrilleToTableau(g));
         
        printf("message envoye au serveur. \n");
                    
        /* lecture de la reponse en provenance du serveur */
        /*while((longueur = read(socket_descriptor, buffer, sizeof(buffer))) > 0) 
        {
        	printf("reponse du serveur : \n");
        	write(1,buffer,longueur);
        }*/

        

    }  
    close(socket_descriptor);
    
    
    printf("connexion avec le serveur fermee, fin du programme.\n");
    
    exit(0);
    
}
