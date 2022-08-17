#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	ListNode *node = malloc(sizeof(ListNode));
	node->elem = elem;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	List *new = malloc(sizeof(List));
	new->first = NULL;
	new->last = NULL;
	return new;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	if (list == NULL) return 1;
	if (list->first == NULL && list->last==NULL)  return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	
	if (isEmpty(list)) return 0;
	if (list->first->elem == elem ) return 1;
	for (ListNode *next = list->first; next != list->last; next = next->next) {
		if (next->elem == elem) return 1;
	}
	if (list->last->elem == elem) return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){
	// Guard against young player errors
	if(list == NULL) return;

	// Verification
	if (pos < 0) return;
	if (isEmpty(list) && pos > 0) return;
	

	// if the list is empty and instertAt pos 0
	if (isEmpty(list)) {
		ListNode *new_node = createNode(elem);
		list->first = new_node;
		list->last = new_node;
		return;
	}
	// First position
	if (pos == 0) {
		ListNode *new_node = createNode(elem);
		new_node->next = list->first;
		list->first->prev=new_node;
		list->first = new_node;
		return;
	}
	// Last position
	int length=0;
	for(ListNode *i = list->first; i != NULL; i= i->next) {
		length++;
	}
	if (length == pos) {
		ListNode *new_node = createNode(elem);
		list->last->next = new_node;
		new_node->prev = list->last;
		list->last=new_node;
		return;
	}
	// Middle
	ListNode *where_i_am = list->first;
	for(int i = 0; i < length; i++) {
		if (i+1 == pos) {
			ListNode *new_node = createNode(elem);
			new_node->prev = where_i_am;
			new_node->next = where_i_am->next;
			where_i_am->next->prev=new_node;
			where_i_am->next=new_node;
			return;
		}
		where_i_am = where_i_am->next;
	}	
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;
	if (contains(list,elem)) {
		if (list->first == list->last){
			free(list->first);
			list->first = NULL;
			list->last = NULL;
			return;
		}
		// first element
		if (list->first->elem == elem) {
			
			// more elememts
				ListNode *aux = list->first->next;
				free(list->first);
				list->first = aux;
				list->first->prev = NULL;
				return;
		}
		// middle and last element 
		for(ListNode *i = list->first; i->next != NULL; i= i->next) {
			if (i->next->elem == elem) {
				if (i->next->next == NULL) {
					free(i->next);
					list->last = i;
					list->last->next = NULL;
					return;
				} else {
					ListNode *aux = i->next->next;
					aux->prev = i;
					free(i->next);
					i->next=aux;
					return;
				}
			}
		}
	}

	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;

	// TODO: Cerinta 1f
	if (isEmpty(list)) {
		return 0;
	}else {
		int length = 0;
		for(ListNode *i = list->first; i != NULL; i= i->next) {
			length++;
		}
		return length;
	}
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;

	//TODO: Cerinta 1g
	ListNode *aux = NULL;
	while (list->first != NULL)
	{
		aux = list->first;
		list->first = list->first->next;
		free(aux);
	}
	free(list);
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
