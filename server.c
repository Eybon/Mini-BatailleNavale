/*----------------------------------------------
Serveur à lancer avant le client
------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h> 	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h> 		/* pour hostent, servent */
#include <string.h> 		/* pour bcopy, ... */  
#define TAILLE_MAX_NOM 256

#include <unistd.h>
#include <pthread.h>
#include "partie.h"

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

Partie tabPartie[20];

/*return 1 si la lecture est bugger (client lost)*/
int receptionCoordonnees(Partie p, int joueur)
{
    char buffer[3];
    int horiz,vert;

    int longueur;
   
    if(joueur == 1)
    {   
        
        if ((longueur = read(p.socketJ1, buffer, sizeof(buffer))) <= 0) 
        {
            gameOverGrille(p.gJ2);
            return 1;
        }
        printf(" -> reception coordonnée joueur 1\n");
    }
    else
    {
        
        if ((longueur = read(p.socketJ2, buffer, sizeof(buffer))) <= 0) 
        {
            gameOverGrille(p.gJ1);
            return 1;
        }
        printf(" -> reception coordonnée joueur 2\n");
    }

    horiz = atoi(&buffer[0]);
    vert = atoi(&buffer[2]);

    printf("valeur d'attaque : %d %d\n",horiz,vert);

    if(joueur == 1)
    {
        attaquerPosition(p.gJ2,vert,horiz);
    }
    else
    {
        attaquerPosition(p.gJ1,vert,horiz);
    }
    return 0;
}
/*
static void *task_receptionGrille(void *data_sock)
{
    if(data_sock != NULL)
    {
        int *sock = data_sock;

        char buffer[200];

        int longueur;      
        if ((longueur = read(*sock, buffer, sizeof(buffer))) <= 0) 
            return NULL;
        if(isFirstPlayer==0)  
        {
            p.socketJ1 = *sock;
            remplirGrilleByString(p.gJ1,buffer);
            isFirstPlayer = 1;
        }
        else
        {
            p.socketJ2 = *sock;
            remplirGrilleByString(p.gJ2,buffer);
            isFirstPlayer = 0;
        }
        afficherDuoGrille(*(p.gJ1),*(p.gJ2));

    }
    return NULL;
}*/

static void *task_receptionGrilleJ1(void *partie)
{
    Partie *partie2 = (Partie*) partie;
    if(partie2 != NULL)
    {
        Partie p;
        p.socketJ1 = (*partie2).socketJ1;
        p.socketJ2 = (*partie2).socketJ2;
        p.gJ1 = (*partie2).gJ1;
        p.gJ2 = (*partie2).gJ2;

        char buffer[200];
        int longueur;  
        printf("Attente de reception grille du J1\n");      
        if ((longueur = read(p.socketJ1, buffer, sizeof(buffer))) <= 0) 
            return NULL;
        remplirGrilleByString(p.gJ1,buffer);

    }
    printf("Reception grille du J1\n");
    return 0;
}

static void *task_receptionGrilleJ2(void *partie)
{
    Partie *partie2 = (Partie*) partie;
    if(partie2 != NULL)
    {
        Partie p;
        p.socketJ1 = (*partie2).socketJ1;
        p.socketJ2 = (*partie2).socketJ2;
        p.gJ1 = (*partie2).gJ1;
        p.gJ2 = (*partie2).gJ2;

        char buffer[200];
        int longueur;    
        printf("Attente de reception grille du J2\n");  
        if ((longueur = read(p.socketJ2, buffer, sizeof(buffer))) <= 0) 
            return NULL;
        remplirGrilleByString(p.gJ2,buffer);

    }
    printf("Reception grille du J2\n");
    return 0;
}


static void *task_gestionPartie(void *partie)
{
    /*Partie *partie2 = (Partie*) partie;
    if(partie2 != NULL)
    {
        Partie p;
        p.socketJ1 = (*partie2).socketJ1;
        p.socketJ2 = (*partie2).socketJ2;
        p.gJ1 = (*partie2).gJ1;
        p.gJ2 = (*partie2).gJ2;*/

    int *i = (int*) partie;

    if(i != NULL)
    {
        int nbPartie = (int) *i;    // tabPartie[nbPartie]
        printf(" Gestion de la partie(value de nbPartie) : %d \n",nbPartie);

        printf("Dans gestionPartie, socket 1 : %d socket 2 :%d\n",tabPartie[nbPartie].socketJ1,tabPartie[nbPartie].socketJ2);

        if ((write(tabPartie[nbPartie].socketJ1, setGrilleToTableau(*(tabPartie[nbPartie].gJ2)), strlen(setGrilleToTableau(*(tabPartie[nbPartie].gJ2))))) < 0) 
        {
            perror("erreur : impossible d'envoyer l'autorisation au client.");
            exit(1);
        } 
        if ((write(tabPartie[nbPartie].socketJ2, setGrilleToTableau(*(tabPartie[nbPartie].gJ1)), strlen(setGrilleToTableau(*(tabPartie[nbPartie].gJ1))))) < 0) 
        {
            perror("erreur : impossible d'envoyer l'autorisation au client.");
            exit(1);
        } 
        printf("envoie des grilles au 2 joueurs : ok\n");
        sleep(1);
        while(tabPartie[nbPartie].end != 1)
        {
            printf("autorise le joueur 1 à jouer\n");
            printf(" socket : %d \n",tabPartie[nbPartie].socketJ1);
            if ((write(tabPartie[nbPartie].socketJ1, setGrilleToTableau(*(tabPartie[nbPartie].gJ1)), strlen(setGrilleToTableau(*(tabPartie[nbPartie].gJ1))))) < 0) 
            {
                perror("erreur : impossible d'envoyer l'autorisation au client.");
                exit(1);
            } 
            printf("attente de l'action du joueur 1\n");
            tabPartie[nbPartie].end = receptionCoordonnees(tabPartie[nbPartie],1);

            printf("autorise le joueur 2 à jouer\n");
            printf(" socket : %d \n",tabPartie[nbPartie].socketJ2);
            if ((write(tabPartie[nbPartie].socketJ2, setGrilleToTableau(*(tabPartie[nbPartie].gJ2)), strlen(setGrilleToTableau(*(tabPartie[nbPartie].gJ2))))) < 0) 
            {
                perror("erreur : impossible d'envoyer l'autorisation au client.");
                exit(1);
            } 
            printf("attente de l'action du joueur 2\n");
            tabPartie[nbPartie].end = receptionCoordonnees(tabPartie[nbPartie],2);

            //system("clear");

            afficherDuoGrille(*(tabPartie[nbPartie].gJ1),*(tabPartie[nbPartie].gJ2));
        } 
        printf(" fin de la partie numero %d \n",nbPartie);
        close(tabPartie[nbPartie].socketJ1);
        close(tabPartie[nbPartie].socketJ2);
    }
    return 0;
}
                                  
int main(int argc, char **argv) 
{


    /*------------------------------------------------------------------------------------------------
    ---------------------         Partie Creation de la connexion         ----------------------------
    ------------------------------------------------------------------------------------------------*/
  
    int 		socket_descriptor, 		/* descripteur de socket */
			first_socket_descriptor,
            seconde_socket_descriptor;	/* [nouveau] descripteur de socket */
	socklen_t		longueur_adresse_courante; 	/* longueur d'adresse courante d'un client */
    sockaddr_in 	adresse_locale, 		/* structure d'adresse locale*/
			adresse_client_courant; 	/* adresse client courant */
    hostent*		ptr_hote; 			/* les infos recuperees sur la machine hote */
    //servent*		ptr_service; 			/* les infos recuperees sur le service de la machine */
    char 		machine[TAILLE_MAX_NOM+1]; 	/* nom de la machine locale */
    
    gethostname(machine,TAILLE_MAX_NOM);		/* recuperation du nom de la machine */
    
    /* recuperation de la structure d'adresse en utilisant le nom */
    if ((ptr_hote = gethostbyname(machine)) == NULL) 
    {
		perror("erreur : impossible de trouver le serveur a partir de son nom.");
		exit(1);
    }
    
    /* initialisation de la structure adresse_locale avec les infos recuperees */			
    
    /* copie de ptr_hote vers adresse_locale */
    bcopy((char*)ptr_hote->h_addr, (char*)&adresse_locale.sin_addr, ptr_hote->h_length);
    adresse_locale.sin_family		= ptr_hote->h_addrtype; 	/* ou AF_INET */
    adresse_locale.sin_addr.s_addr	= INADDR_ANY; 			/* ou AF_INET */


    adresse_locale.sin_port = htons(5000);
    
    printf("numero de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port) /*ntohs(ptr_service->s_port)*/);
    
    /* creation de la socket */
    if ((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
		perror("erreur : impossible de creer la socket de connexion avec le client.");
		exit(1);
    }

    int yes = 1;	
    if(setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
    {
        perror("setsockopt");
        pthread_exit(NULL);
    }

    /* association du socket socket_descriptor à la structure d'adresse adresse_locale */
    if ((bind(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0) 
    {
		perror("erreur : impossible de lier la socket a l'adresse de connexion.");
		exit(1);
    }
    
    /* initialisation de la file d'ecoute */
    listen(socket_descriptor,5);


    /*------------------------------------------------------------------------------------------------
    ---------------------               Partie Gestion du Jeu             ----------------------------
    ------------------------------------------------------------------------------------------------*/

    tabPartie[0] = initPartie();
    tabPartie[1] = initPartie();
    tabPartie[2] = initPartie();
    tabPartie[3] = initPartie();
    int nbPartie = 0;

    //init
    while(1)
    {
        //Partie p = initPartie();

        /* attente des connexions et traitement des donnees recues */
        
    	longueur_adresse_courante = sizeof(adresse_client_courant);	
    	/* adresse_client_courant sera renseigné par accept via les infos du connect */
    	if ((first_socket_descriptor = accept(socket_descriptor, (sockaddr*)(&adresse_client_courant),&longueur_adresse_courante))< 0) 
        {
    		perror("erreur : impossible d'accepter la connexion avec le client.");
    		exit(1);
    	}
        tabPartie[nbPartie].socketJ1 = first_socket_descriptor;

        printf("Partie %d - Socket 1 : %d \n",nbPartie,tabPartie[nbPartie].socketJ1);
        //envoieSignal(first_socket_descriptor);

        longueur_adresse_courante = sizeof(adresse_client_courant); 
        /* adresse_client_courant sera renseigné par accept via les infos du connect */
        if ((seconde_socket_descriptor = accept(socket_descriptor, (sockaddr*)(&adresse_client_courant),&longueur_adresse_courante))< 0) 
        {
            perror("erreur : impossible d'accepter la connexion avec le client.");
            exit(1);
        }  
        tabPartie[nbPartie].socketJ2 = seconde_socket_descriptor;

        printf("Partie %d - Socket 2 : %d \n",nbPartie,tabPartie[nbPartie].socketJ2);
        //envoieSignal(seconde_socket_descriptor);

        
        pthread_t t,t2;
        
        //sleep(1) ici crée un bug !! pourquoi ?? just wtf ....
        envoieSignal(tabPartie[nbPartie].socketJ1);
        envoieSignal(tabPartie[nbPartie].socketJ2);

        printf("signaux envoyés \n");

        pthread_create (&t, NULL, task_receptionGrilleJ1, &tabPartie[nbPartie]);
        pthread_create (&t2, NULL, task_receptionGrilleJ2, &tabPartie[nbPartie]);

        printf("en attente des grilles clients \n");

        pthread_join (t, NULL);
        pthread_join (t2, NULL);

        pthread_t tpartie;
        pthread_create(&tpartie,NULL,task_gestionPartie,&nbPartie);

        //pthread_join(tpartie,NULL);
        sleep(1);
        printf(" Nouveau Thread ! \n");
        nbPartie++;

    }
    return 1;    
}
