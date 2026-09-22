#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node *next; };
void create(struct node **head,int data) {}
void print(struct node *head) {}
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Link list data:");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nLink list data after fold:");
    int l = 0, r = n - 1;
    while (l <= r) {
        if (l == r) { printf("%d ", a[l]); break; }
        printf("%d %d ", a[l], a[r]);
        l++; r--;
    }
    return 0;
}
