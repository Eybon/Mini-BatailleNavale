/*-----------------------------------------------------------
Client a lancer apres le serveur avec la commande :
client <adresse-serveur> <message-a-transmettre>
------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <unistd.h>

#include "partie.h"

typedef struct sockaddr 	sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct hostent 		hostent;
typedef struct servent 		servent;

void action(int sock, Grille *g)
{
    printf("---Choix des coordonnées d'attaque---\n");
    int ph = selectionPositionHorizontale();
    int pv = selectionPositionVerticale();
    attaquerPosition(g,pv,ph);
    envoieCoordonnees(sock,ph,pv);
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

    printf(" Recherche d'un adversaire en cours ....\n")  ;
    receptionSignal(socket_descriptor);

    Grille g = initGrille();
    Grille gAdv = initGrille();
    initialisationDebutPartie(&g);
    envoieGrille(socket_descriptor,setGrilleToTableau(g));

    printf(" En attente de l'adversaire .... (Initialisation)\n")  ;
    receptionGrille(socket_descriptor,&gAdv);
    while(1)
    {      
        system("clear"); 
        affichageClient(g,gAdv);        
        printf(" En attente de l'adversaire ....(Action)\n")  ;
        if ( 1 == receptionGrille(socket_descriptor,&g))
        {
            system("clear");
            affichageClient(g,gAdv);
            printf(" --- Votre action --- \n");  
            action(socket_descriptor,&gAdv);
        }
    }  
    close(socket_descriptor);

    printf("connexion avec le serveur fermee, fin du programme.\n");
    
    exit(0);   
}
