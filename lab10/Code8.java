import java.util.concurrent.locks.ReentrantLock;

public class Code8 {
    private static int numThreads = 1000;
    public static void main(String[ ] args) {
        
        Task[] tasks = new Task[numThreads];
        Thread[] workers = new Thread[numThreads];

        for(int i=0; i<numThreads; i++) {
            tasks[i] = new Task();
            tasks[i].setID(i+1);
            workers[i] = new Thread(tasks[i]);
        }

        for(int i=0; i<numThreads; i++) {
            workers[i].start();
        }
        
        for(int i=0; i<numThreads; i++) {
            try {
                workers[i].join();
            }
            catch (InterruptedException ie) { }
        }
    }
}

class Task implements Runnable {
    private int ID;
    public static ReentrantLock lock;

    public Task(){
        lock = new ReentrantLock();
    }

    public void run(){
        work();
    }
    public void work(){
        lock.lock();
        try{
            System.out.println("Thread " + ID);
        }finally{
            lock.unlock();
        }
    }
    public void setID(int id) { ID = id; }
}