import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

interface Logger {
    void log(String msg);
}

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

    public synchronized boolean WaitingQueueFull() {
        return count >= size;
    }
}

class Semaphore {
    protected int value = 0;

    protected Semaphore() { value = 0; }

    protected Semaphore(int initial) { value = initial; }

    public synchronized void P() {
        value--;
        if (value < 0) {
            try { wait(); } catch(InterruptedException e) {}
        }
    }

    public synchronized void V() {
        value++;
        if (value <= 0) { notify(); }
    }
}

class Pump extends Thread {
    private int pumpId;
    private Buffer buffer;
    private Semaphore spaces;
    private Semaphore elements;
    private Semaphore mutex; 
    private Semaphore pumps;
    private Logger logger;
    private JLabel pumpLabel;
    private DefaultListModel<String> queueModel;

    private final Font labelFont = new Font("Segoe UI", Font.PLAIN, 18);

    public Pump(int pumpId, Buffer buffer, Semaphore spaces, Semaphore elements, Semaphore mutex, Semaphore pumps, Logger logger, JLabel pumpLabel, DefaultListModel<String> queueModel) {
        this.pumpId = pumpId;
        this.buffer = buffer;
        this.spaces = spaces;
        this.elements = elements;
        this.mutex = mutex;
        this.pumps = pumps;
        this.logger = logger;
        this.pumpLabel = pumpLabel;
        this.queueModel = queueModel;

        SwingUtilities.invokeLater(() -> {
            pumpLabel.setOpaque(true);
            pumpLabel.setFont(labelFont);
            pumpLabel.setHorizontalTextPosition(SwingConstants.RIGHT);
        });
    }

    private void updatePumpLabel(String text, Color background) {
        SwingUtilities.invokeLater(() -> {
            pumpLabel.setText("Pump " + pumpId + ": " + text);
            pumpLabel.setBackground(background);
        });
    }

    private void removeFromQueueModel(String carId) {
        SwingUtilities.invokeLater(() -> {
            queueModel.removeElement(carId);
        });
    }

    @Override
    public void run() {
        while (true) {
            try {
                elements.P();
                mutex.P();
                String carId = buffer.removeCar();
                mutex.V();
                spaces.V();

                if (carId == null) {
                    if (ServiceStationGUI.getCarsProcessed() >= ServiceStationGUI.getTotalCars()) break;
                    continue;
                }

                removeFromQueueModel(carId);

                pumps.P();

                updatePumpLabel(carId + " Occupied", Color.RED);
                logger.log("Pump " + pumpId + ": " + carId + " occupied");
                logger.log("Pump " + pumpId + ": " + carId + " login");
                logger.log("Pump " + pumpId + ": " + carId + " begins service at Pump " + pumpId);

                Thread.sleep(2000 + new Random().nextInt(3000));

                logger.log("Pump " + pumpId + ": " + carId + " finishes service");
                logger.log("Pump " + pumpId + ": Pump " + pumpId + " is now free");
                updatePumpLabel("is now free", Color.GREEN);

                pumps.V();
                ServiceStationGUI.carProcessed();

                if (ServiceStationGUI.getCarsProcessed() >= ServiceStationGUI.getTotalCars())
                    break;

            }
            // catch (InterruptedException e) { break; }
            catch (Exception e) { break; }
        }
    }
}

class Car extends Thread {
    private String carId;
    private Buffer buffer;
    private Semaphore spaces;
    private Semaphore elements;
    private Semaphore mutex;
    private Logger logger;
    private DefaultListModel<String> queueModel;

    public Car(String carId, Buffer buffer, Semaphore spaces, Semaphore elements, Semaphore mutex, Logger logger, DefaultListModel<String> queueModel) {
        this.carId = carId;
        this.buffer = buffer;
        this.spaces = spaces;
        this.elements = elements;
        this.mutex = mutex;
        this.logger = logger;
        this.queueModel = queueModel;
    }

    private void addToQueueModel(String carId) {
        SwingUtilities.invokeLater(() -> {
            queueModel.addElement(carId);
        });
    }

    public void run() {
        logger.log(carId + " arrived");

        if (buffer.WaitingQueueFull()) {
            logger.log(carId + " arrived and waiting");
        }

        spaces.P();
        mutex.P();
        buffer.addCar(carId);
        addToQueueModel(carId);
        logger.log(carId + " entered the queue");
        mutex.V();
        elements.V();
    }
}

class ServiceStationGUI extends JFrame implements Logger {
    private DefaultListModel<String> logModel;
    private DefaultListModel<String> queueModel;
    private JTextField capacityField, pumpsField, carsField;
    private JButton startBtn;
    private JLabel[] pumpLabels;
    private JPanel pumpPanel;

    private static volatile int carsProcessed = 0;
    private static int totalCars;

    public static void carProcessed() { carsProcessed++; }
    public static int getCarsProcessed() { return carsProcessed; }
    public static int getTotalCars() { return totalCars; }

    public void log(String msg) {
        SwingUtilities.invokeLater(() -> logModel.addElement(msg));
    }

    public ServiceStationGUI() {
        setTitle("Car Service Simulation");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(0, 10));

        JPanel inputPanel = new JPanel(new GridLayout(2, 4, 10, 10));
        inputPanel.setBorder(BorderFactory.createTitledBorder("Simulation Setup"));

        capacityField = new JTextField("5");
        pumpsField = new JTextField("3");
        carsField = new JTextField("C1,C2,C3,C4,C5");
        startBtn = new JButton("Start Simulation");

        startBtn.setFont(new Font("Segoe UI", Font.BOLD, 15));
        startBtn.setBackground(Color.BLUE);
        startBtn.setForeground(Color.WHITE);
        startBtn.setHorizontalAlignment(SwingConstants.CENTER);
        startBtn.setVerticalAlignment(SwingConstants.CENTER);
        startBtn.setHorizontalTextPosition(SwingConstants.CENTER);
        startBtn.setVerticalTextPosition(SwingConstants.CENTER);

        inputPanel.add(new JLabel("Waiting area capacity:"));
        inputPanel.add(capacityField);
        inputPanel.add(new JLabel("Number of pumps:"));
        inputPanel.add(pumpsField);
        inputPanel.add(new JLabel("Cars (comma-separated):"));
        inputPanel.add(carsField);
        inputPanel.add(new JLabel(""));
        inputPanel.add(startBtn);

        add(inputPanel, BorderLayout.NORTH);

        JPanel centerPanel = new JPanel(new GridLayout(1, 2, 10, 0));

        queueModel = new DefaultListModel<>();
        JList<String> queueList = new JList<>(queueModel);
        queueList.setFont(new Font("Segoe UI", Font.BOLD, 18));
        JScrollPane queueScroll = new JScrollPane(queueList);
        queueScroll.setBorder(BorderFactory.createTitledBorder("Waiting Queue"));
        centerPanel.add(queueScroll);

        pumpPanel = new JPanel(new GridLayout(0, 1, 10, 10));
        pumpPanel.setBorder(BorderFactory.createTitledBorder("Pumps"));
        centerPanel.add(pumpPanel);

        add(centerPanel, BorderLayout.CENTER);

        logModel = new DefaultListModel<>();
        JList<String> logList = new JList<>(logModel);
        JScrollPane logScroll = new JScrollPane(logList);
        logScroll.setPreferredSize(new Dimension(0, 200));
        logScroll.setBorder(BorderFactory.createTitledBorder("Event Log"));
        add(logScroll, BorderLayout.SOUTH);

        startBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                startSimulation();
            }
        });

        setVisible(true);
    }

    private void startSimulation() {
        int waitingAreaCapacity;
        try {
            waitingAreaCapacity = Integer.parseInt(capacityField.getText());
            if (waitingAreaCapacity < 1 || waitingAreaCapacity > 10) {
                JOptionPane.showMessageDialog(this,
                        "queue size must be between 1 and 10 ",
                        "Invalid Capacity",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this,
                    "Please enter a valid number for queue size",
                    "Invalid Input",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        int numPumps;
        try {
            numPumps = Integer.parseInt(pumpsField.getText());
            if (numPumps <= 0) {
                JOptionPane.showMessageDialog(this,
                        "Number of pumps must be at least 1",
                        "Invalid Pump Count",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this,
                    "Please enter a valid number for pumps",
                    "Invalid Input",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        logModel.clear();
        queueModel.clear();
        pumpPanel.removeAll();
        startBtn.setEnabled(false);
        revalidate();
        repaint();

        String[] carIds = carsField.getText().split(",\\s*");
        totalCars = carIds.length;
        carsProcessed = 0;

        Buffer buffer = new Buffer(waitingAreaCapacity);
        Semaphore spaces = new Semaphore(waitingAreaCapacity);
        Semaphore elements = new Semaphore(0);
        Semaphore mutex = new Semaphore(1);
        Semaphore pumps = new Semaphore(numPumps);

        pumpLabels = new JLabel[numPumps];
        Font pumpFont = new Font("Segoe UI", Font.PLAIN, 18);
        for (int i = 0; i < numPumps; i++) {
            pumpLabels[i] = new JLabel("Pump " + (i + 1) + ": Free", SwingConstants.CENTER);
            pumpLabels[i].setFont(pumpFont);
            pumpLabels[i].setBackground(Color.GREEN);
            pumpLabels[i].setOpaque(true);
            pumpPanel.add(pumpLabels[i]);
        }

        revalidate();

        Pump[] pumpThreads = new Pump[numPumps];
        for (int i = 0; i < numPumps; i++) {
            pumpThreads[i] = new Pump(i + 1, buffer, spaces, elements, mutex, pumps, this, pumpLabels[i], queueModel);
            pumpThreads[i].start();
        }

        Car[] carThreads = new Car[totalCars];
        for (int i = 0; i < totalCars; i++) {
            String carId = carIds[i].trim();
            carThreads[i] = new Car(carId, buffer, spaces, elements, mutex, this, queueModel);
            carThreads[i].start();
            try { Thread.sleep(50); } catch (Exception e) {}
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (getCarsProcessed() < getTotalCars()) {
                    try {
                        Thread.sleep(100);
                    } catch (Exception e) {
                    }
                }
                log("All cars processed; simulation ends");
                SwingUtilities.invokeLater(new Runnable() {
                    @Override
                    public void run() {
                        startBtn.setEnabled(true);
                    }
                });
            }
        }).start();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ServiceStationGUI());
    }
}