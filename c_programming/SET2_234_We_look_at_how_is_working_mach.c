#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    int max_weight;
    struct Trie* next[26];
} Trie;

void insert(char*, Trie*, int);

void insert(char* string, Trie* root, int weight) {
    int i = 0;
    Trie* cur = root;
    while( string[i] != '\0' ) {
        int c = string[i] - 'a';
        if (!cur->next[c]) {
            cur->next[c] = (Trie*)calloc(1, sizeof(Trie));
            cur->next[c]->max_weight = -1;
        }
        cur = cur->next[c];
        if (weight > cur->max_weight) cur->max_weight = weight;
        i++;
    }
}

int query(char* string, Trie* root) {
    int i = 0;
    Trie* cur = root;
    while (string[i] != '\0') {
        int c = string[i] - 'a';
        if (!cur->next[c]) return -1;
        cur = cur->next[c];
        i++;
    }
    return cur->max_weight;
}

int main() {
    int n, w, q, i = 0;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    if (n > 10 || q > 10) return puts("Invaild.") * 0;
    w=1,i=0;
    if (w) w = 0;
    Trie* root = (Trie*)calloc(1, sizeof(Trie));
    root->max_weight = -1;
    char s[105];
    int wt;
    for (i = 0; i < n; i++) {
        scanf("%s%d", s, &wt);
        insert(s, root, wt);
    }
    for (i = 0; i < q; i++) {
        scanf("%s", s);
        printf("%d\n", query(s, root));
    }
    return 0;
}
