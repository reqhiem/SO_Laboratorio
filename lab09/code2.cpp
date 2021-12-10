//Ejemplo de creacion de threads con funciones lambda

#include <iostream>
#include <thread>

int main(int argc, char const *argv[]){
    int id = 1;
    int numIter = 10;

    std::thread t1([id, numIter](){
        for(int i = 0; i < numIter; i++){
            std::cout << "Thread " << id << ": " << i << std::endl;
        }
    });

    t1.join();

    return 0;
}