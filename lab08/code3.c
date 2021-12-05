#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/sem.h>

#define SEMKEY ((key_t) 400L)

// number de semaforos
#define NSEMS 2

// definir la clave
#define SHMKEY ((key_t) 7890)

typedef struct{
    int value;
} shared_mem;

shared_mem *total; // puntero a la memoria compartida

// estructura
int sem_id, sem_id2;

typedef union{
    int val;
    struct semid_ds *buf;
    ushort *array;
} semunion;

static struct sembuf OP = {0,-1,0};
static struct sembuf OV = {0,1,0};
struct sembuf *P =&OP;
struct sembuf *V =&OV;

//Funciones semáforo
int wait(){
  int status;
  status = semop(sem_id, P,1);
  return status;
}

int signal(){
  int status;
  status = semop(sem_id, V,1);
  return status;
}


//Esta función incrementa el valor de la variable compartida "total"
//con el objetivo de llegar a 100000
void process1 ();

//Esta función incrementa el valor de la variable compartida "total"
//con el objetivo de llegar a 300000
void process2 ();

//Esta función incrementa el valor de la variable compartida "total"
//con el objetivo de llegar a 300000
void process3 ();

int main(){

    int   shmid;
    int   pid1;
    int   pid2;
    int   pid3;
    int   ID;
    int   status;

    char *shmadd;
    shmadd = (char *) 0;

    //semaforos
    int semnum = 0;
    int value, value1;
    semunion semctl_arg;
    semctl_arg.val =1;

    // Crea los semaforos 
    sem_id = semget(SEMKEY, NSEMS, IPC_CREAT | 0666);
    if(sem_id < 0)
        printf("creating semaphore");

    sem_id2 = semget(SEMKEY, NSEMS, IPC_CREAT | 0666);
    if(sem_id2 < 0)
        printf("creating semaphore");

    // Inicializa los semaforos 
    value1 =semctl(sem_id, semnum, SETVAL, semctl_arg);

    value =semctl(sem_id, semnum, GETVAL, semctl_arg);
    if (value < 1)
        printf("Eror detected in SETVAL");

    // Crear y conectar a la memoria compartida
    if ((shmid = shmget (SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0){
        perror ("shmget");
        exit (1);
    }

    if ((total = (shared_mem *) shmat (shmid, shmadd, 0)) == (shared_mem *) -1){
        perror ("shmat");
        exit (0);
    }

    total->value = 0;
    if ((pid1 = fork()) == 0)
        process1();
    if ((pid1 != 0) && (pid2 = fork()) == 0)
        process2();
    if ((pid1 != 0 ) && (pid2 != 0) && (pid3 = fork()) == 0 )
        process3();

    waitpid(pid1, NULL, 0 );
    waitpid(pid2, NULL, 0 );
    waitpid(pid3, NULL, 0 );

    if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0)){
        waitpid(pid1);
        printf("Child with ID %d has just exited.\n", pid1);

        waitpid(pid2);      
        printf("Child with ID %d has just exited.\n", pid2);

        waitpid(pid3);
        printf("Child with ID %d has just exited.\n", pid3);

        if ((shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0)) == -1){
            perror ("shmctl");
            exit (-1);
        }

        printf ("\t\t  End of Program\n");

        // Desocupar semaforos
        semctl_arg.val = 0;
        status =semctl(sem_id, 0, IPC_RMID, semctl_arg);
        if( status < 0)
            printf("Error in removing the semaphore.\n");
    }
} 

//definicion de los procesos a ejecutar
void process1 (){
    int k = 0;
    while (k < 100000){
        //seccion critica
        wait();
        if (total->value < 600000) {
            total->value = total->value + 1;
        }
        signal();        
        k++;
    }
    printf ("From process1 total = %d\n", total->value);

}

void process2 (){
    int k = 0;
    while (k < 200000){
        //seccion critica
        wait();
        if (total->value < 600000) {
            total->value = total->value + 1;
        }
        signal();      
        k++;
    }

    printf ("El proceso 2 llegó a = %d\n", total->value);
}

void process3 (){
    int k = 0;

    while (k < 300000){
        //sección crítica
        wait();
        if (total->value < 600000) {
            total->value = total->value + 1;
        }
        signal();        
        k++;
    }

    printf ("El proceso 3 llegó a = %d\n", total->value);
}
