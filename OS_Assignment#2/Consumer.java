import java.util.Queue;
public class Consumer implements Runnable {

    private String pumpId;
    private int bayNumber;
    private Queue<String> sharedQueue;
    private Semaphore empty;
    private Semaphore full;
    private Semaphore pumps;
    private Semaphore mutex;

    public Consumer(String id, int bayNum, Queue<String> queue, Semaphore empty, Semaphore full, Semaphore pumps,
            Semaphore mutex) {
        this.pumpId = id;
        this.bayNumber = bayNum;
        this.sharedQueue = queue;
        this.empty = empty;
        this.full = full;
        this.pumps = pumps;
        this.mutex = mutex;
    }

    @Override
    public void run() {
        while (true) {
            try {
                full.wait();
                pumps.wait();
                mutex.wait();

                String carName = sharedQueue.remove();
                System.out.println("• " + pumpId + ": " + carName + " Occupied");

                mutex.signal();
                empty.signal();

                System.out.println("• " + pumpId + ": " + carName + " login");
                System.out.println("• " + pumpId + ": " + carName + " begins service at Bay " + bayNumber);

                Thread.sleep((long) (Math.random() * 3000 + 3000));

                System.out.println("• " + pumpId + ": " + carName + " finishes service");
                System.out.println("• " + pumpId + ": Bay " + bayNumber + " is now free");

                pumps.signal();

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}