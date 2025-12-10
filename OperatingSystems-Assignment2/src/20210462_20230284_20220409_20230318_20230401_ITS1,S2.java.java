import java.util.Random;
import java.util.Scanner;

class Buffer {
    private String[] queue;
    private int size;
    private int count;
    private int front;
    private int rear;

    public Buffer(int size) {
        this.size = size;
        this.queue = new String[size];
        this.count = 0;
        this.front = 0;
        this.rear = 0;
    }

    public void addCar(String carId) {
        if (count < size) {
            queue[rear] = carId;
            rear = (rear + 1) % size;
            count++;
        }
    }

    public String removeCar() {
        if (count > 0) {
            String carId = queue[front];
            front = (front + 1) % size;
            count--;
            return carId;
        }
        return null;
    }
}
class Semaphore {
    protected int value = 0;

    protected Semaphore() {
        value = 0;
    }

    protected Semaphore(int initial) {
        value = initial;
    }

    public synchronized void P() {
        value--;
        if (value < 0) {
            try {
                wait();
            } catch(InterruptedException e) {}
        }
    }

    public synchronized void V() {
        value++;
        if (value <= 0) {
            notify();
        }
    }
}
class Pump extends Thread {
    private int pumpId;
    private Buffer buffer;
    private Semaphore spaces;
    private Semaphore elements;
    private Semaphore mutex;
    private Semaphore pumps;

    public Pump(int pumpId, Buffer buffer, Semaphore spaces, Semaphore elements, Semaphore mutex, Semaphore pumps) {
        this.pumpId = pumpId;
        this.buffer = buffer;
        this.spaces = spaces;
        this.elements = elements;
        this.mutex = mutex;
        this.pumps = pumps;
    }

    public void run() {
        while (ServiceStation.getCarsProcessed() < ServiceStation.getTotalCars()) {
            try {
                elements.P();
                if (ServiceStation.getCarsProcessed() >= ServiceStation.getTotalCars()) {
                    elements.V();
                    break;
                }
                mutex.P();
                String carId = buffer.removeCar();
                mutex.V();
                spaces.V();
                pumps.P();

                System.out.println("Pump " + pumpId + ": " + carId + " Occupied");
                System.out.println("Pump " + pumpId + ": " + carId + " login");
                System.out.println("Pump " + pumpId + ": " + carId + " begins service at Bay " + pumpId);

                try {
                    Thread.sleep(2000 + new Random().nextInt(3000));
                    //Thread.sleep(4000);
                } catch (InterruptedException e) {
                    if (ServiceStation.getCarsProcessed() >= ServiceStation.getTotalCars()) {
                        pumps.V();
                        break;
                    }
                }
                System.out.println("Pump " + pumpId + ": " + carId + " finishes service");
                System.out.println("Pump " + pumpId + ": Bay " + pumpId + " is now free");
                pumps.V();

                ServiceStation.carProcessed();

            } catch (Exception e) {
                if (ServiceStation.getCarsProcessed() >= ServiceStation.getTotalCars()) {
                    break;
                }
            }
        }
    }
}
class Car extends Thread {
    private String carId;
    private Buffer buffer;
    private Semaphore spaces;
    private Semaphore elements;
    private Semaphore mutex;

    public Car(String carId, Buffer buffer, Semaphore spaces, Semaphore elements, Semaphore mutex) {
        this.carId = carId;
        this.buffer = buffer;
        this.spaces = spaces;
        this.elements = elements;
        this.mutex = mutex;
    }

    public void run() {
        System.out.println(carId + " arrived");
        if (WaitingQueueFull()) {
            System.out.println(carId + " arrived and waiting");
        }
        spaces.P();
        mutex.P();
        buffer.addCar(carId);
        System.out.println(carId + " entered the queue");
        mutex.V();
        elements.V();
    }

    private boolean WaitingQueueFull() {
        synchronized (spaces) {
            return spaces.value <= 0;
        }
    }
}
class ServiceStation {
    private static int carsProcessed = 0;
    private static int totalCars;
    private static final Object SimulationEnd = new Object();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int waitingAreaCapacity;
        while (true) {
            System.out.print("Waiting area capacity: ");
            waitingAreaCapacity = scanner.nextInt();
            if (waitingAreaCapacity >= 1 && waitingAreaCapacity <= 10) {
                break;
            } else {
                System.out.println("Error: Waiting area capacity must be between 1 and 10. Please try again.");
            }
        }

        System.out.print("Number of service bays (pumps): ");
        int numPumps = scanner.nextInt();

        scanner.nextLine();

        System.out.print("Cars arriving (order): ");
        String carsInput = scanner.nextLine();
        String[] carIds = carsInput.split(",\\s*");
        totalCars = carIds.length;

        Buffer buffer = new Buffer(waitingAreaCapacity);
        Semaphore empty = new Semaphore(waitingAreaCapacity);
        Semaphore full = new Semaphore(0);
        Semaphore mutex = new Semaphore(1);
        Semaphore pumps = new Semaphore(numPumps);

        Pump[] pumpThreads = new Pump[numPumps];
        for (int i = 0; i < numPumps; i++) {
            pumpThreads[i] = new Pump(i + 1, buffer, empty, full, mutex, pumps);
            pumpThreads[i].start();
        }
        Car[] carThreads = new Car[totalCars];
        for (int i = 0; i < totalCars; i++) {
            String carId = carIds[i].trim();
            carThreads[i] = new Car(carId, buffer, empty, full, mutex);
            carThreads[i].start();
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }

        for (int i = 0; i < totalCars; i++) {
            try {
                carThreads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        waitForAllCarsProcessed();
        for (int i = 0; i < numPumps; i++) {
            pumpThreads[i].interrupt();
        }
        System.out.println("All cars processed; simulation ends");
        scanner.close();
    }

    private static void waitForAllCarsProcessed() {
        synchronized (SimulationEnd) {
            while (carsProcessed < totalCars) {
                try {
                    SimulationEnd.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void carProcessed() {
        synchronized (SimulationEnd) {
            carsProcessed++;
            if (carsProcessed >= totalCars) {
                SimulationEnd.notifyAll();
            }
        }
    }

    public static int getTotalCars() {
        return totalCars;
    }

    public static int getCarsProcessed() {
        synchronized (SimulationEnd) {
            return carsProcessed;
        }
    }
}