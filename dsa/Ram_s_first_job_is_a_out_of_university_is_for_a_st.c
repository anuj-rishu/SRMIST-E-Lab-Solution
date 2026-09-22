void dummy(){}
#include <stdio.h>
#include <string.h>

#define CMDS 5
#define TOKENS 4
#define MAXWORDS 50

int cl[CMDS];
char *lists[CMDS][MAXWORDS];
char *tokens[TOKENS]={"[N]","[AV]","[V]","[AJ]"};
char *cmds[CMDS]={"NOUNS","ADVERBS","VERBS","ADJECTIVES","END"};

char b[5000];
int bp;
int u[CMDS];

int main() {
    char s[500];
    if (!fgets(s, 500, stdin)) return 0;
    char l[100];
    int c = -1, i;
    while (fgets(l, 100, stdin)) {
        for (i = 0; l[i]; i++) if (l[i] < 32) l[i] = 0;
        if (!l[0]) continue;
        int f = -1;
        for (i = 0; i < CMDS; i++) if (!strcmp(l, cmds[i])) f = i;
        if (f == 4) break;
        if (f >= 0) c = f;
        else if (c >= 0) {
            strcpy(&b[bp], l);
            lists[c][cl[c]++] = &b[bp];
            bp += strlen(l) + 1;
        }
    }
    for (int r = 0; r < 2; r++) {
        char *p = s;
        while (*p) {
            int m = -1;
            for (i = 0; i < TOKENS; i++) {
                if (!strncmp(p, tokens[i], strlen(tokens[i]))) {
                    m = i;
                    p += strlen(tokens[i]);
                    break;
                }
            }
            if (m >= 0) printf("%s", lists[m][u[m]++]);
            else putchar(*p++);
        }
    }
    return 0;
}
