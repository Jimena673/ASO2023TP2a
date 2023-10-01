#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int hermano1 = 0;
int hermano2 = 0;

#define NUM_HAMBURGUESAS 10

int turno = 1;

void *comer_hamburguesa(void *arg) {
    int hermano = *((int *)arg); 
    for (int i = 0; i < NUM_HAMBURGUESAS; i++) {
        while (1) {
            pthread_mutex_lock(&mutex);
            if (hermano == turno) {
            
                printf("Hermano %d comiendo hamburguesa %d\n", hermano, i + 1);

                if (hermano == 1) {
                    hermano1++;
                } else {
                    hermano2++;
                }

                turno = 3 - turno; 
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int hermano1 = 1;
    int hermano2 = 2;

    pthread_create(&thread1, NULL, comer_hamburguesa, &hermano1);
    pthread_create(&thread2, NULL, comer_hamburguesa, &hermano2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Hermano 1 comió %d hamburguesas\n", hermano1);
    printf("Hermano 2 comió %d hamburguesas\n", hermano2);

    return 0;
}

