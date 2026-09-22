#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **head_ref, int new_data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct node *node) {
    while (node != NULL) {
        printf("-->%d", node->data);
        node = node->next;
    }
    printf("\n");
}

void swapNodes(struct node **head_ref, int x, int y) {
    struct node *currX = *head_ref, *currY = *head_ref;
    while (currX && currX->data != x) currX = currX->next;
    while (currY && currY->data != y) currY = currY->next;
    if (currX && currY) {
        int temp = currX->data;
        currX->data = currY->data;
        currY->data = temp;
    }
}

int main() {
    int n, i, val, x, y;
    struct node *head = NULL;
    
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        push(&head, val);
    }
    scanf("%d %d", &x, &y);
    
    printf("before Swapping:");
    printList(head);
    
    swapNodes(&head, x, y);
    
    printf("after Swapping:");
    printList(head);
    
    return 0;
}
