# Vigenère Chiper with AVL and Double linked lists :
```
            =(q)=(r)=(r)=
             / \
            /   \
           /     \
          /       \
         /         \
        /           \
       /             \
    =(b)=           =(s)=(s)= 
     / \             / \
    /   \           /   \
   /     \         /     \
  /       \       /       \
(a)=     =(m)=  =(r)=    =(w)=(w)
```
##   Multi-dicitonary based on AVL and Double-Linked-list :
1.  **createTree :**\
Creats a tree dynamic varible with the *root* pointing to NULL, the *size* to 0 and inserts its methodes :
    
2.  **isEmpty :**\
Checks if the tree root or the tree is equal NULL.
3.  **search :**\
Search if in the specific *x* rooted tree there is a node containing a specific key.
4.  **minimum :**\
Using the AVL abstract data strucure propriety travels to the most left node.
5.  **maximum :**\
Using the AVL abstract data strucure propriety travels to the most right node.
6.  **succesor :**\
Function that finds the succesor of a node from the inorder arrange. It returns NULL if the node is the maximum. Cases :
  - The successor is up the tree (and if the aux is the left node and its the right node).
  - The successor is in the right sub-tree of the node.
7.  **predecessor :**\
Function that finds the predeccesor of a node from the inorder arrange. It returns NULL if the node is the minimum. Cases :
  - The predecessor is up the tree (and if the aux is the left node and its the right node).
  - The predecessor is in the left sub-tree of the node.
8.  **updateHeight :**\
Updates the height the x node, by finding the heigh the maximum between the left child's and the right child's height + 1.
9.  **avlRotateLeft :**\
If a tree becomes unbalanced, when a node is inserted into the right subtree of the right subtree, then we perform a left rotation.
10. **avlRotateRight :**\
AVL tree may become unbalanced, if a node is inserted in the left subtree of the left subtree. The tree then needs a right rotation.
11. **avlGetBalance :**\
Check the balance of the node, (heigt_left - height_right);
12. **avlFixUp :**\

