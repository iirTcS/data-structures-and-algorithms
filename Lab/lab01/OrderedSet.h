#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
  long max = set->size, min = 0;
  while(min<=max){
    long mid = (max+min)/2;
    if (element == set->elements[mid]){
      return 1;
    }
    if (element < set->elements[mid]){
      max = mid - 1;
    } else {
      min = mid + 1;
    }
  }
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/
int comp_cresc (const void *a, const void *b) {
    return (*(const T*)a)- (*(const T*)b);
}

void add(OrderedSet* set, const T newElement) {
  if (set->capacity == set->size) {
    set->elements = realloc(set->elements, set->capacity*2 * sizeof(T));
    if (set->elements) {
      set->capacity *=2;
    } else return;
  }
  if (contains(set,newElement) == 0) {
    set->elements[set->size] = newElement;
    set->size++;
    qsort(set->elements,set->size,sizeof(T),comp_cresc);
  }
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet* uni = createOrderedSet(s1->size + s2->size);
  for (int i = 0; i < s1->size; i++ ) {
    add(uni, s1->elements[i]);
  }
  for (int i = 0; i < s2->size; i++) {
    add(uni, s2->elements[i]);
  }
  return uni;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet* inter = createOrderedSet(s1->size+s2->size);
  for(int i = 0; i < s1->size; i++){
    if (1 == contains(s2, s1->elements[i])){
      add(inter,s1->elements[i]);
    }
  }
  return inter;
}

// -----------------------------------------------------------------------------

#endif
