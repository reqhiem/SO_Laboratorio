//Ejemplo con 20 threads y mutex con lock_guard

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>

std::mutex my_lock;

void add(int &num, int &sum){
    while(true){
        std::lock_guard<std::mutex> lock(my_lock);  
        if (num < 100){ //Operating conditions
            num += 1;
            sum += num;
        }   
        else {  //Exit conditions
            break;
        }   
    }   
}

int main(){
    int sum = 0;
    int num = 0;
    std::vector<std::thread> vect;   //Save the thread vector
    for(int i = 0; i < 20; ++i){
        std::thread t = std::thread(add, std::ref(num), std::ref(sum));
        vect.emplace_back(std::move(t)); //Save thread
    }   

    for(auto &hilo : vect){
        hilo.join();
    }
    std::cout << sum << std::endl;
}