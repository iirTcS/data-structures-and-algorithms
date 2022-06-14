# PHANTOM GHOSTDAG
author: Rotari Corneliu
group : 313CD
## Main
1. Cream graful din fisier
    - Citim elementele si dupa toate nodurile adiacente
    - Printarea grafului (pentru debugging)
    - add_edge - adauga o legatura dintre doua noduri
2. In dependenta de argumentel impuse se alege tipul taskului

## Task1
Verificam daca arborele are ciclii sau nu.
Incepand cu fiecare nod din graf, folosim dfs pentru a parcurge toate nodurile adiacente si pentru a verifica daca exista un ciclu in aceast nod.
Daca un ciclu este intalnit functia intoarce valoare negativa.

## Task2
### Past
Folosind un dfs, parcurgem toate nodurile adiacente. Primul nod este printat automat ,iar cu ajutorul functiei print_sorted printam toate nodurile necesare sortate in ordine crescatoare.
