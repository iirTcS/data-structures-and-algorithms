# Comparison of Hash-tables and Red-Blacks Trees

`Author: Corneliu Rotari`

`Group : 323CD`

## Table of Contents

- [Description](#description)
- [Structure](#structure)
- [Exectuion](#exectuion)
- [Implementation](#implementation)

## Description

This repository is a study of 2 Data Structures, in performance and time, on different operations.
- Red-Black Trees are a self-balancing binary search tree in which each node contains an extra bit of information for denoting the color of the node, either red or black.
- Hash-Tables is an array of fixed size containing data items with unique keys, together with a function called a hash function that maps keys to indices in the table. 

## Structure
```
.
├── classes - the compiled app
│   ├── hashing
│   ├── hmo
│   ├── hmr
│   └── rbt
│
├── images - images generated for analysis
│
├── in - input tests
│ 
├── out - the results of the programs
│
├── results - performance results
│
└── src - the implementation
    │
    ├── hashing
    ├── hmo
    ├── hmc
    ├── hmr
    └── rbt
```


## Exectuion

To compile the code:

`make build`

To execute the best program by analysis:

`make run-best`

To run a specific program:

`make run-p1` `make run-p2`

To clean the execution

`make clean`

## Implementation

Every data structure has 5 operations:
- insert
- delete
- contains
- swap
- print

Each has its own starting function.

There are 3 different types hash tables:
- Open Address :
    - implementet using a static array
    - basic operations
    - unchangeble in size
- Resizeble :
    - Initilized with 16 buckets
    - The most costly
    - Doubles in size, when the maximum number of buckets are full
- Collision:
    - If the same function hashes to a location it adds it into a linked list
    - Uses different types of hashes.
