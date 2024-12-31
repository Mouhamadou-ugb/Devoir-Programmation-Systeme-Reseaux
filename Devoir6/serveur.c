#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf( "Usage: %s PORT\n", argv[0]);
        return -1;
    }

    int fdServeur, fdClient;
    struct sockaddr_in addrServeur, addrClient;
    socklen_t addrTaille = sizeof(addrClient);
    char buffer[BUFFER_SIZE];
    int compteur = 0;

    if ((fdServeur=socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Erreur de la création du socket serveur");
        return -1;
    }

    addrServeur.sin_family=AF_INET;
    addrServeur.sin_addr.s_addr=INADDR_ANY;
    addrServeur.sin_port=htons(atoi(argv[1]));

    if (bind(fdServeur, (struct sockaddr*)&addrServeur, sizeof(addrServeur)) < 0) {
        printf("Erreur dans bind");
        return -1;
    }

    if (listen(fdServeur, 1) < 0) {
        printf("Erreur dans listen");
        return -1;
    }

    printf("Le serveur attend une connexion sur le port %s .\n", argv[1]);

    if ((fdClient=accept(fdServeur, (struct sockaddr*)&addrClient, &addrTaille)) < 0) {
        printf("Erreur dans accepte");
        return -1;
    }

    printf("Client connecté avec succes.\n");

    while(1){
        sprintf(buffer, "%d", compteur);
        send(fdClient, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUFFER_SIZE);
        read(fdClient, buffer, BUFFER_SIZE);
        compteur = atoi(buffer) + 1;

        printf("Compteur reçu du client : %d\n", compteur);
        sleep(1);
    }

    close(fdClient);
    close(fdServeur);
    return 0;
}