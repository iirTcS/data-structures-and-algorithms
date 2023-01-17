import java.io.*;
import java.util.*;

public class Trial extends Task {
    private int nrOfNumbers;
    private int nrOfSets;
    private int nrOfSearchedNodes;
    private String conf = "p cnf ";
    private String soltionExists = "";
    private List<Integer> nodes = null;
    private LinkedList<HashSet<Integer>> sets = new LinkedList<>();

    @Override
    public void solve() throws IOException, InterruptedException {
        this.readProblemData();
        this.formulateOracleQuestion();
        this.askOracle();
        this.decipherOracleAnswer();
        this.writeAnswer();

    }

    @Override
    public void readProblemData() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        String[] arg = line.split(" ");
        this.nrOfNumbers = Integer.parseInt(arg[0]);
        this.nrOfSets = Integer.parseInt(arg[1]);
        this.nrOfSearchedNodes = Integer.parseInt(arg[2]);

        for (int i = 0; i < this.nrOfSets; i++) {
            line = reader.readLine();
            arg = line.split(" ");
            HashSet<Integer> set = new HashSet<>();
            for (int j = 1; j < Integer.parseInt(arg[0]) + 1; j++) {
                set.add(Integer.parseInt(arg[j]));
            }
            this.sets.add(set);
        }
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
        FileWriter writer = new FileWriter(this.oracleInput);
        if (this.nrOfSearchedNodes == 1) {
            for (int i = 0; i < this.nrOfSets; i++) {
                Set<Integer> analyzed = this.sets.get(i);
                if (analyzed.size() == this.nrOfNumbers) {
                    boolean valid = true;
                    for (int j = 1; j <= this.nrOfNumbers; j++) {
                        if (!analyzed.contains(j)) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        writer.write(conf + 1 + " " + 1 + "\n" + (i + 1)+" 0");
                        writer.flush();
                        writer.close();
                        return;
                    }
                }
            }
        }

        int V = this.nrOfSearchedNodes * this.nrOfSets;
        int count = 0;

        StringBuilder clauses = new StringBuilder();
        for (int i = 0; i < this.nrOfSearchedNodes; i++) {
            for (int j = 1; j <= this.nrOfSets; j++) {
                clauses.append(j + i * this.nrOfSets).append(" ");
            }
            clauses.append("0\n");
            count += 1;

            for (int j = 1; j <= this.nrOfSets; j++) {
                for (int k = j + 1; k <= this.nrOfSets; k++) {
                    clauses.append("-").append(j + i * this.nrOfSets)
                            .append(" -").append(k + i * this.nrOfSets).append(" 0\n");
                    count += 1;
                }
            }
        }

        for (int j = 1; j <= this.nrOfSets; j++) {
            for (int i = 0; i < this.nrOfSearchedNodes; i++) {
                clauses.append("-").append(j + i * this.nrOfSets).append(" ");
            }
            clauses.append("0\n");
            count +=1;
        }

        for (int i = 1; i <= this.nrOfNumbers; i++) {
            for (int j = 0; j < this.nrOfSets; j++) {
                if (this.sets.get(j).contains(i)) {
                    for (int k = 0; k < this.nrOfSearchedNodes; k++) {
                        clauses.append(j + 1 + k * this.nrOfSets).append(" ");
                    }
                }
            }
            clauses.append("0\n");
            count += 1;
        }


        writer.write(conf + V + " " + count + "\n" + clauses);
        writer.flush();
        writer.close();
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(this.oracleOutput));
        this.soltionExists = reader.readLine();
        if (Boolean.parseBoolean(this.soltionExists)) {
            reader.readLine();
            this.nodes = Arrays.stream(reader.readLine().split(" "))
                    .map(Integer::parseInt)
                    .filter(integer -> integer > 0)
                    .map(integer -> {
                        if (integer % this.nrOfSets == 0) {
                            return this.nrOfSets;
                        }
                        return integer % this.nrOfSets;
                    })
                    .toList();
        }
    }

    @Override
    public void writeAnswer() throws IOException {
        System.out.println(this.soltionExists);
        if (Boolean.parseBoolean(this.soltionExists)) {
            System.out.println(this.nrOfSearchedNodes);
            nodes.forEach(integer -> System.out.print(integer + " "));
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Trial trial = new Trial();
        try {
            trial.solve();
        } catch (Exception e) {
            System.out.println("Problem at solver");
        }
    }
}
