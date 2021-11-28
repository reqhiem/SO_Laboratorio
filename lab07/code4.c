#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int data = 0; //variable global que hace de dato compartido
int aux;
pthread_mutex_t mutex;

//funcion para el consumidor
void* consumer(void* arg) {
    while (1){
        while (data == 0){
            ; //esperar mientras el dato esté vacío
        }

        pthread_mutex_lock(&mutex);
        printf("Cuánto deseas consumir de %d: ", data);
        scanf("%d", &aux);
        printf("Consumido %d de %d...\n", aux, data);
        data -= aux;
        pthread_mutex_unlock(&mutex);
    }
    
}

//Funcion para el productor de datos
void* producer(void* arg) {
    while (1){
        while (data != 0){
            ; //esperar mientras el dato no sea 0
        }
        pthread_mutex_lock(&mutex);
        data = rand() % 100; //generar aleatorio
        printf("Producido %d\n", data);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    srand(time(NULL));

    pthread_t consumer_thread, producer_thread;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, (void*)NULL);
    pthread_create(&consumer_thread, NULL, consumer, (void*)NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}