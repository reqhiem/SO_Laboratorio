#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define LEER 0
#define ESCRIBIR 1

char *frase = "Envia esto a traves de un tubo o pipe";
extern int errno;

int main()
{
    int fd[2], bytesLeidos;
    char mensaje[100];
    int control;

    //se crea la tuberia
    control = pipe(fd);
    if (control != 0){
        perror("pipe:");
        exit(errno);
    }

    //se crea el proceso hijo
    control = fork();
    switch (control)
    {
    case -1:
        perror("fork:");
        exit(errno);
        break;
    case 0:
        close(fd[LEER]);
        write(fd[ESCRIBIR], frase, strlen(frase)+1);
        close(fd[ESCRIBIR]);
        exit(0);
        break;
    default:
        close(fd[ESCRIBIR]);
        bytesLeidos = read(fd[LEER], mensaje, 100);
        printf("Leidos %d bytes : %s\n", bytesLeidos, mensaje);
        close(fd[LEER]);
        break;
    }
    exit(0);
}