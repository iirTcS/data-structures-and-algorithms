
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp) (Item a,Item b))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}



// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	AVLNode *x = y->r;
	if (y == tree->root->l){
		tree->root->l = x;
	}
	x->p = y->p;
	y->p->r = x;
	y->p = x;
	y->r = x->l;
	y->r->p = y;
	x->l = y;
	
	y->height = max(y->l->height, y->r->height) + 1;
	x->height = max(x->l->height, x->r->height) + 1;

	
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	AVLNode *y = x->l;
	if (x == tree->root->l){
		tree->root->l = y;
	}
	y->p = x->p;
	y->p->l = y;
	x->p = y;
	x->l = y->r;
	x->l->p = x;
	y->r = x;
	
	x->height = max(x->l->height, x->r->height) + 1;
	y->height = max(y->l->height, y->r->height) + 1;

}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}



void avlInsert(struct AVLTree* tree, Item elem){
	AVLNode * new_node = avlNewNode(tree);
	new_node->elem = elem;
// Base case	
	if (tree->root->l == tree->nil) {
		tree->root->l = new_node;
		return;	
	}
	
	AVLNode * aux = tree->root->l;
// Insert node in the tree
	while (aux != tree->nil) {
		if (*(aux->elem) == *elem) {
			free(new_node);
			return;
		}
		if (*(aux->elem) > *elem) {
			if (aux->l != tree->nil){
				aux = aux->l;
			} else{
				aux->l = new_node;
				new_node->p = aux;
				break;
			}
		} else { 
			if (aux->r != tree->nil) {
				aux = aux->r;
			} else {
				aux->r = new_node;
				new_node->p = aux;
				break;
			}
		}
	}
// Check balance
	aux = new_node;
	while (aux != tree->nil) {
		int balance = avlGetBalance(aux);
		if (balance <= 1 && balance >= -1) {
			aux->height = max(aux->l->height, aux->r->height) + 1;
			aux = aux->p;
		} else if (balance < 1) {
			avlRightRotate(tree, aux);
			aux = aux->p;
		} else {
			avlLeftRotate(tree, aux);
			aux = aux->p;
		}
	}
}




void avlDeleteNode(AVLTree *tree, AVLNode* node){
	destroyElem(node->elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */