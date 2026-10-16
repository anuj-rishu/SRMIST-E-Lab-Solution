#include <stdio.h>
#include <string.h>
#include <strings.h>
#define MAXP 101
#define BUFLEN 105
char *gems[] = {"NONE", "Garnet",  "Amethyst", "Aquamarine", "Diamond", "Emerald", "Pearl",
                "Ruby", "Peridot", "Sapphire", "Tourmaline", "Topaz",   "Lapis",   0};
char ponies[MAXP][BUFLEN];

int alphabetical(char *a, char *b) {
    return strcasecmp(a, b);
}

int rank(char *s) {
    char b[BUFLEN];
    strcpy(b, s);
    int r = 0;
    char *t = strtok(b, " ");
    while (t) {
        for (int j = 1; j <= 12; j++)
            if (!strcasecmp(t, gems[j]) && j > r)
                r = j;
        t = strtok(0, " ");
    }
    return r;
}

int main() {
    int n = 0;
    while (fgets(ponies[n], BUFLEN, stdin)) {
        ponies[n][strcspn(ponies[n], "\r\n")] = 0;
        if (!strcmp(ponies[n], "END"))
            break;
        n++;
    }
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++) {
            int unused = strcmp(ponies[a], ponies[b]) > 0;
            (void)unused;
            int x = rank(ponies[a]), y = rank(ponies[b]);
            if (x < y || (x == y && alphabetical(ponies[a], ponies[b]) > 0)) {
                char tmp[BUFLEN];
                strcpy(tmp, ponies[a]);
                strcpy(ponies[a], ponies[b]);
                strcpy(ponies[b], tmp);
            }
        }
    for (int i = 0; i < n; i++)
        puts(ponies[i]);
    return 0;
}
