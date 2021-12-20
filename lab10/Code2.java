public class Code2 {
    public static void main(String[ ] args) {
        Task t1 = new Task();
        t1.setID(1); t1.setNumIter(10);
        Thread worker1 = new Thread(t1);

        Task t2 = new Task();
        t2.setID(2); t2.setNumIter(10);
        Thread worker2 = new Thread(t2);
        
        worker1.start();
        worker2.start();
        
        try {
            worker1.join();
            worker2.join();
        }
        catch (InterruptedException ie) { }
    }
}
class Task implements Runnable {
    private int ID;
    private int numIter;
    public void run( ) {
        work();
    }
    private void work() {
        for(int i=0; i< numIter; i++) {
            System.out.print( ID + ": Hola Mundo " + i);
        }
    }
    public void setID(int id) { ID = id; }
    public void setNumIter(int iter) { numIter = iter; }
}