package rbt;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

public class RBTMain {
    public static void main(String[] args) throws IOException {
        for (int i = 1; i < 41; i++) {
            testRBT(i);
        }
    }

    public static LinkedList<LinkedList<Long>> testRBT(int testNumber) throws IOException {
        /* I/O and statistic initialization */
        Scanner scan = new Scanner(new File("in/test"+ testNumber+ ".in"));
        BufferedWriter writer = new BufferedWriter(new FileWriter("out/test"+ testNumber + ".out4"));
        LinkedList<LinkedList<Long>> opTime = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            opTime.add(new LinkedList<>());
        }


        RBTree tree = new RBTree();

        int numberOfActions = scan.nextInt();
        long before = 0, after = 0;

        for (int i = 0; i < numberOfActions; i++) {
            int op = scan.nextInt();
            switch (op) {
                case 0 -> {
                    int key = scan.nextInt();
                    before = System.nanoTime();
                    tree.insert(key);
                    after = System.nanoTime();
                }
                case 1 -> {
                    int keyD = scan.nextInt();
                    before = System.nanoTime();
                    tree.delete(keyD);
                    after = System.nanoTime();
                }
                case 2 -> {
                    int keyC = scan.nextInt();
                    before = System.nanoTime();
                    boolean exists = tree.contains(keyC);
                    after = System.nanoTime();
                    writer.write((exists ? "1" : "0") + "\n");
                }
                case 3 -> {
                    int key1 = scan.nextInt();
                    int key2 = scan.nextInt();
                    before = System.nanoTime();
                    tree.swap(key1, key2);
                    after = System.nanoTime();
                }
                case 4 -> {
                    before = System.nanoTime();
                    String toPrint = tree.print();
                    after = System.nanoTime();
                    writer.write(toPrint);
                }
            }
            opTime.get(op).add(after - before);
        }

        /* I/O closing */
        writer.flush();
        scan.close();
        writer.close();
        return opTime;
    }
}
