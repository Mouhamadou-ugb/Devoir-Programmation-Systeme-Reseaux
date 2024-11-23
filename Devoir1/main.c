#include<stdio.h>   
#include<stdlib.h>
#include<unistd.h>  
#include<math.h>
#include<string.h>

extern int optopt;    
extern char* optarg;  

//execution gcc main.c -o main -lm

int main(int argc, char *argv[])
{
   int opt;
   int k=0, f=0, g=0;
   if(argc<2){
      fprintf(stderr,"Nombre d'argument insuffisant.\n");
      printf("Usage: %s option(-f entier ou -g entier ou -f entier -g ou -g entier -f\n)",argv[0]);
      return 0;
   }
   while ((opt = getopt(argc, argv, ":f:g:")) != -1)
   {
       switch (opt) {
            case 'f':    
                         k = atoi(argv[2]);
                         f=1;
                         break;
            case 'g': 
                          
                         k = atoi(argv[2]) ;
                         g=1;
                       break;
            case '?':
                       printf("Erreur option -%c inconnue.\n", optopt);
                       break;
            default:
                       k = atoi(argv[2]);
                       if((strcmp("-f",argv[1]) == 0) && (strcmp("-g",argv[3])==0)){
                         f=-1;
                         g=-2;
                       }else if ((strcmp("-g",argv[1]) == 0) && (strcmp("-f",argv[3])==0)){
                          f=-2;
                          g=-1;
                       }
                       break;
       }
   }
   if (f==1 && g==0)
      printf("f(%d)= 2^%d = %.0f\n", k, k, pow(2,k));
   else if (g==1 && f==0)
      printf("g(%d)= 2 * %d = %d\n", k, k, 2 * k);
   else if (f==-1 && g==-2 )
        printf("fog(%d)= 2^2x%d = %.0f\n", k, k, pow(2,2*k));
   else if (f==-2 && g==-1)
         printf("gof(%d)= 2x2^%d = %.0f\n", k, k, 2 * pow(2,k));
   return 0;  
}