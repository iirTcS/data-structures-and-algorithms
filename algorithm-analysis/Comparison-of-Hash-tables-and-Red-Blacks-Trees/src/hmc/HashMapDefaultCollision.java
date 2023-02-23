package hmc;


import hashing.Hashing;

import java.util.LinkedList;

public class HashMapDefaultCollision {

    private final int hSize;
    private final LinkedList<LinkedList<Integer>> buckets;


    public HashMapDefaultCollision() {
        this.hSize = 100;
        buckets = new LinkedList<>();
        for (int i = 0; i < hSize; i++) {
            buckets.add(new LinkedList<>());
        }
    }

    public void insert(int key) {
        int hash = Hashing.Division(key, hSize);
        buckets.get(hash).add(key);
    }

    public boolean delete(int key) {
        int hash = Hashing.Division(key, hSize);

        return buckets.get(hash).removeFirstOccurrence(key);
    }

    public boolean contains(int key) {
        for (LinkedList<Integer> bucket: buckets) {
            if (bucket.contains(key)) {
                return true;
            }
        }
        return false;
    }

    public void swap(int previousKey, int newKey) {
        if (this.delete(previousKey)) {
            this.insert(newKey);
        }
    }

    public String print() {
        StringBuilder toReturn = new StringBuilder();
        this.buckets.forEach(bucket -> bucket.forEach(integer -> toReturn.append(integer).append(" ")));
        toReturn.append("\n");
        return toReturn.toString();
    }
}
