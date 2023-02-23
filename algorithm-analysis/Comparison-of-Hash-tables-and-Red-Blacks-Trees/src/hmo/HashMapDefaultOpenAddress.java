package hmo;

import hashing.Hashing;

public class HashMapDefaultOpenAddress {

    private final int hSize;
    private final Integer[] buckets;


    public HashMapDefaultOpenAddress(int hSize) {
        buckets = new Integer[hSize];
        this.hSize = hSize;
    }


    public void insert(int key) {
        int hash = Hashing.Division(key, hSize);
        buckets[hash] = key;
    }

    public void delete(int key) {
        int hash = Hashing.Division(key, hSize);
        buckets[hash] = null;
    }

    public boolean contains(int key) {
        int hash = Hashing.Division(key, hSize);
        return buckets[hash] != null;
    }

    public void swap(int previousKey, int newKey) {
        if (contains(previousKey)) {
            this.delete(previousKey);
            this.insert(newKey);
        }
    }

    public String print() {
        StringBuilder toReturn = new StringBuilder();
        for (int i = 0; i < hSize; i++) {
            if (buckets[i] != null) {
                toReturn.append(buckets[i]).append(" ");
            }
        }
        toReturn.append("\n");
        return toReturn.toString();
    }
}
