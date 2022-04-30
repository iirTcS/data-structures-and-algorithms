#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#include "Cipher.h"



/* Construieste un multi-dictionar pe baza unui fisier text
 * Cheia (elem) unui nod va fi reprezentata de un cuvant din text
 * iar valoarea (info) va fi indexul de inceput al acelui cuvant
 * ignorand caracterele separatoare (",.? \n\r") - i.e. numarul
 * de caractere A-Z precedente
 *
 * E.g: THIS IS AN EXAMPLE
 *
 * 			IS (4)
 *		    / \
 * 	  (6) AN  THIS (0)
 *         \
 *	 	 EXAMPLE (8)
 * */
void buildTreeFromFile(char* fileName, TTree* tree) {

	// Verificarea argumentelor
	if(fileName == NULL || tree == NULL)
		return;
	
	FILE *f = fopen(fileName, "r");
	char *s = malloc(256);
	int j = 0, all = 0;
	while(fgets(s, 256, f)) {
		char* word = malloc(256);
		
		for (int i = 0; i < strlen(s) + 1; i++) {
			// Separets the letters from other characters
			// If there is another character the word is sent into the tree.
			if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) {
				word[j] = s[i];
				j++;
			} else if (j != 0) {
				word[j] = '\0';
				char *to_send = calloc(sizeof(char), 6);
				strncpy(to_send, word, 5);
				insert(tree, to_send, &all);
				all += j;
				j = 0;
				free(to_send);
			}

		}
		free(word);
	}
	free(s);
	fclose(f);
}


/* Functie pentru afisarea unei chei de criptare
 * O cheie este reprezentata print-o serie de offset-uri
 *
 * E.g: key = [1, 2, 3, 4]
 * input text  = A    A    A    A
 *			   +1|  +2|  +3|  +4|
 * 				 V    V    V    V
 * output text = B    C    D    E
 *
 */
void printKey(char *fileName, Range *key) {

	FILE *f = fopen(fileName, "w");

	if (key == NULL) {
		fprintf(f, "No key provided!\n");
		fclose(f);
		return;
	}

	fprintf(f, "Decryption key of length %d is:\n", key->size);

	// Afiseaza fiecare offset din cheie % 26 (lungimea
	// alfabetului A-Z)
	for (int i = 0; i < key->size; i++) {
		fprintf(f, "%d ", key->index[i] % 26);

		// Rand nou pentru lizibilitate
		if ((i + 1) % 10 == 0)
			fprintf(f, "\n");
	}

	fclose(f);
}


/* Returneaza cheia obtinuta de parcurgerea in ordine
 * crescatoare a nodurilor arborelui (parcurgand si listele
 * de duplicate)
 */
Range* inorderKeyQuery(TTree* tree) {
	TreeNode * aux = minimum(tree->root);
	Range *key = malloc(sizeof(*key));
	key->capacity = 1;
	key->index = malloc(key->capacity * sizeof(int));
	key->size = 0;
// Travels throughout all the nodes
	while (aux != NULL) {

		if (key->size == key->capacity) {
			key->index = realloc(key->index, key->capacity * 2 *sizeof(int));
			key->capacity *= 2;
		}

		int i = *((int*)aux->info) % 26;
		aux = aux->next;
		key->index[key->size] = i;
		key->size++;

	}

	return key;
}


/* Functie pentru extragerea cheii formate din valorile
 * nodurilor de la nivelul ce contine cel mai frecvent cuvant
 * (in cazul in care exista mai multe cuvinte cu numar maxim
 * de aparitii atunci se va considera primul nod dintre acestea conform
 * parcurgerii in inordine a arborelui)
 */
Range* levelKeyQuery(TTree* tree) {
	Range *key = malloc(sizeof(*key));
	key->capacity = 1;
	key->index = malloc(key->capacity * sizeof(int));
	key->size = 0;

	TreeNode * aux = minimum(tree->root);
	TreeNode * node_freq = NULL;
	int max = 0;
	// Finds the node with the highest frequence node and its level
	while (aux != NULL) {
		int freq = 1;
		TreeNode *tmp = aux;
		while (tmp != aux->end) {
			freq++;
			tmp = tmp->next;
		}

		if (freq > max) {
			max = freq;
			node_freq = aux;
		}
		aux = aux->end->next;
	}

	aux = node_freq;
	int node_level = 0;
	while (aux != NULL) {
		aux = aux->parent;
		node_level++;
	}

	aux = minimum(tree->root);
	// Checks every node's level and adds to the key
	while (aux != NULL) {
		int level = 0;
		TreeNode* tmp = aux;
		while (tmp != NULL) {
			tmp = tmp->parent;
			level++;
		}
		// Node's level
		if (level == node_level) {
			tmp = aux;
			if (tmp == aux->end) {
				if (key->size == key->capacity) {
					key->index = realloc(key->index, key->capacity * 2 *sizeof(int));
					key->capacity *= 2;
				}

				key->index[key->size] = *((int*)aux->info);
				key->size++;
			} else {
				while (tmp != aux->end->next) {
					if (key->size == key->capacity) {
						key->index = realloc(key->index, key->capacity * 2 *sizeof(int));
						key->capacity *= 2;
					}

					key->index[key->size] = *((int*)tmp->info);
					key->size++;
					tmp = tmp->next;
				}
			}
		}
		aux = aux->end->next;
	}
	
	return key;
}


/* Extragerea cheii din nodurile aflate intr-un anumit
 * domeniu de valori specificat
 */
Range* rangeKeyQuery(TTree* tree, char* q, char* p) {
	Range *key = malloc(sizeof(*key));
	key->capacity = 1;
	key->index = malloc(key->capacity * sizeof(int));
	key->size = 0;

	TreeNode *aux = minimum(tree->root);
	while (aux != NULL) {
		if (key->size == key->capacity) {
			key->index = realloc(key->index, key->capacity * 2 *sizeof(int));
			key->capacity *= 2;
		
		}
		// If the node is in a speciffic range
		if (tree->compare(aux->elem, q) >= 0 && tree->compare(aux->elem, p) <= 0) {
			key->index[key->size] = *((int*)aux->info);
			key->size++;
		}
		aux = aux->next;
	}

	return key;
}


void encrypt(char *inputFile, char *outputFile, Range *key) {

	FILE * f_in  = fopen(inputFile,  "r");
	FILE * f_out = fopen(outputFile, "w");

	if (f_in == NULL)
		return;

	char *buff = (char*) malloc(BUFLEN+1);
	char c;

	int idx = 0;

	while (fgets(buff, BUFLEN, f_in) != NULL) {

		for (int i = 0; i < strlen(buff); i++) {
			if (buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\r') {
				c = ((toupper(buff[i]) - 'A') + key->index[idx] % 26) % 26 + 'A';
				idx += 1;
			} else
			 	c = buff[i];

			fprintf(f_out, "%c", c);

			if (idx == key->size)
				idx = 0;
		}
	}

	free(buff);
	fclose(f_in);
	fclose(f_out);
}


void decrypt(char *inputFile, char *outputFile, Range *key) {
 	
	FILE * f_in  = fopen(inputFile,  "r");
	FILE * f_out = fopen(outputFile, "w");

	if (f_in == NULL)
		return;

	char *buff = (char*) malloc(BUFLEN+1);
	char c;

	int idx = 0;

	while (fgets(buff, BUFLEN, f_in) != NULL) {

		for (int i = 0; i < strlen(buff); i++) {
			if (buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\r') {
				c = ((toupper(buff[i]) - 'A') - (key->index[idx] % 26) + 26) % 26 + 'A';
				idx += 1;
			} else
			 	c = buff[i];

			fprintf(f_out, "%c", c);

			if (idx == key->size)
				idx = 0;
		}
	}

	free(buff);
	fclose(f_in);
	fclose(f_out);
}