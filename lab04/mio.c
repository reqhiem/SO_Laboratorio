#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

const int ms = 50000;

long long res = 0;
long long resComp = 0;
int A[50000];

void generateRandomArray(){
    srand(time(NULL));
    for(int i = 0; i < 50000; i++){
        A[i] = rand() % 2*ms;
        resComp += A[i];
    }
}

void *funcion1(void *p){
    for(int i=0; i<10000; i++) res += A[i];
}
void *funcion2(void *p){
    for(int i=10000; i<20000; i++) res += A[i];
}
void *funcion3(void *p){
    for(int i=20000; i<30000; i++) res += A[i];
}
void *funcion4(void *p) {
    for(int i=30000; i<40000; i++) res += A[i];
}
void *funcion5(void *p) {
    for(int i=40000; i<50000; i++) res += A[i];
}


int main(){
    pthread_t hilo1, hilo2, hilo3, hilo4, hilo5;
    generateRandomArray();

    int iret1, iret2, iret3, iret4, iret5;
    iret1 = pthread_create(&hilo1, NULL, funcion1, NULL);
    iret2 = pthread_create(&hilo2, NULL, funcion2, NULL);
    iret3 = pthread_create(&hilo3, NULL, funcion3, NULL);
    iret4 = pthread_create(&hilo4, NULL, funcion4, NULL);
    iret5 = pthread_create(&hilo5, NULL, funcion5, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);
    pthread_join(hilo5, NULL);

    printf("Suma con verificación: %lld\n", resComp);
    printf("Suma con Threads: %lld\n", res);
    exit(0);
}
