//Ejemplo de creació de multiples threads con
// bloqueo mutex

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mt;

void count(int id, int numIter){
	for(int i=0; i<numIter; i++){
        //Bloqueo de sección crítica
        mt.lock();
		    std::cout << "Thread " << id << ":" << i << std::endl;
		mt.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main(int argc, char **argv){
	std::thread t1(count, 1, 10);
	std::thread t2(count, 2, 10);

	t1.join();
	t2.join();

	return 0;
}