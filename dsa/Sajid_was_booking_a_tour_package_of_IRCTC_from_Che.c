#include <stdio.h>
char stack[100005];
int t;

void push(char c) {
    stack[t++] = c;
}

char pop() {
    return stack[--t];
}

int empty() {
    return t == 0;
}

int main() {
    char c;
    int ok = 1;
    while ((c = getchar()) != EOF) {
        if (c == '(' || c == '[' || c == '{')
            push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (empty()) {
                ok = 0;
                break;
            }
            char x = pop();
            if (!((x == '(' && c == ')') || (x == '[' && c == ']') || (x == '{' && c == '}')))
                ok = 0;
        }
    }
    puts(ok && empty() ? "Balanced" : "Not Balanced");
    return 0;
}
