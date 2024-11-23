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
    if(argc != 6){
        perror("Nombre d'argument incorrecte.\n");
        printf(" Usage: %s nomFichier part1 part2 part3 part4.", argv[0]);
        return -1;
    }
    
    char nomFichierDest[50];
    strcpy(nomFichierDest, argv[1]);
    int  fdDest= open(nomFichierDest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    for ( int i = 2; i < 6; i++)
    {
        char buff;
        int nbRead, nbWrite;
        int nbTotal = 0;
        int fdSource = open(argv[i], O_RDONLY);
        do{
            //lecture dans le fichier source
            nbRead = read(fdSource, &buff, sizeof(char));
           //ecriture dans le ficchier de dest
            if(nbRead>0){
                nbWrite = write(fdDest,&buff, sizeof(char));
                if(nbWrite<=0){

                    printf("Erreur d'ecriture dans le fichier de destination");
                    return 0;
                }
            }
        }while (nbRead>0);
      close(fdSource);
    }
    if(close(fdDest)==-1){
      perror("Erreur de fermeture du fichier source");
      return -1;
   }
    printf("Jointure effectuee avec succes.\n");
    
    return 0;
}
