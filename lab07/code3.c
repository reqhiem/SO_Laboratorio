/**
 *  @autor: Joel Perca
 *  @descripcion: Programa en C para hallar la suma de los elementos de un arreglo
 *                de enteros con threads y uso de exclusión mutua.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

// maximo numero de threads
#define MAX_THREAD 4

// maximo tamaño de arreglo
#define MAX_SIZE 5000

int a[MAX_SIZE]; //arreglo a procesar
int part = 0; //contador de particiones
long long sum_total = 0; //suma total
pthread_mutex_t mutex; //mutex para suma total

void* sum_array(void* arg){
    // Cada thread calcula la suma de 1/4 del arreglo
	int thread_part = part++;

	for (int i = thread_part * (MAX_SIZE / 4); i < (thread_part + 1) * (MAX_SIZE / 4); i++){
		// bloqueo de la suma total
        pthread_mutex_lock(&mutex);
        sum_total += a[i];
        pthread_mutex_unlock(&mutex);
    }
}

// Funcion para generar el arreglo con valores aleatorios
void generate_array(){
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++){
        a[i] = rand() % (MAX_SIZE*2);
    }
}

//Funcion para sumar el arreglo de forma secuencial
long long sum_array_serial(){
    long long sum = 0;
    for (int i = 0; i < MAX_SIZE; i++){
        sum += a[i];
    }
    return sum;
}

// Driver Code
int main(){

	pthread_t threads[MAX_THREAD];
    pthread_mutex_init(&mutex, NULL);
    generate_array();

	// Creando los threads
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

    // Join de los threads. El thread principal espera a que todos los threads terminen
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

    printf("Suma del arreglo con threads y mutex: %lld\n", sum_total);
    printf("Suma del arreglo de forma secuencial: %lld\n", sum_array_serial());

	return 0;
}