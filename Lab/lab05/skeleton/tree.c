/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Item value) {
	(*root) = malloc(sizeof(TreeNode));
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->value = value;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	if (root == NULL) {
		init(&root, value);
		return root;
	} else if (root->value == value) {
		return root;
	} else if (root->value > value) {
		// Left side of the branch
		if (root->left == NULL) {
			init(&root->left, value);
			return root;
		} else {
			insert(root->left, value);
			return root;
		}
	} else {
		// Right side of the branch
		if (root->right == NULL) {
			init(&root->right, value);
			return root;
		} else {
			insert(root->right, value);
			return root;
		}
	}
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în postordine
*/
void printPostorder(Tree root) {
	// SDR
	if (root != NULL) {
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ", root->value);
	}
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în preordine
*/
void printPreorder(Tree root) {
	// RSD
	if (root != NULL) {
		printf("%d ", root->value);
		printPreorder(root->left);
		printPreorder(root->right);
	}
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în inordine
*/
void printInorder(Tree root) {
	// SRD
	if (root != NULL) {
		printInorder(root->left);
		printf("%d ", root->value);
		printInorder(root->right);
	}
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	if ((*root) == NULL) {
		return;
	}
	freeTree(&(*root)->left);
	freeTree(&(*root)->right);
	free((*root));
	*root = NULL;
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(Tree root) {
	if (root == NULL) {
		return 0;
	} else {
		return 1 + size(root->left) + size(root->right);
	}
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int maxDepth(Tree root) {
	int left_depth = 0, right_depth = 0;
	if (root == NULL) {
		return -1;
	} else {
		left_depth = maxDepth(root->left);
		right_depth = maxDepth(root->right);
		if (left_depth > right_depth) {
			return 1 + left_depth;
		} else {
			return 1 + right_depth;
		}
	}
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(Tree root) {
	if (root == NULL) {
		return;
	}
	mirror(root->left);
	mirror(root->right);

	Tree aux= root->left;
	root->left = root->right;
	root->right = aux;
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(Tree root1, Tree root2) {
	if (root1 == NULL && root2==NULL)
        return 1;
    if (root1 != NULL && root2 != NULL)
    {
        return
        (
            root1->value == root2->value &&
            sameTree(root1->left, root2->left) &&
            sameTree(root2->right, root1->right)
        );
    }
    return 0;
}
