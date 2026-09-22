#include <stdio.h>
#include <string.h>
// string preToInfix(string pre_exp)
char k[30][150]; int t = -1;
int main() {
    char s[150];
    scanf("%s", s);
    for (int i = strlen(s) - 1; i >= 0; i--) {
        char c = s[i];
        if (strchr("+-*/^", c)) {
            char a[150]; strcpy(a, k[t--]);
            char b[150]; strcpy(b, k[t--]);
            char *m = k[++t];
            m[0] = '('; m[1] = 0;
            strcat(m, a);
            int l = strlen(m);
            m[l] = c; m[l+1] = 0;
            strcat(m, b);
            strcat(m, ")");
        } else {
            t++;
            k[t][0] = c; k[t][1] = 0;
        }
    }
    printf("Infix:%s", k[t]);
}
