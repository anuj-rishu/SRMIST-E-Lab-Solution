#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

void insertStart(struct Node **head, int data) {
    struct Node *p = malloc(sizeof *p);
    p->data = data;
    p->prev = 0;
    p->next = *head;
    if (*head)
        (*head)->prev = p;
    *head = p;
}

int main() {
    int n, x;
    struct Node *h = 0, *p, *last = 0;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        insertStart(&h, x);
    }
    for (p = h; p; p = p->next) {
        printf("%d ", p->data);
        last = p;
    }
    puts("");
    for (p = last; p; p = p->prev)
        printf("%d ", p->data);
    return 0;
}
