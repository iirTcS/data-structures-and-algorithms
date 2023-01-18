# Polynomial Reduction

`Author : Rotari Corneliu`

---

- [Structure](#structure)
- [Description](#description)
  - [Trial](#trial)
  - [Rise](#rise)
  - [Redemption](#redemption)
- [Build and Run](#build-and-run)

---

## Structure

```bash
.
├── Makefile
├── README.md
├── Redemption.java
├── Rise.java
├── Task.java
├── Trial.java
├── check
├── install.sh
├── sat_oracle.py
├── tasks/
└── check_utils/
```

---

## Description

This project associates and models the applications of practical problems with NP-Hard problems.

Its main responsibility is to make a polynomial reduction to the SAT problem or to approximate a result in a specific time frame.

All the tests and references are in the [tasks'](tasks) folder.

Hierarchy of created classes:
```bash
└─Task.java  
    ├──> Trial.java ──────> Rise.java
    └──> Redemption.java
```
### Trial

**Complexity : O(n * m * lg m)**

The main idea of this task is to associate the problem given to the SAT problem to solve it < 8s.

The sets contain numbers, and we have to search if exists a combination of sets that can create a sequence of N numbers.

Steps taken:
1. Read the input and parse it into sets.
2. Transform the sets into 4 main group of clauses for the [sat_oracle](sat_oracle.py). 
   1. Only one set can be chosen at a given moment. So we create a variable for each set for a given moment in time.
   2. There cannot be 2 sets from the same moment in time. So we create individual clauses for every node in a given moment.
   3. If a node was chosen in a previous moment we cannot choose it again in a different moment in time.
   4. We specify all the sets in which a specific number exits.
3. Print all the clauses in a file and ask the oracle if a solution exists.
4. We decipher and write the output.

### Rise

**Complexity : O(n * m * lg m * k)**

Transform sets that contain words to the previous task to find the minimum of sets that are needed to create a combination of N words.
1. Read for the searched words, the words that we know already and the sets where to search.
2. Eliminate form the searched words the words that we know already.
3. Create the sets with the searched words and eliminate every word that is useless.
4. Map the words to a specific number as an id.
5. Call the previous task.
6. Translate the output to the given problem.

### Redemption 

**Complexity : O(n3)**


This exact approximation is to sort the sets created as in [Rise](#rise), except the mapping the words to an id,
ascending order by the number of elements in the set.
This way we maximise the chances of given set to have a majority of the searched words.
We traverse each set in this order and delete from the searched words every encounter of a new-found word.

---

## Build and Run

`make build` - compiles the source files and creates all the necessary files and dependencies. [makefile](Makefile)

`./check` - To run the project [check](check)
