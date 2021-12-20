#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <vector>

std::mutex mtx;           // mutex para la sección crítica
std::once_flag flag;

void print_block (int n, char c) {
    //unique_lock tiene varios constructores, donde std::defer_lock no establece el estado de bloqueo
    std::unique_lock<std::mutex> my_lock (mtx, std::defer_lock);
    //Tratar de bloquear, si el bloqueo es exitoso, ejecutar
    //(Util para el escenario en que un trabajo se ejecuta regularmente, un hilo puede ser ejecutado, y el timestamp de actualización se puede utilizar para asistir)
    if(my_lock.try_lock()){
        for (int i=0; i<n; ++i)
            std::cout << c;
        std::cout << '\n';
    }
}

void run_one(int &n){
    std::call_once(flag, [&n]{n=n+1;}); //solo ejecuta una vez, para inicializar una variable estática
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