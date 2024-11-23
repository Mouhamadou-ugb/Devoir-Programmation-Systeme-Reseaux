#include<stdio.h>   
#include<stdlib.h>
#include<unistd.h>  
#include<string.h>
#include<sys/types.h>  
#include<sys/stat.h>  
#include<fcntl.h>    
#include<unistd.h>    

#define SIZE 50
 

int** Matrice_aleatoire(int d){
    int **m =(int**)malloc(d*sizeof(int*));
    if(!m){
        printf("Pas assez de memoire.");
        exit(-1);
    }
    int i,j;
    for (i = 0; i < d; i++){
       m[i]=(int*) malloc(d*sizeof(int));
        if(!m[i]){
            printf("Pas assez de memoire.");
            exit(-1);
        }
    }
    for (i = 0; i < d; i++)
        for (j = 0; j < d; j++)
           m[i][j] = rand()%10;  //pour plus de lisibilité, on crée une matrice composé de nombres 0 à 9 
    return m;
}

int Copie_mode_binaire(int**m, int dim, char nomFic[SIZE]){
   printf("Copie des donnees en mode binaire ...\n");
   int fd = open(nomFic, O_WRONLY | O_CREAT | O_TRUNC, 0644);  
    if( fd == -1 ){
      perror("Erreur d'ouverture du fichier");
      return 0;
    }

    //ajouter des donnees dans le fichier

    int nbWrite=0;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
           nbWrite = write(fd,&m[i][j], sizeof(int));
           if(nbWrite <= 0){
              perror("Erreur d'ecriture");
              return 0;
           }         
        }
    }
    printf("Copie terminee avec succes.\n");
    close(fd);
    return fd;
}

int Copie_mode_texte(int**m, int dim, char nomFic[SIZE]){
   printf("Copie des donnees en mode texte ...\n");
   int fd = open(nomFic, O_WRONLY | O_CREAT | O_TRUNC, 0644);  
    if( fd == -1 ){
      perror("Erreur d'ouverture du fichier");
      return 0;
    }

    char buffer[64]; 
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            
            int len = snprintf(buffer, sizeof(buffer), "%d ", m[i][j]);
            if (write(fd, buffer, len) != len) {
                perror("Erreur d'écriture dans le fichier");
                close(fd);
                return 0;
            }
        }
    }
    printf("Copie terminee avec succes.\n");
    close(fd);
    return fd;
}

void Afficher_fichier(char nomFichier[]){
   int fd = open(nomFichier, O_RDONLY);
    if (fd == -1) {
        perror("Erreur d'ouverture du fichier");
        exit(-1);
    }

    char buff[SIZE];
    ssize_t lignelu;

    printf("Affichage du contenu du fichier %s\n",nomFichier);
    
    while ((lignelu = read(fd, buff, SIZE)) > 0)
        write(STDOUT_FILENO, buff, lignelu);

    if (lignelu == -1) {
        perror("Erreur de lecture");
        close(fd);
        exit(-1);
    }

    close(fd);
    printf("\n");
}

extern int optopt;    
extern char* optarg;  

int main(int argc, char *argv[])
{
   int opt;
   int c=0, a=0, b=0, f=0, d=0,t=0, dim=0;  //ces variables nous permetterons de savoir les options simultannément donner en argument
   char nomFichier[SIZE];
   if(argc<6){
      fprintf(stderr,"Nombre d'argument insuffisant.\n");
      printf("Usage: %s option( -f entier ou -g entier ou -f entier -g ou -g entier -f \n)",argv[0]);
      return 0;
   }
   while ((opt = getopt(argc, argv, ":cabtd:f:")) != -1)
   {
       switch (opt) {
            case 'c':         
                     c = 1; 
                     break;
            case 'a': 
                     a = 1;
                     break;
            case 'd':   
                        d=1;
                        if(dim = atoi(argv[3]))
                            break;
                        else{
                            printf("Erreur %s doit etre un entier.\n", argv[3]);
                            return 0;
                        }
                        
            case 't': 
                       t=1;
                       break;
            case 'b': 
                       b=1;
                       break;
            case 'f':   
                      f==1; 
                      strcpy(nomFichier,argv[5]);
                       break;
            case ':':
                       printf("Erreur l'option -%c attend un argument.\n",optopt);
                       exit(EXIT_FAILURE);
            case '?':
                       printf("Erreur option -%c inconnue.\n", optopt);
                       break;
       }
   }
   if(c==1 && b==1){
      printf("Creation d'une matrice aleatoire de dimension %d\n", dim);  
      int **m=Matrice_aleatoire(dim);
      int fd = Copie_mode_binaire(m,dim,nomFichier);
   }else if (c==1  && t==1)
   {
      printf("Creation d'une matrice aleatoire de dimension %d\n", dim);  
      int **m=Matrice_aleatoire(dim);
      int fd = Copie_mode_texte(m,dim,nomFichier);
   }
   else if (c==1 && t==0 && b==0)  //Si aucun type de fichier n'est donné
   {
    //on choisi par defaut le mode binaire
    printf("Creation d'une matrice aleatoire de dimension %d\n", dim);  
    int **m=Matrice_aleatoire(dim);
    int fd = Copie_mode_binaire(m,dim,nomFichier);
   }else if (a==1 && t==1 )
        Afficher_fichier(argv[5]);
   return 0;  
}
