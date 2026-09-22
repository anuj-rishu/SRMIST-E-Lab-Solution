#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
     if(t<=0||t>=1000) {
        printf("Invalid Input\n");
        return 0;
    }
    while (t--) {
        char matchscenario[102];
        scanf("%s",matchscenario);
        int len = strlen(matchscenario);
        int arif = 0, opp = 0;
        for (int i = 0; i < len; i++) {
            if (matchscenario[i] == '1') arif++;
            else opp++;
            if ((arif >= 11 || opp >= 11) && (arif - opp >= 2 || opp - arif >= 2)) break;
        }
        if (arif >= 11 && arif - opp >= 2) printf("WIN\n");
        else printf("LOSS\n");
    }
    return 0;
}
