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
    std::vector<std::thread> ver;   //Save the thread vector
    for(int i = 0; i < 20; ++i){
        std::thread t = std::thread(add, std::ref(num), std::ref(sum));
        ver.emplace_back(std::move(t)); //Save thread
    }   

    for(auto &hilo : ver){
        hilo.join();
    }
    //std::for_each(ver.begin(), ver.end(), std::mem_fn(&std::thread::join)); //join
    std::cout << sum << std::endl;
}