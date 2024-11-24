#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 10  //par defaut notre N vaut 10

int compteur=0, i=0;
sem_t semSecondaire, semTertiaire;

void *fthreadsecondaire(void *arg) {
    while(1){
        sem_wait(&semSecondaire);
        for ( i = 1; i <= N; i++)
          printf("%d \n", i);
        sem_post(&semTertiaire);
    }
    pthread_exit(NULL);
}

void *fthreadtertiaire(void *arg) {
    while(1){
        sem_wait(&semTertiaire);
        for ( i = -; i >= -N; i--)
          printf("%d \n", i);
        sem_post(&semSecondaire);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t th1, th2;
    int resultat;
    resultat = sem_init(&semSecondaire, 0, 1);

    if(resultat==-1) {
        perror("Erreur d'initialisation de la sémaphore");
        return 0;
    }

    resultat = sem_init(&semTertiaire, 0, 0);
    if(resultat==-1) {
        perror("Erreur d'initialisation de la sémaphore");
        return 0;
    }

    resultat=pthread_create(&th1, NULL, fthreadsecondaire, (void *)NULL);
    if(resultat==-1) {
        perror("Erreur de lancement du thread secondaire");
        return 0;
    }

    resultat = pthread_create(&th2, NULL, fthreadtertiaire, (void *)NULL);

    if(resultat==-1) {
        perror("Erreur de lancement du thread tertiaire");
        return 0;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&semSecondaire);
    sem_destroy(&semTertiaire);

    return 0;
}
