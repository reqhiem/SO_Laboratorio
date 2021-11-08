// Nos dá el PPID y el PID
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
  printf( "Proceso hijo PID = %d\n", getpid() );
  printf( "Proceso padre PPID = %d\n", getppid() );

  exit(0);

}