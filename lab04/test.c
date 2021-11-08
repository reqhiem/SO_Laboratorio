#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


int A[] = {1,2,3,4,5};
int res = 0, l=0, r=4;
void *sumar(void *p1){
    for(int i=l; i<=r; i++) res += A[i];
}

int main(){
    pthread_t hilo1;

    int iret1 = pthread_create(&hilo1, NULL, sumar, NULL);


    pthread_join(hilo1, NULL);
    printf("%d\n", res);
    exit(0);
}
