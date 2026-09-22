#include <stdio.h>
#include <string.h>
#include <ctype.h>
// string infixToPostfix(string infix)
int pr[128];
void init() { pr['^'] = 3; pr['*'] = pr['/'] = 2; pr['+'] = pr['-'] = 1; }
void rswap(char *s, char *r) {
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        char c = s[n - 1 - i];
        r[i] = (c == '(') ? ')' : ((c == ')') ? '(' : c);
    }
    r[n] = 0;
}
void hclose(char *op, int *t, char *p, int *q) {
    while (*t >= 0 && op[*t] != '(') p[(*q)++] = op[(*t)--];
    (*t)--;
}
void hop(char *op, int *t, char *p, int *q, char c) {
    while (*t >= 0 && op[*t] != '(' && pr[(int)op[*t]] > pr[(int)c]) p[(*q)++] = op[(*t)--];
    op[++(*t)] = c;
}
void conv(char *r, char *p, int *q) {
    char op[99]; int t = -1;
    for (int i = 0; r[i]; i++) {
        char c = r[i];
        if (isalnum(c)) p[(*q)++] = c;
        else if (c == '(') op[++t] = c;
        else if (c == ')') hclose(op, &t, p, q);
        else hop(op, &t, p, q, c);
    }
    while (t >= 0) p[(*q)++] = op[t--];
    p[*q] = 0;
}
int main() {
    init();
    char s[99], r[99], p[99];
    int q = 0;
    scanf("%s", s);
    rswap(s, r);
    conv(r, p, &q);
    while (q--) putchar(p[q]);
    return 0;
}
