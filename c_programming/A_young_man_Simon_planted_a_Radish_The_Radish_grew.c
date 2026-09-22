#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 1000

int stack[MAX_SIZE];
int top = -1;

void push(int element);
void push(int element) {
    stack[++top] = element;
}

int pop() {
    return stack[top--];
}

int applyOp(int a, int b, char op) {
    return (op == '+') ? a + b : (op == '-') ? a - b : (op == '*') ? a * b : a / b;
}

int main() {
    char exp[1005];
    if (scanf("%s", exp) != 1) return 0;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            push(exp[i] - '0');
        } else {
            int val2 = pop();
            int val1 = pop();
            push(applyOp(val1, val2, exp[i]));
        }
    }
    printf("%d\n", pop());
    return 0;
}
