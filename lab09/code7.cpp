#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <vector>

std::mutex mtx;           // mutex for critical section
std::once_flag flag;

void print_block (int n, char c) {
    //unique_lock has multiple sets of constructors, where std::defer_lock does not set the lock state
    std::unique_lock<std::mutex> my_lock (mtx, std::defer_lock);
    //Try to lock, if the lock is successful, execute
    //(Suitable for the scenario where a job is executed regularly, one thread can be executed, and the update timestamp can be used to assist)
    if(my_lock.try_lock()){
        for (int i=0; i<n; ++i)
            std::cout << c;
        std::cout << '\n';
    }
}

void run_one(int &n){
    std::call_once(flag, [&n]{n=n+1;}); //Only execute once, suitable for lazy loading; multi-threaded static variables
}

int main () {
    std::vector<std::thread> ver;
    int num = 0;
    for (auto i = 0; i < 10; ++i){
        ver.emplace_back(print_block,50,'*');
        ver.emplace_back(run_one, std::ref(num));
    }

    for (auto &hilo : ver){
        hilo.join();
    }
    
    std::cout << num << std::endl;
    return 0;
}