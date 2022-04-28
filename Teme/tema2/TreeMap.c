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
		tree->root = x->right;
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
	if (x->right) {
		x->right->parent = x;
	}
	y->left = x;
	
	updateHeight(x);
	updateHeight(y);
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
	if (y->left)
		y->left->parent = y;
	x->right = y;
	
	updateHeight(y);
	updateHeight(x);
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
			updateHeight(aux);
			aux = aux->parent;
		} else if (balance < -1) {
			if (avlGetBalance(aux->right) < 0) {
				avlRotateLeft(tree, aux);
			} else {
				avlRotateRight(tree, aux->right);
				avlRotateLeft(tree, aux);
			}
			aux = aux->parent;
		} else {
			if (avlGetBalance(aux->left) > 0) {
				avlRotateRight(tree, aux);
			} else {
				avlRotateLeft(tree, aux->left);
				avlRotateRight(tree, aux);
			}
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
	if (tree == NULL) {
		return;
	}
	TreeNode * new = createTreeNode(tree, elem, info);
	new->end = new;
	if (tree->root == NULL) {
		tree->root = new;
		return;
	}
	TreeNode* aux = search(tree, tree->root, elem);
	if (aux) {
		// Last position
		if (aux->end->next != NULL) {
			new->next = aux->end->next;
			new->next->prev = new;
		}
		aux->end->next = new;
		new->prev = aux->end;
		aux->end = new;
	} else {
		// Avl insert
		aux = tree->root;
		while (aux != NULL) {
			if (tree->compare(aux->elem, elem) == 1) {
				
				if (aux->left != NULL){
					aux = aux->left;
				} else{
					aux->left = new;
					new->parent = aux;
					break;
				}
			} else if (tree->compare(aux->elem, elem) == -1){ 				
				if (aux->right != NULL) {
					aux = aux->right;
				} else {
					aux->right = new;
					new->parent = aux;
					break;
				}
			}
		}
		avlFixUp(tree, new);
		
	// List insert
		aux = tree->root;
		if (tree->compare(aux->elem, elem) == -1) {
			// Left side
			while (aux->next != NULL && tree->compare(aux->next->elem, elem) == -1) {
				aux =  aux->next;
			}

			if (aux->next != NULL) {
				new->next = aux->next;
				aux->next->prev = new;
			}
			aux->next = new;
			new->prev = aux;
		} else if (tree->compare(aux->elem, elem) == 1){ 
			// Right side
			while (aux->prev != NULL && tree->compare(aux->prev->elem, elem) == 1) {
				aux =  aux->prev;
			}

			if (aux->prev != NULL) {
				new->prev = aux->prev;
				aux->prev->next = new;
			}
			aux->prev = new;
			new->next = aux;
		}

	}
	tree->size++;
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
TreeNode* delete_avl(TTree* tree, TreeNode* root, void* elem) {
	if (root == NULL) {
		return root;
	} else if (tree->compare(root->elem, elem) == 1) {				
		root->left = delete_avl(tree, root->left, elem);

	} else if (tree->compare(root->elem, elem) == -1) {

		root->right = delete_avl(tree, root->right, elem);
	
	} else {
		if (root->left != NULL && root->right != NULL) {
			TreeNode *aux = root->next;
			
			tree->destroyElement(root->elem);
			tree->destroyInfo(root->info);
			root->elem = tree->createElement(aux->elem);
			root->info = tree->createInfo(aux->info);

			root->right = delete_avl(tree, root->right, aux->elem);
		} else {
			TreeNode *aux = root;
			if (root->next)
				root->next->prev = root->prev;
			if (root->prev)
				root->prev->next = root->next;


			if (root->left != NULL) {
				root->left->parent = root->parent;
				root->parent->left = root->left;
			} else if (root->right != NULL){
				root->right->parent = root->parent;
				root = root->right;
			} else {
				root = NULL;
			}
			TreeNode* fix = aux->parent;
			destroyTreeNode(tree, aux);
			avlFixUp(tree, fix);
		}
	}

	updateHeight(root);
	return root;
}

void delete(TTree* tree, void* elem) {
	TreeNode * to_delete = search(tree, tree->root, elem);
	if (to_delete) {
		if (to_delete->end == to_delete) {
			TreeNode* par = to_delete->parent;
			if (par)
				delete_avl(tree, par, elem);
			else 
				delete_avl(tree, to_delete, elem);

			avlFixUp(tree, minimum(tree->root));

			avlFixUp(tree, maximum(tree->root));

		} else {
			if (to_delete->end->next) {
				to_delete->end->next->prev = to_delete->end->prev;
			}
			to_delete->end->prev->next = to_delete->end->next;
			TreeNode* aux = to_delete->end->prev;
			destroyTreeNode(tree, to_delete->end);
			to_delete->end = aux;
		}
		tree->size--;
	}
}


/* Eliberarea memoriei unui arbore
 */
void destroyTree(TTree* tree){
	if (tree == NULL || tree->root == NULL)
		return;
	
}