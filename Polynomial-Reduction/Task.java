import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

public abstract class Task {

    protected int nrOfNumbers;
    protected int nrOfSets;
    protected int nrOfSearchedNodes;
    protected String conf = "p cnf ";
    protected String solutionExists = "";
    protected List<Integer> foundNodes = null;
    protected final String oracleInput = "sat.cnf";
    protected final String oracleOutput = "sat.sol";
    public abstract void solve() throws IOException, InterruptedException;

    public abstract void readProblemData() throws IOException;

    public abstract void writeAnswer();

    public void askOracle() throws IOException, InterruptedException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.redirectErrorStream(true);
        builder.command("python3", "sat_oracle.py", this.oracleInput, this.oracleOutput);
        Process process = builder.start();
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String buffer;
        StringBuilder output = new StringBuilder();


        while ((buffer = in.readLine()) != null) {
            output.append(buffer).append("\n");
        }

        int exitCode = process.waitFor();

        if (exitCode != 0) {
            System.err.println("Error encountered while running oracle");
            System.err.println(output);
            System.exit(-1);
        }

    }
}