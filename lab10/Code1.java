public class Code1 {
    public static void main(String[ ] args) {
        Thread worker = new Thread(new Task());
        worker.start();
        try {
            worker.join();
        }
        catch (InterruptedException ie) { }
    }
}

class Task implements Runnable
{
    public void run() {
        System.out.println("Hola Mundo");
    }
}