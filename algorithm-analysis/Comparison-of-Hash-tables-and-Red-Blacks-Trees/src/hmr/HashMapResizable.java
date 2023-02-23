package hmr;

import hashing.Hashing;

import java.util.LinkedList;

// implementation of generic hashmaps using array of Linked Lists

public class HashMapResizable {

    private int size; // n (total number of key-value pairs)
    private LinkedList<LinkedList<Integer>> buckets; // N = buckets.length

    public HashMapResizable() {
        initBuckets(50000);
        size = 0;
    }

    // load factor = 0.75 means if we need to add 100 items, and we have added
    // 75, then adding 76th item it will double the size, copy all elements
    // & then add 76th item.

    private void initBuckets(int N) {
        buckets = new LinkedList<>();
        for (int i = 0; i < N; i++) {
            buckets.add(new LinkedList<>());
        }
    }

    public void insert(int value) {
        LinkedList<Integer> nodes = buckets.get(Hashing.Division(value, buckets.size()));
        nodes.add(value);
        size++;

        float loadFactor = 0.75f;
        if ((float) size / buckets.size() > loadFactor) {
            reHash();
        }
    }

    private void reHash() {
        LinkedList<LinkedList<Integer>> old = buckets;
        initBuckets(old.size() * 2);
        this.size = 0;

        for (LinkedList<Integer> nodes : old) {
            nodes.forEach(this::insert);
        }
    }

    public boolean delete(int key) {
        if (buckets.get(Hashing.Division(key, buckets.size())).removeFirstOccurrence(key)) {
            size--;
            return true;
        }
        return false;
    }


    public boolean contains(int value) {
        for (LinkedList<Integer> bucket: buckets) {
            if (bucket.contains(value)) {
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