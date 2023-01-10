# Vigenère Chiper with AVL and Double linked lists :
Author : Rotari Corneliu.
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
- compare
- createInfo
- createElem
- destoryInfo
- destoryElem
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
Check the balance of the node, (heigt_left - height_right).
12. **avlFixUp :**\
Balances the tree to keep the property of an AVL:
- If the node doesn't need fix just update.
- Performes the specific rotations (Left, Right, Left-Right, Right-Left).
13. **createTreeNode :**\
Creates an node using the tree methodes and sets the height to 1.
14. **insert :**\
Adds a node in to the data-structures so that every propriety is respected.
-  Creates a node.
-  Checks if a node with the same key exsits :
    - If exists, the node is innserted in the double linked list.
    - If the search is NULL , the node is first added to the AVL tree and after that in the double linked list.
15. **destroyTreeNode :**\
Frees the memory of a node using the tree methodes.
16. **delete :**\
- Search if the node exists :
- Deletes from the avl and the lists (case the node is the root or not) and calls [ delete_avl ] or only from the list.
17. **delete_avl :**\
Recursive function that deletes a node from the avl and the linked list. Cases:
- If the node has to children.
- If the node has only one child.
- If the node is the child.
18. **destoryTree :**\
Frees the memory of a tree variable and the data - structures.

## Cipher :
1.  **buildTreeFromFile :**\
Reads the infromation from a file and adds the word into a the tree.
2. **inorderKeyQuery :**\
Creats a key from every node's information.
3. **levelKeyQuery :**\
Creats a key from all the node's information that are on the same level as the node with the highest frequences.
4. **rangeKeyQuery :**\
Creats a key from every node's information that resides in a specific range.


