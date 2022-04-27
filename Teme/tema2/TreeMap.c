#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeMap.h"

#define MAX(a, b) (((a) >= (b))?(a):(b))


/* Creeaza un arbore cu o serie de metode asociate
 *
 * return: arborele creat
 */
TTree* createTree(void* (*createElement)(void*),
				  void (*destroyElement)(void*),
				  void* (*createInfo)(void*),
				  void (*destroyInfo)(void*),
				  int compare(void*, void*)) {
	TTree* tree = malloc(sizeof(* tree));
	tree->compare = compare;
	tree->createElement = createElement;
	tree->createInfo = createInfo;
	tree->destroyElement = destroyElement;
	tree->destroyInfo = destroyInfo;
	tree->root = NULL;
	tree->size = 0;
	return tree;
}


/* Verifica daca un arbore este gol (vid)
 * 		1 - daca arborele este gol
 * 		0 - in caz contrar
 */
int isEmpty(TTree* tree) {
	return tree->root == NULL || tree == NULL;
}


/* Cauta un anumit element in interiorul unui arbore
 *
 * tree: structura cu metodele asociate arborelui
 *   !folosit pentru a putea compara elementul curent cu cel cautat
 *
 * x: radacina arborelui curent (in care se face cautarea)
 * elem: elementul ce trebuie cautat
 */
TreeNode* search(TTree* tree, TreeNode* x, void* elem) {
	if (tree == NULL || x == NULL || tree->root == NULL) return NULL;
	
	TreeNode* aux = x;

	while (aux != NULL && tree->compare(aux->elem, elem) != 0) {

		if (tree->compare(aux->elem, elem) == -1) {
			aux = aux->right;
		} else {
			aux = aux->left;
		}
	}
	return aux;
}


/* Gaseste nodul cu elementul minim dintr-un arbore
 * avand radacina in x
 */
TreeNode* minimum(TreeNode* x) {
	if (x == NULL) return NULL;

	TreeNode *aux = x;
	while (aux->left != NULL) {
		aux = aux->left;
	}
	return aux;
}

/* Gaseste nodul cu elementul maxim dintr-un arbore
 * avand radacina in x
 */
TreeNode* maximum(TreeNode* x) {
	if (x == NULL) return NULL;

	TreeNode *aux = x;
	while (aux->right != NULL) {
		aux = aux->right;
	}
	return aux;
}


/* Functie pentru gasirea succesorului unui nod
 * (succesorul in inordine)
 */
TreeNode* successor(TreeNode* x) {
	TreeNode * aux = x;
	
	if (aux == NULL) return NULL;

	if (aux->right == NULL) {
		if (aux->parent != NULL) {
			if (aux->parent->left == aux) {
				return aux->parent;
			} else {
				while (aux->parent != NULL && aux->parent->right == aux) {
					aux = aux->parent;
				}
				return aux->parent;
			}
		} else {
			return NULL;
		}
	} else {
		return minimum(aux->right);
	}
	return NULL;
}


/* Functie pentru gasirea predecesorului unui nod
 * (predecesorul in inordine)
 */
TreeNode* predecessor(TreeNode* x) {
	TreeNode * aux = x;
	
	if (aux == NULL) return NULL;

	if (aux->left == NULL) {
		if (aux->parent != NULL) {
			if (aux->parent->right == aux) {
				return aux->parent;
			} else {
				while (aux->parent != NULL && aux->parent->left == aux) {
					aux = aux->parent;
				}
				return aux->parent;
			}
		} else {
			return NULL;
		}
	} else {
		return maximum(aux->left);
	}
	return NULL;
}


/* Actualizeaza inaltimea unui nod din arbore
 */
void updateHeight(TreeNode* x) {

	int leftHeight = 0;
	int rightHeight = 0;

	if (x != NULL) {
		if (x->left != NULL)  leftHeight  = x->left->height;
		if (x->right != NULL) rightHeight = x->right->height;
		x->height = MAX(leftHeight, rightHeight) + 1;
	}
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la stanga
 * a subarborelui care are varful in x
 *
 *   (x)	 Rotatie    (y)
 *	 / \     stanga     / \
 *  a  (y)    ---->   (x)  c
 *	   / \			  / \
 *    b   c          a   b
 */
void avlRotateLeft(TTree* tree, TreeNode* x) {
	if (tree == NULL || x == NULL) return;
	TreeNode *y = x->right;
	if (x == tree->root){
		tree->root = y;
	}
	y->parent = x->parent;
	if (y->parent != NULL) {
		if (y->parent->left == x) {
			y->parent->left = y;
		} else if (y->parent->right == x){
			y->parent->right = y;
		}
	}
	x->parent = y;
	x->right = y->left;
	x->right->parent = x;
	y->left = x;
	
	x->height = MAX(x->left == NULL? 0 : x->left->height, x->right == NULL? 0 : x->right->height) + 1;
	y->height = MAX(y->left == NULL? 0 : y->left->height, y->right == NULL? 0 : y->right->height) + 1;
	return;
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la dreapta
 * a subarborelui care are varful in y
 *
 *     (y)	 Rotatie    (x)
 *	   / \   dreapta    / \
 *   (x)  c   ---->    a  (y)
 *	 / \			      / \
 *  a   b                b   c
 */
void avlRotateRight(TTree* tree, TreeNode* y) {
	if (tree == NULL || y == NULL) return;
	TreeNode *x = y->left;
	if (y == tree->root){
		tree->root = x;
	}
	x->parent = y->parent;
	if (x->parent != NULL) {
		if (x->parent->right == y) {
			x->parent->right = x;
		} else if (x->parent->left == y){
			x->parent->left = x;
		}
	}
	y->parent = x;
	y->left = x->right;
	y->left->parent = y;
	x->right = y;
	
	y->height = MAX(y->left == NULL? 0 : y->left->height, y->right == NULL? 0 : y->right->height) + 1;
	x->height = MAX(x->left == NULL? 0 : x->left->height, x->right == NULL? 0 : x->right->height) + 1;
	return;
}


/* Calculeaza factorul de echilibrare pentru un nod x
 * (AVL balance factor)
*/
int avlGetBalance(TreeNode *x) {
	if (x == NULL) {
		return 0;
	}
	return (x->left == NULL? 0 : x->left->height) - (x->right == NULL? 0 : x->right->height);
}


/* Functie pentru reechilibrarea unui arbore AVL
 * in urma unei inserari prin rotatii simple sau duble
 * si recalcularea inaltimii fiecarui nod intalnit parcurgand
 * arborele de jos in sus, spre radacina
 *
 */
void avlFixUp(TTree* tree, TreeNode* y) {
	TreeNode *aux = y;
	while (aux != NULL) {
		int balance = avlGetBalance(aux);
		if (balance <= 1 && balance >= -1) {
			aux->height = MAX(aux->left == NULL? 0 : aux->left->height,
							 aux->right == NULL? 0 : aux->right->height) + 1;
			aux = aux->parent;
		} else if (balance < 1) {
			avlRotateRight(tree, aux);
			aux = aux->parent;
		} else {
			avlRotateLeft(tree, aux);
			aux = aux->parent;
		}
	}
	return;
}


/* Functie pentru crearea unui nod
 *
 * value: valoarea/cheia din cadrul arborelui
 * info: informatia/valoarea din dictionar
 */
TreeNode* createTreeNode(TTree *tree, void* value, void* info) {

	if (tree == NULL)
		return NULL;

	// Alocarea memoriei
	TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

	// Setarea elementului si a informatiei
	node->elem = tree->createElement(value);
	node->info = tree->createInfo(info);

	// Initializarea legaturilor din cadrul arborelui
	node->parent = node->right = node->left = NULL;

	// Initializarea legaturilor din cadrul listei dublu inlantuite
	node->next = node->prev = node->end = NULL;


	// Inaltimea unui nod nou este 1
	// Inaltimea lui NULL este 0
	node->height = 1;

	return node;
}


/* Inserarea unul nou nod in cadrul multi-dictionarului
 * ! In urma adaugarii arborele trebuie sa fie echilibrat
 *
 */
void insert(TTree* tree, void* elem, void* info) {
	TreeNode * new = createTreeNode(tree, elem, info);
}


/* Eliminarea unui nod dintr-un arbore
 *
 * ! tree trebuie folosit pentru eliberarea
 *   campurilor `elem` si `info`
 * */
void destroyTreeNode(TTree *tree, TreeNode* node){

	// Verificarea argumentelor functiei
	if(tree == NULL || node == NULL) return;

	// Folosirea metodelor arborelui
	// pentru de-alocarea campurilor nodului
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);

	// Eliberarea memoriei nodului
	free(node);
}


/* Eliminarea unui nod din arbore
 *
 * elem: cheia nodului ce trebuie sters
 * 	! In cazul in care exista chei duplicate
 *	  se va sterge ultimul nod din lista de duplicate
 */
void delete(TTree* tree, void* elem) {

}


/* Eliberarea memoriei unui arbore
 */
void destroyTree(TTree* tree){

	/* Se poate folosi lista dublu intalntuita
	 * pentru eliberarea memoriei
	 */
	if (tree == NULL || tree->root == NULL)
		return;
}