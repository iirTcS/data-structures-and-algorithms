/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
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
void init(Tree *root, Tree parent, Item value) {
	(*root) = createTree(parent, value);
}
/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	if (root == NULL) {
		init(&root, NULL, value);
		return root;
	} else if (root->value == value) {
		return root;
	} else if (root->value > value) {
		// Left side
		if (root->left == NULL) {
			init(&root->left, root, value);
			return root;
		} else {
			insert(root->left, value);
			return root;
		}
	} else {
		// Right side
		if (root->right == NULL) {
			init(&root->right, root, value);
			return root;
		} else {
			insert(root->right, value);
			return root;
		}
	}
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	return (root == NULL);
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	if (tree == NULL) {
		return 0;
	} else if (tree->value == value){
		return 1;
	} else if (tree->value > value) {
		if (tree->left == NULL) {
			return 0;
		} else {
			contains(tree->left, value);
		}
	} else {
		if (tree->right == NULL) {
			return 0;
		} else {
			contains(tree->right, value);
		}
	}
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	if (tree == NULL) {
		return NULL;
	} else if (tree->left == NULL) {
		return tree;
	} else {
		minimum(tree->left);
	}
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	if (tree == NULL) {
		return NULL;
	} else if (tree->right == NULL) {
		return tree;
	} else {
		maximum(tree->right);
	}
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree find_node(Tree root, Item value) {
	if (root != NULL) {
		if (root->value == value) {
			return root;
		} else if (root->value > value) {
			return find_node(root->left, value);
		} else {
			return find_node(root->right, value);
		}
	}
}

Tree successor(Tree root, Item value) {
	if (root != NULL) {
		if (value == maximum(root)->value) {
			return NULL;
		}
		Tree aux = find_node(root, value);
		if (aux->right == NULL) {
			if (aux->parent->value > value) {
				return aux->parent;
			} else { 
				while (aux->parent->value < value) {
					aux = aux->parent;
				}
				return aux->parent;
			}
		} else {
			return minimum(aux->right);
		}
	}
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	if (root != NULL) {
		if (value == minimum(root)->value) {
			return NULL;
		}
		Tree aux = find_node(root, value);
		if (aux->left == NULL) {
			if (aux->parent->value < value) {
				return aux->parent;
			} else { 
				while (aux->parent->value > value) {
					aux = aux->parent;
				}
				return aux->parent;
			}
		} else {
			return maximum(aux->left);
		}
	}
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	if ((*root) == NULL) {
		return;
	}
	destroyTree(&(*root)->left);
	destroyTree(&(*root)->right);
	free((*root));
	*root = NULL;
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	if (root == NULL) {
		return NULL;
	} else if (root->value > value) {
		root->left = delete(root->left, value);
	} else if (root->value < value) {
		root->right = delete(root->right, value);
	} else {
		if (root->left != NULL && root->right != NULL) {
			Tree aux = minimum(root->right);
			root->value = aux->value;
			root->right = delete(root->right, aux->value);
		} else {
			Tree aux = root;
			if (root != NULL) {
				root = root->left;
			} else {
				root = root->right;
			}
			free(aux);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	if (root == NULL) {
		return NULL;
	} else if (root->value > value1 && root->value > value2) {
		return lowestCommonAncestor(root->left, value1, value2);
	} else if (root->value < value1 && root->value < value2) {
		return lowestCommonAncestor(root->right, value1, value2);
	} else {
		return root;
	}
}
