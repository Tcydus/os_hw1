package com.company;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Main {

    static int philosopher = 5;
    static philosopher philosophers[] = new philosopher[philosopher];
    static chopstick chopsticks[] = new chopstick[philosopher];

    static class chopstick {

        public Semaphore mutex = new Semaphore(1);

        void grab() {
            try {
                mutex.acquire();
            }
            catch (Exception e) {
                e.printStackTrace(System.out);
            }
        }

        void release() {
            mutex.release();
        }

        boolean isFree() {
            return mutex.availablePermits() > 0;
        }

    }

    static class philosopher extends Thread {

        public int number;
        public chopstick leftchopstick;
        public chopstick rightchopstick;
        public int done = 0;
        public boolean waiting = False;

        philosopher(int num, chopstick left, chopstick right) {
            number = num;
            leftchopstick = left;
            rightchopstick = right;
        }

        public void run(){

            while (true) {
                if (!waiting){
                    leftchopstick.grab();
                    System.out.println("philosopher " + (number+1) + " grabs left chopstick.");
                    rightchopstick.grab();
                    System.out.println("philosopher " + (number+1) + " grabs right chopstick.");
                    eat();
                    leftchopstick.release();
                    System.out.println("philosopher " + (number+1) + " releases left chopstick.");
                    rightchopstick.release();
                    System.out.println("philosopher " + (number+1) + " releases right chopstick.");
                    done += 1;
                }
                else {
                    
                    try {
                        Thread.sleep(1000);
                        waiting = false;
                    }
                    catch (Exception e) {
                        waiting = false;
                        e.printStackTrace(System.out);
                        
                    }
                }
            }
        }

        void eat() {
            try {
                int sleepTime = ThreadLocalRandom.current().nextInt(0, 1000);
                System.out.println("philosopher " + (number+1) + " eats for " + sleepTime);
                Thread.sleep(sleepTime);
            }
            catch (Exception e) {
                e.printStackTrace(System.out);
            }
        }

        void setWait(int waiting_thread_no){
            if (waiting_thread_no != number){
                waiting = true;
            }
        }
    }

    public static void main(String argv[]) {

        for (int i = 0; i < philosopher; i++) {
            chopsticks[i] = new chopstick();
        }

        for (int i = 0; i < philosopher; i++) {
            philosophers[i] = new philosopher(i, chopsticks[i], chopsticks[(i + 1) % philosopher]);
            philosophers[i].start();
        }

        while (true) {
            try {
                // sleep 1 sec
                Thread.sleep(1000);

                // check for deadlock
                boolean deadlock = true;
                for (chopstick f : chopsticks) {
                    if (f.isFree()) {
                        deadlock = false;
                        break;
                    }
                }
                if (deadlock) {
                    Thread.sleep(1000);
                    System.out.println("Everyone Eats");
                    break;
                }

                int unreason_i = -1;
                for (philosopher f : philosophers) {
                    if (f.done == 5) {
                        for (int i = 0; i < 5; i++) {
                            if ( philosophers[i].done = 0) {
                                unreason_i = i ;
                            }
                          }
                    }
                }

                for (philosopher f : philosophers) {
                    f.setWait(unreason_i);
                }

                
            }
            catch (Exception e) {
                e.printStackTrace(System.out);
            }
        }

        System.out.println("Exit The Program!");
        System.exit(0);
    }

}