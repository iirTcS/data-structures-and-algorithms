#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	Stack *stiva = malloc(sizeof(*stiva));
	stiva->head = NULL;
	stiva->size = 0;
	return stiva;
}

int isStackEmpty(Stack* stack){
	return stack->head == 0;
}

void push(Stack *stack, Item elem){
	StackNode * new = malloc(sizeof(*new));
	new->elem = elem;
	new->next = stack->head;
	stack->head = new;
	stack->size++;
	return;
}

Item top(Stack *stack){	
	return stack->head->elem;
} 

Item pop(Stack *stack){
	Item to_return;
	if (stack->size > 0) {
		StackNode *remove = stack->head;
		stack->head = stack->head->next;
		stack->size--;
		Item to_return = remove->elem;
		free(remove);
	}
	return to_return;  
}

void destroyStack(Stack *stack){
	while(stack->head != NULL) {
		StackNode *aux = stack->head;
		stack->head = stack->head->next;
		free(aux);
	}
	free(stack);
}

#endif 
