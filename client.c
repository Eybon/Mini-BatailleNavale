/*-----------------------------------------------------------
Client a lancer apres le serveur avec la commande :
client <adresse-serveur> <message-a-transmettre>
------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>

#include "partie.h"

typedef struct sockaddr 	sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct hostent 		hostent;
typedef struct servent 		servent;

int socket_descriptor;  /* descripteur de socket */
int victoire;

void traitementsignal(int signal) 
{
    close(socket_descriptor);
    system("clear");
    if(1==victoire)
    {
        printf(" -------------------------------------\n");
        printf(" -            VICTOIRE !!!           -\n");
        printf(" -------------------------------------\n");
    }
    else
    {
        if(0==victoire)
        {
            printf(" -------------------------------------\n");
            printf(" -            DEFAITE ...            -\n");
            printf(" -------------------------------------\n");
        } 
    }
    exit(1);
}

void action(int sock, Grille *gAdv, Grille gClient)
{
    printf("---Choix des coordonnées d'attaque---\n");
    int ph = selectionPositionHorizontale();
    int pv = selectionPositionVerticale();
    int type = attaquerPosition(gAdv,pv,ph);
    envoieCoordonnees(sock,ph,pv);
    system("clear");
    affichageClient(gClient,*gAdv);
    if((type==BAT1)||(type==BAT2)||(type==BAT3)||(type==BAT4)||(type==BAT5))
    {
        printf(" ------------------------------------------\n");
        printf(" ->  Touché !                             -\n");
        if(0==rechercheBateau(*gAdv,type))
        {
            printf(" -> Vous avez coulé un bateau adverse !   -\n");
        }
        printf(" ------------------------------------------\n");
    }
    else
    {
        printf(" ------------------------------------------\n");
        printf(" ->  Raté !                               -\n");
        printf(" ------------------------------------------\n");
    }
    if(0==rechercheFinDePartie(*gAdv))
    {
        victoire = 1;
        kill(getpid(),SIGQUIT);
    }
}

void actionReception(Grille *g)
{
    if(0==rechercheFinDePartie(*g))
    {
        victoire = 0;
        kill(getpid(),SIGQUIT);
    }
    if(-1==rechercheFinDePartie(*g))
    {
        victoire = 1;
        kill(getpid(),SIGQUIT);
    }    
}

int main(int argc, char **argv) {
  
    //traitement des signaux
    signal(SIGQUIT,traitementsignal);//traitement pour Quitter avec END
    signal(SIGINT,traitementsignal);//taitement pour le signal Ctrl-C
    victoire = 0;

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
    printf(" Signal recu \n")  ;

    Grille g = initGrille();
    Grille gAdv = initGrille();
    initialisationDebutPartie(&g);
    envoieGrille(socket_descriptor,setGrilleToTableau(g));

    printf(" En attente de l'adversaire .... (Initialisation)\n")  ;
    receptionGrille(socket_descriptor,&gAdv);
    printf(" Grille Recu \n");
    //afficherGrille(gAdv);
    system("clear");
    while(1)
    {      
        //system("clear"); 
        //affichageClient(g,gAdv);        
        printf(" En attente de l'adversaire ....(Action)\n")  ;
        if ( 1 == receptionGrille(socket_descriptor,&g))
        {
            system("clear");    
            actionReception(&g);
            affichageClient(g,gAdv);
            //afficherDuoGrille(g,gAdv);
            printf(" --- Votre action --- \n");  
            action(socket_descriptor,&gAdv,g);
        }
    }  
    close(socket_descriptor);

    printf("connexion avec le serveur fermee, fin du programme.\n");
    
    exit(0);   
}


