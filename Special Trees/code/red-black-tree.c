#include <stdio.h>
#include <stdlib.h>

#define red_color  "\033[31m"
#define reset_color "\033[0m" 

typedef enum {RED, BLACK} COLOR;

typedef struct Node {
    int key;
    COLOR color;
    struct Node *left, *right, *parent;
} Node;

typedef struct Tree {
    Node* root;
    Node* nil;
} Tree;

Node* create_node(Tree* tree, int key) {
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = tree->nil;
    return node;
}

Tree* create_tree() {
    Tree *tree = malloc(sizeof(Tree));
    tree->nil = malloc(sizeof(Node));
    tree->nil->color = BLACK;
    tree->nil->parent = tree->nil->left = tree->nil->right = tree->nil;
    tree->root = tree->nil;
    return tree;
}


void rotate_right(Tree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == tree->nil) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rotate_left(Tree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->nil) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}


void insert_fixup(Tree *tree, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(Tree *tree, int key) {
    Node *z = create_node(tree, key);
    Node *y = tree->nil;
    Node *x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == tree->nil) tree->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    insert_fixup(tree, z);
}

void preorder(Tree *tree, Node *node) {
    if (node == tree->nil) return;
    if (node->color == RED) printf(red_color "%d " reset_color, node->key);
    else printf("%d ", node->key);
    preorder(tree, node->left);
    preorder(tree, node->right);
}

void inorder(Tree *tree, Node *node) {
    if (node == tree->nil) return;
    inorder(tree, node->left);
    if (node->color == RED) printf(red_color "%d " reset_color, node->key);
    else printf("%d ", node->key);
    inorder(tree, node->right);
}


int main() {
    Tree *tree = create_tree();
    int student_number[11] = {1, 4, 0, 3, 6, 3, 2, 1, 0, 0, 1};

    for(int i = 0; i < 11; i++){
        insert(tree, student_number[i]);
    }

    printf("in-order:\n"); // ldr
    inorder(tree, tree->root);
    printf("\n\npre-order:\n"); // dlr
    preorder(tree, tree->root);
    printf("\n");

    return 0;
}
