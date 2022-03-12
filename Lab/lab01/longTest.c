#include <stdio.h>
#include <string.h>

typedef long T;
#include "OrderedSet.h"

/*
  Function that returns an ordered set with long elements between
  @start and @end that are multiples of @div
*/

OrderedSet* divide(long star, long end, long div) {
  OrderedSet* set = createOrderedSet(end - star);

  for (int i = star; i <= end; i++)
        if (i % div == 0)
            add(set, i);

  return set;
}

// -----------------------------------------------------------------------------

/*
  Function that prints the size and the elements of an ordered set.
*/

void printOrderedLongSet(OrderedSet* set) {
  long idx;
  printf("There are %ld numbers:", set->size);                 // print the size
  for(idx = 0; idx < set->size; idx++)
    printf(" %ld", set->elements[idx]);                     // print each element
  printf("\n");
}

// -----------------------------------------------------------------------------


int main(int argc, char* argv[]) {
  OrderedSet *s1, *s2, *sU, *sI;

    s1 = divide(4,25,3);
    printOrderedLongSet(s1);

    s2 = divide(5,30,4);
    printOrderedLongSet(s2);

    sU = unionOrderedSets(s1, s2);                    // the union of the two sets
    printf("reunion: ");
    printOrderedLongSet(sU);

    sI = intersectOrderedSets(s1, s2);                         // the intersection
    printf("intersection: ");
    printOrderedLongSet(sI);

  return 0;
}
