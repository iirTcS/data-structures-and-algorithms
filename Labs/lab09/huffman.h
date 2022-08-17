#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct HuffmanNode {
    unsigned char value;
    struct HuffmanNode *left,
                        *right,
                        *parent;
} HuffmanNode, *PHuffmanNode;

typedef PHuffmanNode T;

#include "heap.h"


PHuffmanNode initNode(unsigned char value) {
    PHuffmanNode new = malloc(sizeof(*new));
    new->left = new->right = new->parent = NULL;
    new->value = value;
    return new;
}

void computeFreqs(char *text, int freqs[256]) {
    for (int i = 0; i < strlen(text); i++) {
        if (freqs[(int) text[i]] == 0) {
            freqs[(int) text[i]] = 1;
        } else {
            freqs[(int) text[i]]++;
        }
    }
    return;
}

PHuffmanNode makeTree(int freqs[256]) {
    PHeap h = makeHeap(256);
    for (int i = 0; i < 256; i++) {
        if (freqs[i] != 0) {
            insert(h, initNode(i), freqs[i]);
        }
    }
    PHuffmanNode parent = NULL;
    while (h->size >= 2) {
        PHeapNode child_1 = removeMin(h);
        PHeapNode child_2 = removeMin(h);
        parent = initNode('\0');
        
        child_1->elem->parent = parent;
        child_2->elem->parent = parent;
        parent->left = child_1->elem;
        parent->right = child_2->elem;
        
        insert(h, parent, child_1->prior + child_2->prior);
    }
    
    PHeapNode child_1 = removeMin(h);
    parent = child_1->elem;
    
    freeHeap(h);
    return parent;
}

void makeCodes(PHuffmanNode root, char **allCodes) {
    if (root->value == '\0') {
        makeCodes(root->left, allCodes);
        makeCodes(root->right, allCodes);
        return;
    }
    PHuffmanNode aux = root;
    char *s = malloc(256);
    int len = 0;
    while (aux->parent != NULL) {
        if (aux->parent->left == aux) {
            s[len] = '0';
        } else {
            s[len] = '1';
        }
        len++;
        s[len] = '\0';
        aux = aux->parent;
    }
    allCodes[root->value] = malloc(len + 1);
    strncpy(allCodes[root->value], s, len + 1);
    for (int i = 0; i < strlen(allCodes[root->value]) / 2; i++) {
        char aux = allCodes[root->value][i];
        allCodes[root->value][i] = allCodes[root->value][strlen(allCodes[root->value]) - i-1];
        allCodes[root->value][strlen(allCodes[root->value]) - i -1] = aux;
    }   
    return;
}


char *compress(char *textToEncode, char **allCodes) {
    char *encode = malloc(10000);
    for (int i = 0; i < strlen(textToEncode); i++) {
        strcat(encode, allCodes[(int) textToEncode[i]]);
    }
    return encode;
}

char *decompress(char *textToDecode, PHuffmanNode root) {
    PHuffmanNode aux = root;
    char *s = malloc(10000);
    int len = 0;

    for (int i = 0; i < strlen(textToDecode); i++) {
        if (textToDecode[i] == '0') {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
        if (aux->value != '\0') {
            s[len] = aux->value;
            len++;
            aux = root;
        }
    }
    s[len] = '\0';
    return s;
}

#endif
