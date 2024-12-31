#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc<2) {
        printf("Usage : %s Adresse_IP\n", argv[0]);
        return -1;
    }
    
    struct sockaddr_in addrServer;

    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin_family = AF_INET;         
    addrServer.sin_addr.s_addr = inet_addr(argv[1]); 
    
    int socketClient;
    int resultat;
    int index_port;

    printf("Scan des ports TCP ouverts sur l'adresse %s de 0 à 3000 ... \n", argv[1]);
   
    for (index_port=0; index_port<=3000; index_port++) {
       
        socketClient = socket(AF_INET, SOCK_STREAM, 0);
        if (socketClient == -1) {
            printf("Erreur de la création de la socket.");
            return -1;
        }

        addrServer.sin_port=htons(index_port);

        resultat=connect(socketClient, (struct sockaddr *)&addrServer, sizeof(addrServer));

        if (resultat==0) 
            printf("Port ouvert : %d\n", index_port);

        close(socketClient);
    }

    return 0;
}
