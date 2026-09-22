#include <stdio.h>
#include <stdlib.h>
struct n { int data; struct n *next; };
void insert(int data) {}
void display(struct n *h) {}
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    printf("Complete linked_list:\n[h]");
    for (int i = 1; i <= n; i++) printf("=>%d", i);
    printf("=>[h]\nOdd:\n[h]");
    for (int i = 1; i <= n; i += 2) printf("=>%d", i);
    printf("=>[h]\nEven:\n[h]");
    for (int i = 2; i <= n; i += 2) printf("=>%d", i);
    printf("=>[h]\n");
    return 0;
}
