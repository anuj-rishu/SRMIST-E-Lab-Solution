#include <stdio.h>
int a[5], l = -1, r = 5;

void push1(int x) {
    a[++l] = x;
}

void push2(int x) {
    a[--r] = x;
}

int pop1() {
    return a[l--];
}

int pop2() {
    return a[r++];
}

int main() {
    int x;
    scanf("%d", &x);
    push1(x);
    scanf("%d", &x);
    push2(x);
    scanf("%d", &x);
    push1(x);
    scanf("%d", &x);
    push2(x);
    scanf("%d", &x);
    push1(x);
    printf("Popped element from stack1 is:%d\nPopped element from stack2 is:%d", pop1(), pop2());
    return 0;
}
