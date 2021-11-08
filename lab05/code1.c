#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    pid_t idProceso;
    int estadoHijo;
    int descriptorTuberia[2];
    char buffer[100];
    if(pipe(descriptorTuberia) == -1)
    {
        perror("No se puede crear Tuberia");
        exit(-1);
    }

    idProceso = fork();
    if (idProceso == -1)
    {
        perror("No puede crear proceso");
        exit(-1);
    }
    if(idProceso == 0)
    {
        close(descriptorTuberia[1]);
        read(descriptorTuberia[0], buffer, 8);
        printf("Hijo: Recibido \"%s\"\n", buffer);
        exit(0);
    }if(idProceso > 0)
    {
        close(descriptorTuberia[0]);
        printf("Padre: Envio\"Ciencia\"\n");
        strcpy(buffer, "Ciencia");
        write(descriptorTuberia[1], buffer, strlen(buffer) + 1);
        wait(&estadoHijo);
        exit(0);
    }

    return 1;
}
