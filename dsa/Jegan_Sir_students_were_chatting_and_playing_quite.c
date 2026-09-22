#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node *left,*right; };
struct node* newNode(int item) {
    struct node* n = malloc(sizeof(struct node));
    n->data = item; n->left = n->right = NULL;
    return n;
}
struct node* insert(struct node* root, int val) {
    if (!root) return newNode(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}
int f = 1;
void preorder(struct node* root) {
    if (!root) return;
    if (!f) printf(" ");
    printf("%d", root->data);
    f = 0;
    preorder(root->left);
    preorder(root->right);
}
int main() {
    int n, x;
    if (scanf("%d", &n) != 1) return 0;
    struct node* root = NULL;
    while (n--) { scanf("%d", &x); root = insert(root, x); }
    preorder(root);
    return 0;
}
