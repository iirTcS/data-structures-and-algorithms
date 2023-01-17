import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class Test {
    int nrOfSets = 4;
    int nrOfSearchedNodes = 3;
    int nrOfNumbers = 6;
    private LinkedList<HashSet<Integer>> sets = new LinkedList<>(List.of(
            new HashSet<>(Set.of(1,2,3)),
            new HashSet<>(Set.of(2,4,5)),
            new HashSet<>(Set.of(2,3,4)),
            new HashSet<>(Set.of(5,6))
    ));

    public void formulateOracleQuestion() throws IOException {
        int V = this.nrOfSearchedNodes * this.nrOfSets;
        int count = 0;

        StringBuilder clauses = new StringBuilder();
        for (int i = 0; i < this.nrOfSearchedNodes; i++) {
            for (int j = 1; j <= this.nrOfSets; j++) {
                clauses.append(j + i * this.nrOfSets).append(" ");
            }
            clauses.append(" 0\n");
            count += 1;
        }

        for (int i = 0; i < this.nrOfSearchedNodes; i++) {
            for (int j = 1; j <= this.nrOfSets; j++) {
                for (int k = j + 1; k <= this.nrOfSets; k++) {
                    clauses.append("!").append(j + i * this.nrOfSets)
                            .append(" !").append(k + i * this.nrOfSets).append(" 0\n");
                    count += 1;
                }
            }
        }


        for (int j = 1; j <= this.nrOfSets; j++) {
            for (int i = 0; i < this.nrOfSearchedNodes; i++) {
                clauses.append("!").append(j + i * this.nrOfSets).append(" ");
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
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Trial trial = new Trial();
        trial.readProblemData();
        trial.formulateOracleQuestion();
    }
}
