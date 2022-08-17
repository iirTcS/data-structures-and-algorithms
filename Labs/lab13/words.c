#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  (*h) = malloc(sizeof(HashTable));
  (*h)->elements = calloc(size,sizeof(Element *));
  (*h)->size = size;
  (*h)->hashFunction = f;
}

int exists(HashTable *hashTable, Key key) {
  Element* i = hashTable->elements[hashTable->hashFunction(key, hashTable->size)];
      printf("yolo\n");


  for (Element* i = hashTable->elements[hashTable->hashFunction(key, hashTable->size)]; i != NULL; i = i->next) {    
    if (i == NULL) {
      return 0;
    }

    if (strcmp(i->key, key) == 0) {
      return 1;
    }
  }
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  if (exists(hashTable, key)) {
    long hash = hashTable->hashFunction(key, hashTable->size);
    for (Element *i = hashTable->elements[hash]; i != NULL; i = i->next) {
      if (strcmp(i->key, key) == 0) {
        return i->value;
      }
    }
  }
  return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  Element *new = malloc(sizeof(*new));
  strcpy(new->key,key);
  new->value = value;
  long hash = hashTable->hashFunction(key, hashTable->size);
  new->next = hashTable->elements[hash];
  hashTable->elements[hash] = new;
}

void deleteKey(HashTable *hashTable, Key key) {
  for (Element* i = hashTable->elements[hashTable->hashFunction(key, hashTable->size)]; i->next != NULL; i = i->next) {
    if (strcmp(i->key, key) == 0) {
       hashTable->elements[hashTable->hashFunction(key, hashTable->size)] = i->next;
       free(i);
       return;
    }
    if (strcmp(i->next->key, key) == 0) {
      Element*aux = i->next;
      i->next = i->next->next;
      free(aux);
      return;
    }
  }
}

void print(HashTable *hashTable) {
  for (int i = 0; i < hashTable->size; i++) {
    printf("Bucketul = %d : ", i);
    for (Element *j = hashTable->elements[i]; j->next != NULL ; j = j->next) {
      printf("[%s; %d]", j->key, j->value);
    }
    printf("\n");
  }
  
}

void freeHashTable(HashTable *hashTable) {
  for (int i = 0; i < hashTable->size; i++) {
    for (Element* j = hashTable->elements[i]; j->next != NULL; j = j->next) {
      Element*aux = j->next;
      free(j);
      j = aux;
    }
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  long h = 0;
  for (int i = 0; i < strlen(word) - 1; i++) {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);

  for (int i = 0; i < 27; i++) {
    Key word = malloc(sizeof(* word));
    fscanf(f1, "%s", word);

    if (exists(hashTable, word)) {
      long value = get(hashTable, word) + 1;
      deleteKey(hashTable,word);
      put(hashTable, word, value);
    } else {
      put(hashTable, word, 1);
    }
  }
  print(hashTable);



  
  
  // Cerinta 3

  // ...

  // Cerinta 4

  // ...

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
