import hmr.HMRMain;
import rbt.RBTMain;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Random;

public class TestsAndPerformanceReview {

    public static void test() throws IOException {
        ArrayList<Integer> tree = new ArrayList<>();
        BufferedWriter writer1 = new BufferedWriter(new FileWriter("in/test40.in"));
        Random random = new Random();

        for (int i = 1; i <= 50_000; i++) {
            int key = random.nextInt(1,1_00_000);
            writer1.write("0 " + key + "\n");
            tree.add(key);
        }


        for (int i = 0; i < 50_000; i++) {
            int key1 = random.nextInt(1, 1_000_000);
            int key2 = random.nextInt(1, 1_000_000);
            int oper = random.nextInt(0,5);
            writer1.write(oper + "");
            if (oper < 4) {
                if (oper == 2) {
                    key1 = tree.get(random.nextInt(1, tree.size()));
                }
                writer1.write(" " + key1);
            }
            if (oper == 3) {
                writer1.write(" " + key2);
            } else {
                writer1.write("\n2 " + key2);
            }
            writer1.write("\n");
        }

        for (int i = tree.size() - 1; i > 0;) {
            writer1.write("1 " + (tree.get(i)) + "\n");
            tree.remove(tree.get(i));
            i = tree.size() - 1;
        }
        writer1.close();
    }

    public static void main(String[] args) throws IOException {
        BufferedWriter writer1 = new BufferedWriter(new FileWriter("results_htr_50000.out"));
        LinkedList<LinkedList<LinkedList<Long>>> testResults = new LinkedList<>();

        for (int i = 1; i <= 40; i++) {
            for (int j = 0; j < 2; j++) {
//                Change this to performe new test
                HMRMain.testResizeble(i);
            }
//            And this
            testResults.add(HMRMain.testResizeble(i));
            System.out.println("Test " + i);
        }

        LinkedList<LinkedList<Float>> resultsOperation = new LinkedList<>();
        LinkedList<LinkedList<Integer>> operationNumber = new LinkedList<>();
        for (int i = 0; i < 5; i++) {
            resultsOperation.add(new LinkedList<>());
            operationNumber.add(new LinkedList<>());
        }

        for (int i = 0; i < 40; i++) {
            int operation = 0;
            for (LinkedList<Long> op: testResults.get(i)) {
                long sum = 0;
                for (Long time: op) {
                    sum += time;
                }

                if (op.size() != 0) {
                    Float av = (float) sum / (float) op.size();
                    resultsOperation.get(operation).add(av);
                    operationNumber.get(operation).add(op.size());
                }
                operation++;
            }
        }
        int oper = 0;
        for (LinkedList<Float> avt: resultsOperation) {
            writer1.write(oper + " av " + avt.toString() + "\n");
            writer1.write(oper + " nr " + operationNumber.get(oper).toString() + "\n");

            oper++;
        }
        writer1.flush();
        writer1.close();
    }
}