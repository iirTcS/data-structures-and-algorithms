import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

public class Rise extends Trial {
    @Override
    public void solve() throws IOException, InterruptedException {
        this.readProblemData();
        for (int i = 1; i <= this.nrOfSets; i++) {
            this.nrOfSearchedNodes = i;
            super.formulateOracleQuestion();
            this.askOracle();
            super.decipherOracleAnswer();
            if (Boolean.parseBoolean(this.solutionExists)) {
                break;
            }
        }
        this.writeAnswer();
    }

    @Override
    public void readProblemData() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String argLine = reader.readLine();
        String[] arg = argLine.split(" ");
        HashMap<String, Integer> mapOfName = new HashMap<>();
        ArrayList<String> initialCards = new ArrayList<>();
        for (int i = 0; i < Integer.parseInt(arg[0]); i++) {
            initialCards.add(reader.readLine());
        }
        int hashCode = 1;
        for (int i = 0; i < Integer.parseInt(arg[1]); i++) {
            String nameOfCard = reader.readLine();
            if (!initialCards.contains(nameOfCard)) {
                mapOfName.put(nameOfCard, hashCode);
                hashCode += 1;
            }
        }
        this.nrOfNumbers = mapOfName.size();

        for (int i = 0; i < Integer.parseInt(arg[2]); i++) {
            HashSet<Integer> set = new HashSet<>();
            String nrInThisSet = reader.readLine();
            for (int j = 0; j < Integer.parseInt(nrInThisSet); j++) {
                Integer mappingOfName = mapOfName.get(reader.readLine());
                if (mappingOfName != null) {
                    set.add(mappingOfName);
                }
            }
            if (set.size() != 0) {
                this.sets.add(set);
            }
        }
        this.nrOfSets = this.sets.size();
        reader.close();
    }

    @Override
    public void writeAnswer() {
        System.out.println(this.nrOfSearchedNodes);
        foundNodes.forEach(integer -> System.out.print(integer + " "));
    }

    public static void main(String[] args) {
        Rise rise = new Rise();
        try {
            rise.solve();
        } catch (Exception e) {
            System.out.println("Problem at solver " + e.getLocalizedMessage() + " "+ Arrays.toString(e.getStackTrace()));
        }
    }

}
