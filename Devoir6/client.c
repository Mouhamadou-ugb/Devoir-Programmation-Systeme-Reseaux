#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s adresse_serveur PORT", argv[0]);
        return -1;
    }

    int socketClient;
    struct sockaddr_in addrServeur;
    char buffer[BUFFER_SIZE];
    int compteur;

    if ((socketClient = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erreur de la création du socket client.");
       return -1;
    }


    addrServeur.sin_family = AF_INET;
    addrServeur.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &addrServeur.sin_addr)<=0) {
        printf("Adresse inconnue");
        return -1;
    }

    if (connect(socketClient, (struct sockaddr*)&addrServeur, sizeof(addrServeur)) < 0) {
        printf("Erreur de connexion au serveur");
        return -1;
    }

    printf("Connecté au serveur avec succes: %s:%s.\n", argv[1], argv[2]);

    while(1){
        memset(buffer,0, BUFFER_SIZE);
        read(socketClient, buffer, BUFFER_SIZE);
        compteur=atoi(buffer)+1;

        printf("Compteur reçu du serveur : %d\n", compteur);
        sleep(1);
        sprintf(buffer, "%d", compteur);
        send(socketClient, buffer, strlen(buffer), 0);
    }

    close(socketClient);
    return 0;
}