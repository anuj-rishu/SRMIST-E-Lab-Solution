#include <stdio.h>
#include <string.h>

struct word {
    char str[10];
    int found;
} w[55];

void check(char *s,int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(w[i].str, s) == 0) w[i].found = 1;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    if (t < 1 || t > 5) {
        printf("Invaild.\n");
        return 0;
    }
    while (t--) {
        int n, k, i;
        scanf("%d%d", &n, &k);
        for(i=0;i<n;i++) {
            scanf("%s",w[i].str);
            w[i].found = 0;
        }
        for (int p = 0; p < k; p++) {
            int l;
            scanf("%d", &l);
            for (int j = 0; j < l; j++) {
                char phrase_word[10];
                scanf("%s", phrase_word);
                check(phrase_word, n);
            }
        }
        for (i = 0; i < n; i++) {
            if (w[i].found) printf("YES ");
            else printf("NO ");
        }
        printf("\n");
    }
}
