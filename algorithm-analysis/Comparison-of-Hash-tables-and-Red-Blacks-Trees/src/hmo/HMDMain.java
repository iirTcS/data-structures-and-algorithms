package hmo;

import hmc.HashMapDefaultCollision;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

public class HMDMain {

    public static void main(String[] args) throws IOException {
        for (int i = 1; i < 41; i++) {
            testOpenAddress(i);
        }
    }

    public static LinkedList<LinkedList<Long>> testOpenAddress(int testNumber) throws IOException {
        /* I/O and statistic initialization */
        Scanner scan = new Scanner(new File("in/test"+ testNumber+ ".in"));
        BufferedWriter writer = new BufferedWriter(new FileWriter("out/test"+ testNumber + ".out2"));
        LinkedList<LinkedList<Long>> opTime = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            opTime.add(new LinkedList<>());
        }


        /* Data Structures Initialization */
        HashMapDefaultOpenAddress hashMap = new HashMapDefaultOpenAddress(1_000_000);


        int numberOfActions = scan.nextInt();
        long before = 0, after = 0;

        for (int i = 0; i < numberOfActions; i++) {
            int op = scan.nextInt();
            switch (op) {
                case 0 -> {
                    int key = scan.nextInt();
                    before = System.nanoTime();
                    hashMap.insert(key);
                    after = System.nanoTime();
                }
                case 1 -> {
                    int keyDe = scan.nextInt();
                    before = System.nanoTime();
                    hashMap.delete(keyDe);
                    after = System.nanoTime();
                }
                case 2 -> {
                    int keyC = scan.nextInt();
                    before = System.nanoTime();
                    boolean exists = hashMap.contains(keyC);
                    after = System.nanoTime();
                    writer.write((exists ? "1" : "0") + "\n");
                }
                case 3 -> {
                    int key1 = scan.nextInt();
                    int key2 = scan.nextInt();
                    before = System.nanoTime();
                    hashMap.swap(key1, key2);
                    after = System.nanoTime();
                }
                case 4 -> {
                    before = System.nanoTime();
                    String toPrint = hashMap.print();
                    after = System.nanoTime();
                    writer.write(toPrint);
                }
            }
            opTime.get(op).add(after - before);
        }

        /* I/O closing */
        scan.close();
        writer.flush();
        writer.close();
        return opTime;
    }
}
