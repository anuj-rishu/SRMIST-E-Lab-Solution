#include <stdio.h>
#include <string.h>

typedef struct stack {
    char a[1005];
    int top;
} stack;

void arranging(char *s, int n, stack *p) {
    int at[1005], t = 0;
    p->top = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '/')
            at[t++] = p->top;
        else if (s[i] == '\\') {
            int l = at[--t], r = p->top - 1;
            while (l < r) {
                char c = p->a[l];
                p->a[l++] = p->a[r];
                p->a[r--] = c;
            }
        } else
            p->a[p->top++] = s[i];
    }
    p->a[p->top] = 0;
}

int main() {
    char S[1005];
    stack s1;
    scanf("%s", S);
    arranging(S, strlen(S), &s1);
    puts(s1.a);
    return 0;
}
