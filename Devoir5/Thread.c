#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5  // 5 thread par defaut

pthread_t tid[N];
int compteur = 0;
pthread_mutex_t mutex;

void *incremente(void *arg) {
   while (1){
    pthread_mutex_lock(&mutex);  
    compteur++;
    printf("Thread %d\n", compteur);
    for (int i = 0; i < 1000000; i++);
    printf("Fin de la tâche du Thread %d\n", compteur);
    if(compteur==5)
       compteur = 0;
    pthread_mutex_unlock(&mutex);  
   }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex,NULL);  

    // Par defaut on a choisi 5 thread qui seront exécuté en boucle

    for (int i = 0; i < N; i++) {
        if (pthread_create(&tid[i], NULL, incremente, NULL) != 0) {
            perror("pthread_cree");
            exit(1);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(tid[i],NULL);
    }

    pthread_mutex_destroy(&mutex);  
    return 0;
}
