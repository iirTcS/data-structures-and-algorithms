package rbt;

import java.io.Writer;

public class RBTree {

    private final int R = 0;
    private final int B = 1;
    private int size = 0;

    public int getSize() {
        return size;
    }

    private class Node {
        int key = -1, color = B;
        Node left = nil, right = nil, p = nil;

        Node(int key) {
            this.key = key;
        }

        @Override
        public String toString() {
            return this.key != -1 ? (((this.color == R) ? "R" : "B") + " : " + this.key + "\n") : "nill";
        }
    }

    private final Node nil = new Node(-1);
    private Node root = nil;

    public int getRoot() {
        return root.key;
    }

    public void insert(int number) {
        this.size++;
        this.insert(new Node(number));
    }
    private void insert(Node node) {
        Node temp = root;
        if (root == nil) {
            root = node;
            node.color = B;
            node.p = nil;
        } else {
            node.color = R;
            while (true) {
                if (node.key < temp.key) {
                    if (temp.left == nil) {
                        temp.left = node;
                        node.p = temp;
                        break;
                    } else {
                        temp = temp.left;
                    }
                } else {
                    if (temp.right == nil) {
                        temp.right = node;
                        node.p = temp;
                        break;
                    } else {
                        temp = temp.right;
                    }
                }
            }
            fixTree(node);
        }
    }

    private void fixTree(Node node) {
        while (node.p.color == R) {
            Node y = nil;
            if (node.p == node.p.p.left) {
                y = node.p.p.right;

                if (y != nil && y.color == R) {
                    node.p.color = B;
                    y.color = B;
                    node.p.p.color = R;
                    node = node.p.p;
                    continue;
                }
                if (node == node.p.right) {
                    node = node.p;
                    rotateLeft(node);
                }
                node.p.color = B;
                node.p.p.color = R;
                rotateRight(node.p.p);
            } else {
                y = node.p.p.left;
                if (y != nil && y.color == R) {
                    node.p.color = B;
                    y.color = B;
                    node.p.p.color = R;
                    node = node.p.p;
                    continue;
                }
                if (node == node.p.left) {
                    node = node.p;
                    rotateRight(node);
                }
                node.p.color = B;
                node.p.p.color = R;
                rotateLeft(node.p.p);
            }
        }
        root.color = B;
    }

    void rotateLeft(Node node) {
        if (node.p != nil) {
            if (node == node.p.left) {
                node.p.left = node.right;
            } else {
                node.p.right = node.right;
            }
            node.right.p = node.p;
            node.p = node.right;
            if (node.right.left != nil) {
                node.right.left.p = node;
            }
            node.right = node.right.left;
            node.p.left = node;
        } else {
            Node right = root.right;
            root.right = right.left;
            right.left.p = root;
            root.p = right;
            right.left = root;
            right.p = nil;
            root = right;
        }
    }

    void rotateRight(Node node) {
        if (node.p != nil) {
            if (node == node.p.left) {
                node.p.left = node.left;
            } else {
                node.p.right = node.left;
            }

            node.left.p = node.p;
            node.p = node.left;
            if (node.left.right != nil) {
                node.left.right.p = node;
            }
            node.left = node.left.right;
            node.p.right = node;
        } else {
            Node left = root.left;
            root.left = root.left.right;
            left.right.p = root;
            root.p = left;
            left.right = root;
            left.p = nil;
            root = left;
        }
    }

    void transplant(Node target, Node with) {
        if (target.p == nil) {
            root = with;
        } else if (target == target.p.left) {
            target.p.left = with;
        } else {
            target.p.right = with;
        }
        with.p = target.p;
    }

    Node treeMinimum(Node subTreeRoot) {
        while (subTreeRoot.left != nil) {
            subTreeRoot = subTreeRoot.left;
        }
        return subTreeRoot;
    }

    public boolean delete(int key) {
        Node z = containsNode(key);
        if (z == nil) {
            return false;
        }

        Node x;
        Node y = z;
        int yOriginalColor = y.color;

        if (z.left == nil) {
            x = z.right;
            transplant(z, z.right);
        } else if (z.right == nil) {
            x = z.left;
            transplant(z, z.left);
        } else {
            y = treeMinimum(z.right);
            yOriginalColor = y.color;
            x = y.right;
            if (y.p == z) {
                x.p = y;
            } else {
                transplant(y, y.right);
                y.right = z.right;
                y.right.p = y;
            }
            transplant(z, y);
            y.left = z.left;
            y.left.p = y;
            y.color = z.color;
        }
        if (yOriginalColor == B) {
            deleteFixup(x);
        }
        this.size--;
        return true;
    }

    void deleteFixup(Node x) {
        while (x != root && x.color == B) {
            if (x == x.p.left) {
                Node w = x.p.right;
                if (w.color == R) {
                    w.color = B;
                    x.p.color = R;
                    rotateLeft(x.p);
                    w = x.p.right;
                }
                if (w.left.color == B && w.right.color == B) {
                    w.color = R;
                    x = x.p;
                    continue;
                } else if (w.right.color == B) {
                    w.left.color = B;
                    w.color = R;
                    rotateRight(w);
                    w = x.p.right;
                }
                if (w.right.color == R) {
                    w.color = x.p.color;
                    x.p.color = B;
                    w.right.color = B;
                    rotateLeft(x.p);
                    x = root;
                }
            } else {
                Node w = x.p.left;
                if (w.color == R) {
                    w.color = B;
                    x.p.color = R;
                    rotateRight(x.p);
                    w = x.p.left;
                }
                if (w.right.color == B && w.left.color == B) {
                    w.color = R;
                    x = x.p;
                    continue;
                } else if (w.left.color == B) {
                    w.right.color = B;
                    w.color = R;
                    rotateLeft(w);
                    w = x.p.left;
                }
                if (w.left.color == R) {
                    w.color = x.p.color;
                    x.p.color = B;
                    w.left.color = B;
                    rotateRight(x.p);
                    x = root;
                }
            }
        }
        x.color = B;
    }

    public void print2DUtil(Node root, int space)
    {
        // Base case
        if (root == null)
            return;

        // Increase distance between levels
        int COUNT = 10;
        space += COUNT;

        // Process right child first
        print2DUtil(root.right, space);

        // Print current node after space
        // count
        System.out.print("\n");
        for (int i = COUNT; i < space; i++)
            System.out.print(" ");
        System.out.print(root);

        // Process left child
        print2DUtil(root.left, space);
    }

    public void swap(int previousNumber, int newNumber) {
        if (this.delete(previousNumber)) {
            this.insert(newNumber);
        }
    }

    public boolean contains(int key) {
        return this.containsNode(key) != nil;
    }

    private Node containsNode(int key) {
        Node aux = root;
        while (aux != nil) {
            if (aux.key == key) {
                break;
            } else if (aux.key > key) {
                aux = aux.left;
            } else {
                aux = aux.right;

            }
        }
        return aux;
    }

    public String print() {
        StringBuilder builder = new StringBuilder();
        this.printTree(root, builder);
        builder.append("\n");
        return builder.toString();
    }

    public void printTree(Node node, StringBuilder toPrint) {
        if (node == nil) {
            return;
        }
        printTree(node.left, toPrint);
        toPrint.append(node.key).append(" ");
        printTree(node.right, toPrint);
    }
}