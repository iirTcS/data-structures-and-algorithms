package hashing;

public class Hashing {
    public static int Division(int key, int mapSize) {
        int hash = key % mapSize;
        if (hash < 0) {
            hash += mapSize;
        }
        return hash;
    }

    public static int Multiply(int key, int mapSize) {
        return (int) Math.floor((mapSize * ((key * 0.65795) % 1)));
    }
}
