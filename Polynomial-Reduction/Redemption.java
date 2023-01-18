import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Redemption extends Task{

    private static class CardSet extends HashSet<String> {
        public int pos;
        public int nrOfContains;

        public CardSet(int pos) {
            super();
            this.pos = pos;
        }

        @Override
        public String toString() {
            return super.toString() + " pos=" + pos;
        }
    }

    protected TreeSet<CardSet> sets;
    protected HashSet<String> searchedCards;

    public Redemption() {
        this.sets = new TreeSet<>((o1, o2) -> {
            if (o2.size() == o1.size()) {
                return Integer.compare(o1.pos, o2.pos);
            }
            return Integer.compare(o2.size(), o1.size());
        });
        this.searchedCards = new HashSet<>();
        this.foundNodes = new ArrayList<>();
    }

    public void readProblemData() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String argLine = reader.readLine();
        String[] arg = argLine.split(" ");
        ArrayList<String> initialCards = new ArrayList<>();
        for (int i = 0; i < Integer.parseInt(arg[0]); i++) {
            initialCards.add(reader.readLine());
        }
        for (int i = 0; i < Integer.parseInt(arg[1]); i++) {
            String nameOfCard = reader.readLine();
            if (!initialCards.contains(nameOfCard)) {
                searchedCards.add(nameOfCard);
            }
        }

        for (int i = 0; i < Integer.parseInt(arg[2]); i++) {
            CardSet set = new CardSet(i + 1);
            String nrInThisSet = reader.readLine();
            for (int j = 0; j < Integer.parseInt(nrInThisSet); j++) {
                String name = reader.readLine();
                if (searchedCards.contains(name)) {
                    set.add(name);
                }
            }
            if (set.size() != 0) {
                this.sets.add(set);
            }
        }
        reader.close();
    }

    public void solve() throws IOException {
        this.readProblemData();
        for (CardSet set: this.sets) {
            if (this.searchedCards.size() == 0) {
                break;
            }
            for (String name : searchedCards) {
                if (set.contains(name)) {
                    this.foundNodes.add(set.pos);
                    this.searchedCards.removeAll(set);
                    break;
                }
            }
        }
        this.nrOfSearchedNodes = this.foundNodes.size();
        this.writeAnswer();
    }

    public void writeAnswer() {
        System.out.println(this.nrOfSearchedNodes);
        foundNodes.forEach(integer -> System.out.print(integer + " "));
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
    }

    public static void main(String[] args) {
        Redemption redemption = new Redemption();
        try {
            redemption.solve();
        } catch (Exception e ) {
            System.out.println("Problem at solver: " + e.getLocalizedMessage() + " \n"
                                + Arrays.toString(e.getStackTrace()));
        }
    }

}
