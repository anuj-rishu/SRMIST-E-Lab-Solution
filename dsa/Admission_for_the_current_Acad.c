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

void printMiddle(struct node *head) {
    struct node *slow_ptr = head;
    struct node *fast_ptr = head;

    while (fast_ptr) {
        fast_ptr = fast_ptr->next;
        if (!fast_ptr) break;
        fast_ptr = fast_ptr->next;
        slow_ptr = slow_ptr->next;
    }
    if (slow_ptr) printf("The middle element is [%d]\n", slow_ptr->data);
}

int main() {
    int n, i, val;
    struct node *head = NULL;
    
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        push(&head, val);
    }
    
    printf("Linked list:");
    struct node *temp = head;
    while(temp) {
        printf("-->%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
    
    printMiddle(head);
    
    return 0;
}
