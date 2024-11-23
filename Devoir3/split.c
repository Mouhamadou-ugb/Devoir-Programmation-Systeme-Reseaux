#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    if(argc != 3){
        perror("Nombre d'argument incorrecte.\n");
        printf(" Usage: %s nomFichier Taille.", argv[0]);
        return -1;
    }
    
    int fdSource = open(argv[1], O_RDONLY);
    if(!fdSource){
        perror("Erreur d'ouverture du fichier.");
        return -1;
    }
    char nomFichierSource[50];
    strcpy(nomFichierSource,argv[1]); 
    struct stat infoFile;
    int resultat=fstat(fdSource, &infoFile);  
    if(resultat == -1){
        printf("Erreur de recuperation des informations sur le fichier source.");
        return 0;
    }
     printf("Taille du fichier: %ld\n", infoFile.st_size);

    //Dans notre programme on decoupera par defaut un fichier en 10 parties

    size_t tailleDeDecoupage = (infoFile.st_size + 9) / 10; 
    char buffer[4096];
    ssize_t nbReadSource;
    int partie = 1;
    char nomPartie[256];
    size_t nb_octet = tailleDeDecoupage;

    while ((nbReadSource = read(fdSource, buffer, sizeof(buffer))) > 0) {
        snprintf(nomPartie, sizeof(nomPartie), "Split%d.txt", partie);
        int fdDest = open(nomPartie, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fdDest < 0) {
            perror("Erreur d'ouverture du fichier de sortie");
            close(fdSource);
            exit(EXIT_FAILURE);
        }

        size_t bytes_written = 0;
        while (bytes_written < nb_octet && nbReadSource > 0) {
            ssize_t write_size = write(fdDest, buffer, nbReadSource);
            if (write_size < 0) {
                perror("Erreur d'écriture dans le fichier de sortie");
                close(fdSource);
                close(fdDest);
                exit(EXIT_FAILURE);
            }
            bytes_written += write_size;
            nbReadSource = read(fdSource, buffer, sizeof(buffer));
        }

        close(fdDest);
        partie++;
        if (partie > 10) break;
    }
   
   if(close(fdSource)==-1){
      perror("Erreur de fermeture du fichier source");
      return -1;
   }
    
    return 0;
}
