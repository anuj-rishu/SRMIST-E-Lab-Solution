#include <stdio.h>
#include <string.h>

int check(char *str, int l) {
    for (int i = 0; i + 2 < l; i++) {
        if ((str[i] == '0' && str[i + 1] == '1' && str[i + 2] == '0') ||
            (str[i] == '1' && str[i + 1] == '0' && str[i + 2] == '1'))
            return 1;
    }
    return 0;
}

int main() {
    int t;
    scanf("%d", &t);
    if (t < 1 || t > 10) return printf("Invalid input\n") * 0;
    while (t--) {
        char str[100005];
        scanf("%s", str);
        if (strlen(str) > 100000) continue;
        int l = strlen(str);
        int flag = check(str, l);
        if (flag == 0) printf("Bad\n");
        else printf("Good\n");
    }
}
