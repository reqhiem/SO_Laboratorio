//Ejemplo breve de creación de Thread

#include <thread>
#include <iostream>
//using namespace std;

void count(int id, int numIter){
    for(int i=0; i<numIter; i++){
        std::cout << "Thread " << id << ": " << i << std::endl;
    }
}

int main(int argc, char const *argv[]){
    std::thread t1(count, 1, 10);
    t1.join();

    return 0;
}


