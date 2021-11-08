#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int fd1[2], fd2[2];
    char buffer[30], buffer2[30];

    pid_t pid, pidNieto;

    pipe(fd1);
    pipe(fd2);

    pid = fork();
    
    switch (pid){
    case -1: //Error
        printf("Error al crear el proceso hijo\n");
        exit(-1);
        break;
    case 0:
        close(fd1[0]);
        printf("Escribe el padre... \n");
        write(fd1[1], "El padre dice hola", 20);

        pidNieto = fork();
        switch (pidNieto)
        {
        case -1:
            printf("Error al crear el proceso nieto\n");
            exit(-1);
            break;
        case 0:
            close(fd2[0]);
            printf("Escribe el nieto... \n");
            write(fd2[1], "El nieto dice hola", 20);
            break;
        default:
            close(fd2[1]);
            wait(NULL);
            printf("El padre lee al nieto: \n");
            read(fd2[0], buffer2, 20);
            printf("Mensaje leido: %s\n", buffer2);
            break;
        }
        break;
    default:
        close(fd1[1]);
        wait(NULL);
        printf("El abuelo lee al padre: \n");
        read(fd1[0], buffer, 20);
        printf("Mensaje leido: %s\n", buffer);
        break;
    }

    exit(0);
}